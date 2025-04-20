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

#include "parser.h"

#include <weekend.h>
#include <schedule.h>
#include <business_day_adjuster_interface.h>
#include <calendar.h>

#include <chrono>
#include <iostream>

using namespace gregorian;

using namespace std;
using namespace std::chrono;



inline auto parse_ics_england_and_wales() -> schedule
{
	// from https://www.gov.uk/bank-holidays
	return parse_ics("..\\..\\..\\example\\ICS\\data\\england-and-wales.ics"); // or set a working directory?
}

inline auto parse_ics_scotland() -> schedule
{
	// from https://www.gov.uk/bank-holidays
	return parse_ics("..\\..\\..\\example\\ICS\\data\\scotland.ics");
}

inline auto parse_ics_northern_ireland() -> schedule
{
	// from https://www.gov.uk/bank-holidays
	return parse_ics("..\\..\\..\\example\\ICS\\data\\northern-ireland.ics");
}

inline auto parse_ics_united_states() -> schedule
{
	// from https://www.newyorkfed.org/aboutthefed/holiday_schedule
	return parse_ics("..\\..\\..\\example\\ICS\\data\\united-states.ics"); // is it the same as US national hols?
}



int main()
{
	const auto good_friday = 2023y / April / 7d;

	const auto england = calendar{ SaturdaySundayWeekend, parse_ics_england_and_wales() };
	const auto wales = calendar{ SaturdaySundayWeekend, parse_ics_england_and_wales() };
	const auto scotland = calendar{ SaturdaySundayWeekend, parse_ics_scotland() };
	const auto northern_ireland = calendar{ SaturdaySundayWeekend, parse_ics_northern_ireland() };

	const auto united_states = calendar{ SaturdaySundayWeekend, parse_ics_united_states() };

	cout << boolalpha;

	cout << "Good Friday " << good_friday << endl;

	cout << "Is it a business day in England? " << england.is_business_day(good_friday) << endl;
	cout << "Is it a business day in Wales? " << wales.is_business_day(good_friday) << endl;
	cout << "Is it a business day in Scotland? " << scotland.is_business_day(good_friday) << endl;
	cout << "Is it a business day in Northern Ireland? " << northern_ireland.is_business_day(good_friday) << endl;

	cout << "Is it a business day in United States? " << united_states.is_business_day(good_friday) << endl;

	return 0;
}
