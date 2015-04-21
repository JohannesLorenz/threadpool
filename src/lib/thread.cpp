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

namespace threadpool
{

snd_pcm_t *thread_t::create_audio_handle()
{
	int err;
	snd_pcm_t* ret_val = nullptr;
	for(int cur_dev = 0; !ret_val && cur_dev < 8; ++cur_dev)
	{
		std::string dev_name = "hw:0,2," + std::to_string(cur_dev);

		std::cerr << "Opening device: " << dev_name << std::endl;
		err = snd_pcm_open(&ret_val, dev_name.c_str(),
			SND_PCM_STREAM_CAPTURE, 0);
		if(0 > err)
		{
			std::cerr << "Could not open pcm device: "
				<< snd_strerror(err) << std::endl;
			ret_val = nullptr;
		}
		else
		{
			std::cerr << "Opened device: "
				<< dev_name.c_str() << std::endl;
		}
	}

	if(!ret_val)
	{
		clean_up();
		std::cerr << "Could not open any pcm device: "
				<< snd_strerror(err) << std::endl;
		throw "Could not open pcm device";
	}
	return ret_val;
}

void thread_t::join_pool(thread_t *t, threadpool_t *tp) {
	tp->join(*t);
}

void thread_t::clean_up() {
	thred.join();
}

thread_t::thread_t(threadpool_t &tp, bool ) :
	thred(join_pool, this, &tp),
	audio_handle(create_audio_handle())
{
}

thread_t::~thread_t() { clean_up(); }
}
