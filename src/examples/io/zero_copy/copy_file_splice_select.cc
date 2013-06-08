/*
 * This file is part of the linuxapi project.
 * Copyright (C) 2011-2013 Mark Veltzer <mark.veltzer@gmail.com>
 *
 * The linuxapi package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * The linuxapi package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with the GNU C Library; if not, write to the Free
 * Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
 * 02111-1307 USA.
 */

#include <firstinclude.h>
#include <stdio.h>	// for fprintf(3)
#include <stdlib.h>	// for exit(3), EXIT_SUCCESS, EXIT_FAILURE, atoi(3)
#include <sys/types.h>	// for open(2)
#include <sys/stat.h>	// for open(2)
#include <fcntl.h>	// for open(2), splice(2), fcntl(2)
#include <unistd.h>	// getpagesize(2), fcntl(2)
#include <us_helper.h>	// for CHECK_NOT_M1()
#include <limits.h>	// for INT_MAX
#include <Selector.hh>	// for Selector:Object

/*
 * This copy file program uses both splice and select to even better
 * performance.
 */

void copy_file(const char* filein, const char* fileout, const bool setbufsize, const size_t buf_size) {
	// lets create a pipe
	int pipe_fds[2];
	CHECK_NOT_M1(pipe2(pipe_fds,O_NONBLOCK));
	if(setbufsize) {
		CHECK_NOT_M1(fcntl(pipe_fds[0], F_SETPIPE_SZ, buf_size));
	}
	int fdin=CHECK_NOT_M1(open(filein, O_RDONLY|O_LARGEFILE|O_NONBLOCK, 0666));
	int fdout=CHECK_NOT_M1(open(fileout, O_WRONLY|O_CREAT|O_TRUNC|O_LARGEFILE|O_NONBLOCK, 0666));
	size_t data=0;
	Selector s;
	bool eof=false;
	do {
		s.null();
		if(data>0) {
			s.addWriteFd(fdout);
		}
		if(!eof && buf_size-data>0) {
			s.addReadFd(fdin);
		}
		s.doSelect();
		if (s.isReadActive(fdin)) {
			ssize_t len=CHECK_NOT_M1(splice(fdin, 0, pipe_fds[1], 0, buf_size-data, SPLICE_F_MOVE | SPLICE_F_NONBLOCK));
			if(len==0) {
				eof=true;
			} else {
				data+=len;
			}
		}
		if (s.isWriteActive(fdout)) {
			data-=CHECK_INT(splice(pipe_fds[0], 0, fdout, 0, data, SPLICE_F_MOVE | SPLICE_F_NONBLOCK),data);
		}
	} while(!eof || data>0);
	CHECK_NOT_M1(close(pipe_fds[0]));
	CHECK_NOT_M1(close(pipe_fds[1]));
	CHECK_NOT_M1(close(fdin));
	CHECK_NOT_M1(close(fdout));
}

int main(int argc, char** argv, char** envp) {
	if(argc!=5) {
		fprintf(stderr, "%s: usage: %s [infile] [outfile] [setbufsize] [num_pages]\n", argv[0], argv[0]);
		fprintf(stderr, "%s: try to use setbufsize=1 and num_pages=8 to match what is going on in the official cp(1)\n", argv[0]);
		fprintf(stderr, "%s: which was derived by strac(1)ing cp(1)\n", argv[0]);
		return EXIT_FAILURE;
	}
	const char* filein=argv[1];
	const char* fileout=argv[2];
	bool setbufsize=atoi(argv[3]);
	const unsigned int num_pages=atoi(argv[4]);
	copy_file(filein, fileout, setbufsize, num_pages*getpagesize());
	return EXIT_SUCCESS;
}
