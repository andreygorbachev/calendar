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

		static auto _make_Tokyo_known_schedule_part0() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?

				// from https://www.boj.or.jp/en/about/outline/holi.htm

				2026y / January / 1d,
				2026y / January / 2d,
				2026y / January / 3d,
				2026y / January / 11d,
				2026y / February / 11d,
				2026y / February / 23d,
				2026y / March / 20d,
				2026y / April / 29d,
				2026y / May / 3d,
				2026y / May / 4d,
				2026y / May / 5d,
				2026y / May / 6d,
				2026y / July / 20d,
				2026y / August / 11d,
				2026y / September / 21d,
				2026y / September / 22d,
				2026y / September / 23d,
				2026y / October / 12d,
				2026y / November / 3d,
				2026y / November / 23d,
				2026y / December / 31d,

				2027y / January / 1d,
				2027y / January / 2d,
				2027y / January / 3d,
				2027y / January / 11d,
				2027y / February / 11d,
				2027y / February / 23d,
				2027y / March / 21d,
				2027y / March / 22d,
				2027y / April / 29d,
				2027y / May / 3d,
				2027y / May / 4d,
				2027y / May / 5d,
				2027y / July / 19d,
				2027y / August / 11d,
				2027y / September / 20d,
				2027y / September / 23d,
				2027y / October / 11d,
				2027y / November / 3d,
				2027y / November / 23d,
				2027y / December / 31d,
			};

			return schedule{
				days_period{ 2026y / FirstDayOfJanuary, 2027y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		auto make_Tokyo_calendar_versions() -> _calendar_versions
		{
			const auto known_part = _make_Tokyo_known_schedule_part0();

			// should provisional dates as of publication time should be historical rules?

			auto cal0 = calendar{
				SaturdaySundayWeekend,
				known_part
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}