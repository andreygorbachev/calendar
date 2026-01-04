// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "util.h"

#include <period.h>

#include <utility>
#include <chrono>
#include <stdexcept>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// is it too confusing to have util.h/util.cpp here and util namespace elewhere?

		// first thing we need is to generate a known period and generated period
		// from what we know about holidays and from the Epoch
		// (maybe ignore as_of_date for now, and handle it later)
		auto known_period_generated_period(
			const days_period& schedule_period,
			const days_period& epoch
		) -> pair<days_period, days_period> 
		{
			if(schedule_period.get_from() < epoch.get_from())
				throw std::out_of_range{ "Schedule period from can't be after epoch from" };

			const auto known_from = schedule_period.get_from();
			const auto known_until = schedule_period.get_until();
			const auto generated_from = year_month_day{ sys_days{ known_until } + days{ 1 } };
			const auto generated_until = epoch.get_until();
			return {
				days_period{ known_from, known_until },
				days_period{ generated_from, generated_until }
			};
		}

	}

}
