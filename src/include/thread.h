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

namespace detail {

//! boolean that is set to false when moved
class owned_bool
{
	bool _value;
public:
	owned_bool(owned_bool&& other) :
		_value(std::move(other._value))
	{
		other._value = false;
	}
	owned_bool(const owned_bool& ) = delete;

	owned_bool& operator=(owned_bool&& other) {
		_value = std::move(other._value);
		other._value = false;
		return *this;
	}
	owned_bool& operator=(const owned_bool& ) = delete;

	owned_bool(bool value) : _value(value) {}
	owned_bool() = default;
	operator bool() const { return _value; }
};

//! base class with threadpool_t access
class thread_base
{
	friend class threadpool_base;
protected:
	owned_bool running = true; //!< only to be used by main thread
	//!< only flipped once by thread itself,
	//!< and "now and then" read by main thread
	bool zombie = false;

	//!< main: only uses or changed this before running or
	//!< thread itself uses it to join and to leave the tp
	threadpool_t* tp = nullptr;
	thread_base(threadpool_t& _tp);
	thread_base() = default;
};

}

//! thread class for general threads
//! all members are only either used by self or main thread
//! each function must make this sure each time it is being called
//! @note all public functions are only allowed to be called by
//!  the main thread
class thread_t : public detail::thread_base
{
public:
	bool is_main_thread;
private:
	std::thread thred;
protected:
	//!< only called by this thread
	static void join_pool(threadpool_t* tp, thread_t* self);
private:
	void clean_up(); //!< main thread only
protected:
	thread_t(threadpool_t& _tp, bool is_main_thread);
public:
	void join();
	thread_t(threadpool_t& _tp) : thread_t(_tp, false) {}
	thread_t(const thread_t& ) = delete;
	// TODO: update threadpool about ptr change??
	thread_t(thread_t&& ) = default;
	thread_t() = default;

	thread_t& operator=(const thread_t& ) = delete;
	// TODO: update threadpool about ptr change??
	thread_t& operator=(thread_t&& ) = default;

	~thread_t();
};

class main_thread_t : public thread_t
{
public:
	main_thread_t(threadpool_t& _tp)
		: thread_t(_tp, true) {}

	//! runs this thread. this should be called by the main thread
	//! @note: you might want to release a thread of the threadpool
	//! @a before you call this function
	void acquire() { join_pool(tp, this); } // TODO: safe??

	// TODO: allow moving???
};

}

#endif // THREAD_H
