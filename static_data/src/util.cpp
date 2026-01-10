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
#include "makers.h"

#include <period.h>
#include <annual_holiday_interface.h>

#include <optional>
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

		// first thing we need is to generate a generated period
		// from known_period and from the Epoch
		// (maybe ignore as_of_date for now, and handle it later)
		auto make_generated_period(
			const optional<days_period>& known,
			const days_period& epoch
		) -> optional<days_period>
		{
			if (!known || known->get_until() < epoch.get_from())
				return epoch;

			if (known->get_from() < epoch.get_from())
				throw out_of_range{ "Known period from can't be after epoch from" };

			if (known->get_until() >= epoch.get_until())
				return nullopt;

			const auto generated_from = year_month_day{ sys_days{ known->get_until() } + days{1} };
			const auto generated_until = epoch.get_until();

			return days_period{ generated_from, generated_until };
		}


		auto make_holiday_schedule_as_of_date(
			const _annual_holiday_period_storage& storage,
			const year_month_day& as_of_date
		) -> annual_holiday_storage
		{
			return {};
		}

	}

}
