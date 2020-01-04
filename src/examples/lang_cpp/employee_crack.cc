/*
 * This file is part of the linuxapi package.
 * Copyright (C) 2011-2020 Mark Veltzer <mark.veltzer@gmail.com>
 *
 * linuxapi is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * linuxapi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with linuxapi. If not, see <http://www.gnu.org/licenses/>.
 */

#include <firstinclude.h>
#include <stdio.h>	// for printf(3)
#include <string.h>	// for memcpy(3)
#include <stdlib.h>	// for EXIT_SUCCESS

// //////////////////////////
// This is in the HH file //
// //////////////////////////

class Employee {
private:
	int salary;

public:
	void printSalary();
	void setSalary(int newsalary);
};

// //////////////////////////
// This is in the CC file //
// //////////////////////////
void Employee::printSalary() {
	printf("my salary is %d\n", salary);
}
void Employee::setSalary(int newsalary) {
	salary=newsalary;
}

// /////////////////////////////
// This is in the using part //
// /////////////////////////////
int main(int argc, char** argv, char** envp) {
	Employee e;
	int* p=(int*)&e;
	*p=1200;
	e.printSalary();
	return EXIT_SUCCESS;
}
