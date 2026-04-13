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
#include <ios>

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

static auto make_Sunday_to_Monday_adjusted_calendar(const util::years_period& period) -> calendar
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



// Holidays Observed - K.8 
// https://www.federalreserve.gov/aboutthefed/k8.htm
// https://www.frbservices.org/about/holiday-schedules

int main()
{
	const auto sunday_to_monday = make_Sunday_to_Monday_adjusted_calendar(util::years_period{ 2026y, 2030y });

	cout << boolalpha;

	// * Saturday - the Federal Reserve Banks are open, but the Board of Governors is closed on July 3, 2026, June 18, 2027, December 24, 2027, November 10, 2028, and December 31, 2028.
	// ** Sunday - the Federal Reserve Banks and the Board of Governors are closed on July 5, 2027, and November 12, 2029.

	const auto day1 = 2026y / July / 3d;
	cout << "2026 Independence Day (no adjustment): " << day1 << " is business day: " << sunday_to_monday.is_business_day(day1) << endl;

	const auto day2 = 2027y / June / 18d;
	cout << "2027 Juneteenth National Independence Day (no adjustment): " << day2 << " is business day: " << sunday_to_monday.is_business_day(day2) << endl;

	const auto day3 = 2027y / July / 5d;
	cout << "2027 Independence Day (adjustment): " << day3 << " is business day: " << sunday_to_monday.is_business_day(day3) << endl;

	const auto day4 = 2027y / December / 24d;
	cout << "2027 Christmas Day (no adjustment): " << day4 << " is business day: " << sunday_to_monday.is_business_day(day4) << endl;

	const auto day5 = 2027y / December / 31d;
	cout << "2027 New Year's Day (no adjustment): " << day5 << " is business day: " << sunday_to_monday.is_business_day(day5) << endl;

	const auto day6 = 2028y / November / 10d;
	cout << "2027 Veterans Day (no adjustment): " << day6 << " is business day: " << sunday_to_monday.is_business_day(day6) << endl;

	const auto day7 = 2029y / November / 12d;
	cout << "2028 Veterans Day (adjustment): " << day7 << " is business day: " << sunday_to_monday.is_business_day(day7) << endl;

	return 0;
}
