/*
   Copyright (C) 2021 Minh Khoa Tran

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
   */

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "pool.h"

Pool::Pool(std::size_t nthreads) : done(false)
{
	std::size_t k;

	for (k = 0; k < nthreads; k++) {
		this->workers.push_back(std::thread(&Pool::loop, this));
	}
}

Pool::~Pool()
{
	{
		std::lock_guard<std::mutex> _(this->mutex);
		done = true;
	}

	this->cond.notify_all();
	for (std::thread &worker: this->workers)
		worker.join();
}

void Pool::loop(void)
{
	while (true) {
		std::function<void()> task;

		{
			std::unique_lock<std::mutex> lock(this->mutex);

			while ((! this->done) && this->tasks.empty())
				this->cond.wait(lock);

			if (this->done && this->tasks.empty())
				return;

			task = std::move(this->tasks.front());
			this->tasks.pop();
		}

		task();
	}
}

void Pool::real_add_task(std::function<void()> task)
{
	{
		std::lock_guard<std::mutex> _(this->mutex);

		if (! this->done)
			this->tasks.push(task);
	}

	this->cond.notify_one();
	return;
}
