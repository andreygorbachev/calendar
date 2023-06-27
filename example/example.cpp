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
#include <business_day_convention_interface.h>
#include <calendar.h>

#include <chrono>

using namespace gregorian;

using namespace std;
using namespace std::chrono;



// from https://www.gov.uk/bank-holidays
constexpr auto EnglandAndWalesICS = "england-and-wales.ics";

// from https://www.newyorkfed.org/aboutthefed/holiday_schedule
constexpr auto UnitedStatesICS = "united-states.ics";


inline auto parse_ics_england() -> const schedule&
{
	static const auto s = parse_ics(EnglandAndWalesICS);

	return s;
}

inline auto parse_ics_united_states() -> const schedule&
{
	static const auto s = parse_ics(UnitedStatesICS);

	return s;
}



int main()
{
	{
		const auto expected = calendar{ SaturdaySundayWeekend, parse_ics_england() };

//		auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_england() };
//		c.substitute(&Following);
	}

	{
		const auto expected = calendar{ SaturdaySundayWeekend, parse_ics_united_states() };

//		auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_united_states() };
//		c.substitute(&Nearest);
	}

	return 0;
}
