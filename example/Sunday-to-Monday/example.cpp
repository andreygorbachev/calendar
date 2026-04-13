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

#include <calendar.h>
#include <schedule.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>
#include <period.h>
#include <weekend.h>
#include <business_day_adjusters.h>

#include <chrono>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace gregorian;

using namespace std;
using namespace std::chrono;



const auto _MartinLutherKing = weekday_indexed_holiday{ January / Monday[3] }; // Birthday Of Martin Luther King, Jr.
const auto _Washington = weekday_indexed_holiday{ February / Monday[3] }; // Washington's Birthday
const auto _MemorialDay = weekday_last_holiday{ May / Monday[last] };
const auto _Juneteenth = named_holiday{ June / 19d }; // Emancipation Day
const auto _IndependenceDay = named_holiday{ July / 4d };
const auto _LaborDay = weekday_indexed_holiday{ September / Monday[1] };
const auto _ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
const auto _VeteransDay = named_holiday{ November / 11d };
const auto _ThanksgivingDay = weekday_indexed_holiday{ November / Thursday[4] };

static auto make_Nearest(const util::years_period& period) -> calendar
{
	const auto rules = annual_holiday_storage{
		&NewYearsDay,
		&_MartinLutherKing,
		&_Washington,
		&_MemorialDay,
		&_Juneteenth,
		&_IndependenceDay,
		&_LaborDay,
		&_ColumbusDay,
		&_VeteransDay,
		&_ThanksgivingDay,
		&ChristmasDay
	};

	const auto s = make_holiday_schedule(
		period,
		rules
	);

	auto cal = calendar{
		SaturdaySundayWeekend,
		s
	};
	cal.substitute(Nearest);

	return cal;
}

static auto make_Sunday_to_Monday(const util::years_period& period) -> calendar
{
	const auto rules = annual_holiday_storage{
		&NewYearsDay,
		&_MartinLutherKing,
		&_Washington,
		&_MemorialDay,
		&_Juneteenth,
		&_IndependenceDay,
		&_LaborDay,
		&_ColumbusDay,
		&_VeteransDay,
		&_ThanksgivingDay,
		&ChristmasDay
	};

	const auto s = make_holiday_schedule(
		period,
		rules
	);

	// move holiday falling on Sunday to Monday
	auto cal0 = calendar{
		SundayWeekend,
		s
	};
	cal0.substitute(Following);

	// add Saturdays
	const auto cal1 = calendar{
		SaturdaySundayWeekend,
		schedule{ s.get_period(), {} }
	};

	return cal0 | cal1;
}



// K.8 - Holidays Observed by the Federal Reserve System 2026-2030
// also https://www.frbservices.org/about/holiday-schedules
int main()
{
	const auto period = util::years_period{ 2026y, 2030y };

	const auto nearest = make_Nearest(period);
	const auto sunday_to_monday = make_Sunday_to_Monday(period);

	const auto dp = util::days_period{
		period.get_from() / January / 1d,
		period.get_until() / December / 31d
	};

	auto diffs = schedule::dates{};
	ranges::set_symmetric_difference(
		nearest.make_business_days_schedule(dp).get_dates(),
		sunday_to_monday.make_business_days_schedule(dp).get_dates(),
		inserter(diffs, diffs.begin())
	);
	cout << "The following dates are in one calendar but not in the other:" << endl;
	for (const auto& d : diffs)
		cout << d << endl;

	return 0;
}
