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

#include "static_data.h"
#include "makers.h"

#include <period.h>
#include <calendar.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <weekend.h>

#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		auto make_T2_calendar_versions() -> _calendar_versions // should we give it a full name of TARGET2?
		{
			constexpr auto from = 2007y; // Actually the calendar became effective from November 2007, so not 100% sure about 2007 prior to that
			constexpr auto until = Epoch.get_until().year();
			static_assert(from <= Epoch.get_from().year(), "Non-standard [from, until] should cover Epoch");

			const auto LabourDay = named_holiday{ std::chrono::May / std::chrono::day{ 1u } };

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&GoodFriday,
				&EasterMonday,
				&LabourDay,
				&ChristmasDay,
				&BoxingDay
			};

			const auto s = make_holiday_schedule(
				years_period{ from, until },
				rules
			);

			auto cal = calendar{
				SaturdaySundayWeekend,
				s
			};
			// please note that holidays are not adjusted in T2

			return {
				{ cal.get_schedule().get_period().get_from(), std::move(cal) },
			};
		}

	}

}