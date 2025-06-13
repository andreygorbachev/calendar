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

#include "calendar_K.8.h"

#include <schedule.h>
#include <annual_holidays.h>
#include <weekend.h>
#include <business_day_adjusters.h>

using namespace std;
using namespace std::chrono;

using namespace gregorian;
using namespace gregorian::util;



auto _make_K_8_calendar() -> calendar
{
	const auto from = Epoch.year();
	const auto until = Epoch.year() + years{ 100 }; // factor out this const

	const auto MartinLutherKing = weekday_indexed_holiday{ January / Monday[3] }; // Birthday Of Martin Luther King, Jr.
	const auto Washington = weekday_indexed_holiday{ February / Monday[3] }; // Washington's Birthday
	const auto MemorialDay = weekday_last_holiday{ May / Monday[last] };
	const auto Juneteenth = named_holiday{ June / day{ 19u } }; // Juneteenth National Independence Day
	const auto IndependenceDay = named_holiday{ July / day{ 4u } };
	const auto LaborDay = weekday_indexed_holiday{ September / Monday[1] };
	const auto ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
	const auto VeteransDay = named_holiday{ November / day{ 11u } };
	const auto ThanksgivingDay = weekday_indexed_holiday{ November / Thursday[4] };

	const auto rules = annual_holiday_storage{
		&NewYearsDay,
		&MartinLutherKing,
		&Washington,
		&MemorialDay,
		&Juneteenth,
		&IndependenceDay,
		&LaborDay,
		&ColumbusDay,
		&VeteransDay,
		&ThanksgivingDay,
		&ChristmasDay
	};

	// 2025 January 20 is also an innaguration day (in addition to Birthday Of Martin Luther King, Jr.)

	const auto s = make_holiday_schedule(
		years_period{ from, until },
		rules
	);

	auto c = calendar{
		SaturdaySundayWeekend,
		s
	};

	c.substitute(Nearest);

	return c;
}


auto make_K_8_calendar() -> const calendar&
{
	static const auto s = _make_K_8_calendar();
	return s;
}
