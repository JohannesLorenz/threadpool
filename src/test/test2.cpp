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
#include <vector>

#include "thread.h"
#include "threadpool.h"

class test_threadpool : public threadpool::threadpool_t
{
	std::vector<threadpool::thread_t> threads;
public:
	test_threadpool() : threads(1) {
		threads[0] = threadpool::thread_t(*this);
	}
	bool callback() { return true; }
};

int main()
{
	try {
		test_threadpool tp;
	} catch (const char* err) {
		std::cerr << "Aborting on error caught: " << err << std::endl;
		return 1;
	}

	return 0;
}













