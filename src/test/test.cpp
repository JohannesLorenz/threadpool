/*************************************************************************/
/* threadpool - A simple ALSA implementation of an RT safe threadpool.   */
/* Copyright (C) 2015-2015                                               */
/* Johannes Lorenz (jlsf2013 @ sourceforge)                              */
/*                                                                       */
/* This program is free software; you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation; either version 3 of the License, or (at */
/* your option) any later version.                                       */
/* This program is distributed in the hope that it will be useful, but   */
/* WITHOUT ANY WARRANTY; without even the implied warranty of            */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU      */
/* General Public License for more details.                              */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program; if not, write to the Free Software           */
/* Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110, USA  */
/*************************************************************************/

#include <iostream>

#include "thread.h"
#include "threadpool.h"

void get_free() {
char **hints;
/* Enumerate sound devices */
int err = snd_device_name_hint(-1, "pcm", (void***)&hints);
if (err != 0)
   return;//Error! Just return

char** n = hints;
while (*n != NULL) {

    char *name = snd_device_name_get_hint(*n, "NAME");

    if (name != NULL && 0 != strcmp("null", name)) {
	//Copy name to another buffer and then free it
	std::cerr << name << std::endl;
	free(name);
    }
    n++;
}//End of while

//Free hint buffer too
snd_device_name_free_hint((void**)hints);
}

int main()
{
	get_free();

	try {

		threadpool::threadpool_t tp;
		using thread_t = threadpool::thread_t;

		thread_t t1(tp);
		thread_t t2(tp);
		//thread_t t2(tp);

	} catch (const char* err) {
		std::cerr << "Aborting on error caught: " << err << std::endl;
		return 1;
	}

	return 0;
}












