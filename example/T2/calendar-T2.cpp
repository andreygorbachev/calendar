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

#include "calendar-T2.h"

#include <schedule.h>
#include <annual_holidays.h>
#include <weekend.h>
#include <business_day_conventions.h>

#include <memory>

using namespace std;
using namespace std::chrono;

using namespace gregorian;



auto _make_T2_calendar() -> calendar
{
	const auto from = Epoch.year();
	const auto until = Epoch.year() + years{ 100 }; // factor out this const

	const auto LabourDay = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };

	const auto rules = annual_holiday_storage{
		&NewYearsDay,
		&GoodFriday,
		&EasterMonday,
		&LabourDay,
		&ChristmasDay,
		&BoxingDay
	};

	const auto s = make_holiday_schedule(
		{ from, until },
		rules
	);

	return calendar{
		SaturdaySundayWeekend,
		s
	};
	// please note that holidays are not adjusted in T2
}


auto make_T2_calendar() -> const calendar&
{
	static const auto s = _make_T2_calendar();
	return s;
}
