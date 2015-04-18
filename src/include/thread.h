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

#include <alsa/asoundlib.h>
#include <thread>

namespace threadpool {

class threadpool;

class thread
{
	std::thread thred;
	snd_pcm_t* audio_handle = nullptr;

	static snd_pcm_t get_audio_handle() {
		if(0 > snd_pcm_open(&audio_handle, ))
		 throw "Could not open pcm device";
	}
private:
	static void join_pool(const thread* t, const threadpool& tp);
public:
	thread(const threadpool& tp)
		: thred(join_pool, this, tp)
	{
	}
};

}

#endif // THREAD_H
