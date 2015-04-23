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

#ifndef THREAD_H
#define THREAD_H

#include <atomic>
#include <thread>

namespace threadpool {

class threadpool_t;

class thread_t
{
	std::thread thred;
public: // TODO
	bool running = true;
public: // TODO!
	threadpool_t* tp;
private:
	static void join_pool(thread_t *t, threadpool_t* tp);
	void clean_up();
public:
	void join();
	thread_t(threadpool_t& _tp);
	thread_t(const thread_t& ) = delete;
	thread_t(thread_t&& ) = default;


	~thread_t();
};

}

#endif // THREAD_H
