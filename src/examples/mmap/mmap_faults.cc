/*
 * This file is part of the demos-linux package.
 * Copyright (C) 2011-2021 Mark Veltzer <mark.veltzer@gmail.com>
 *
 * demos-linux is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * demos-linux is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with demos-linux. If not, see <http://www.gnu.org/licenses/>.
 */

#include <firstinclude.h>
#include <stdio.h>	// for printf(3)
#include <sys/mman.h>	// for mmap(2), munmap(2)
#include <sys/types.h>	// for open(2), fstat(2)
#include <sys/stat.h>	// for open(2), fstat(2)
#include <fcntl.h>	// for open(2)
#include <unistd.h>	// for fstat(2), close(2), getpagesize(2)
#include <stdlib.h>	// for EXIT_SUCCESS
#include <err_utils.h>	// for CHECK_NOT_M1(), CHECK_NOT_VOIDP()
#include <proc_utils.h>	// for getrusage_show_vmem()

/*
 * This example shows the page faults that are generated by access to an mmaped file.
 * The example maps some big file to user space and then accesses it (only read).
 * This will page fault the entire file. The example prints it's resident size
 * and number of minor page faults before and after this is done and the difference
 * should be roughly the size of the file in question.
 */

/*
 * A file which is big and kind of guaranteed to exist...
 */
const char* file_to_map="/initrd.img.old";

int main(int argc, char** argv, char** envp) {
	const int pagesize=getpagesize();
	getrusage_show_vmem();
	int fd=CHECK_NOT_M1(open(file_to_map, O_RDONLY));
	struct stat stat_buf;
	CHECK_NOT_M1(fstat(fd, &stat_buf));
	printf("size of file is %ld\n", stat_buf.st_size);
	printf("which means %ld pages\n", stat_buf.st_size/pagesize);
	const int size=stat_buf.st_size;
	void *res=CHECK_NOT_VOIDP(mmap(
			NULL,	/* addr: dont recommend address */
			size,	/* size: the size of the file */
			PROT_READ,	/* prot: we just want read */
			// MAP_PRIVATE | MAP_POPULATE, /* flags: PRIVATE or SHARED ** MUST** be specified */
			MAP_PRIVATE,	/* flags: PRIVATE or SHARED ** MUST** be specified */
			fd,	/* fd: our file descriptor */
			0	/* offset: from the begining of the file */
			), MAP_FAILED);
	// we have the mmap address, we don't need the file anymore...
	CHECK_NOT_M1(close(fd));
	// lets read the memory...
	// the volatile is here to prevent the compiler from making the entire loop go
	// away. If you take it away you will find no page faults occuring at all
	// since nothing is done with 'sum' and the compiler will remove the entire
	// loop and the sum variable...
	volatile int sum=0;
	for(int i=0; i<size; i+=pagesize) {
		sum+=((char*)res)[i];
	}
	CHECK_NOT_M1(munmap(res, stat_buf.st_size));
	getrusage_show_vmem();
	return EXIT_SUCCESS;
}
