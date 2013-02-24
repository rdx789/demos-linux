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
#include <ace/Thread.h>
#include <ace/Log_Msg.h>
#include <ace/Synch.h>
#include <stdlib.h>	// for EXIT_SUCCESS

/*
 * EXTRA_COMPILE_CMDS=pkg-config --cflags ACE
 * EXTRA_LINK_CMDS=pkg-config --libs ACE
 */
static int number=0;
static int seed=0;

static void* worker(void *arg) {
	ACE_UNUSED_ARG(arg);
	ACE_DEBUG((LM_DEBUG, "Thread (%t) Created to do some work"));
	number++;
	ACE_DEBUG((LM_DEBUG, " and number is %d\n", number));

	// Let the other guy go while I fall asleep for a random period of time
	ACE_Thread::yield();
	ACE_OS::sleep(ACE_OS::rand() % 2);

	// Exiting now
	ACE_DEBUG((LM_DEBUG, "\t\t Thread (%t) Done! \t The number is now: %d\n", number));
	// ACE_OS::fflush(stdout);
	return(0);
}

int ACE_TMAIN(int argc, ACE_TCHAR** argv, ACE_TCHAR** envp) {
	if(argc<2) {
		ACE_DEBUG((LM_DEBUG, "Usage: %s <number of threads>\n", argv[0]));
	}
	int n_threads=ACE_OS::atoi(argv[1]);
	// Setup the random number generator
	ACE_OS::srand(::seed);
	// create the data structures needed
	ACE_thread_t* threads=new ACE_thread_t[n_threads];
	// ACE_hthread_t *threadHandles=new ACE_hthread_t[n_threads];
	// Spawn off n_threads number of threads
	for(int i=0; i<n_threads; i++) {
		if(ACE_Thread::spawn(
			   worker,	// thread worker function
			   NULL,// argument to worker
			   THR_NEW_LWP | THR_JOINABLE,	// flags
			   threads+i	// thread id
			   )==-1) {
			ACE_DEBUG((LM_DEBUG, "Error in spawning thread\n"));
		}
	}
	// Wait for all the threads to exit before you let the main fall through
	// and have the process exit. This way of using join is non-portable
	// and may not work on a system using pthreads.
	int check_count=0;
	// sleep(30);
	while(ACE_Thread::join(threads[check_count], NULL, NULL)==0) {
		check_count++;
	}
	ACE_DEBUG((LM_DEBUG, "It's all over\n"));
	ACE_ASSERT(check_count==n_threads);
	return EXIT_SUCCESS;
}
