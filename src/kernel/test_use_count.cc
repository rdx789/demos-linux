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
#include <sys/types.h>	// for open(2)
#include <sys/stat.h>	// for open(2)
#include <fcntl.h>	// for open(2)
#include <sys/ioctl.h>	// for ioctl(2)
#include <unistd.h>	// for close(2), sleep(3), usleep(3)
#include <stdio.h>	// for printf(3)
#include <us_helper.h>	// for CHECK_NOT_M1()
#include "shared.h"	// for ioctl numbers

/*
 * This is a simple test to see the use count of kernel modules
 */
int main(int argc, char** argv, char** envp) {
	const char *filename="/dev/mod_use_count";
	printf("Inserting the driver...\n");
	my_system("sudo rmmod mod_use_count");
	my_system("sudo insmod ./mod_use_count.ko");
	my_system("sudo chmod 666 %s", filename);
	printf("run something like watch --interval=0.2 lsmod\n");
	// file descriptor
	int fd;
	int fd2;
	while(true) {
		fd=CHECK_NOT_M1(open(filename, O_RDWR));
		fd2=CHECK_NOT_M1(open(filename, O_RDWR));
		usleep(1000000);
		// sleep(1);
		CHECK_NOT_M1(close(fd));
		CHECK_NOT_M1(close(fd2));
		usleep(1000000);
		// sleep(1);
	}
	return(0);
}
