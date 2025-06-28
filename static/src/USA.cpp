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

#include "static.h"

#include <schedule.h>
#include <annual_holidays.h>
#include <weekend.h>
#include <business_day_adjusters.h>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		auto _make_K_8_calendar() -> calendar // const auto InaugurationDay = named_holiday{ January / day{ 20u } }; - do we need to handle it?
		{
			const auto from = Epoch.get_from().year();
			const auto until = Epoch.get_until().year();

			const auto MartinLutherKing = weekday_indexed_holiday{ January / Monday[3] }; // Birthday Of Martin Luther King, Jr.
			const auto Washington = weekday_indexed_holiday{ February / Monday[3] }; // Washington's Birthday
			const auto MemorialDay = weekday_last_holiday{ May / Monday[last] };
			const auto IndependenceDay = named_holiday{ July / day{ 4u } };
			const auto LaborDay = weekday_indexed_holiday{ September / Monday[1] };
			const auto ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
			const auto VeteransDay = named_holiday{ November / day{ 11u } };
			const auto ThanksgivingDay = weekday_indexed_holiday{ November / Thursday[4] };

			const auto rules1 = annual_holiday_storage{
				&NewYearsDay,
				&MartinLutherKing,
				&Washington,
				&MemorialDay,
				&IndependenceDay,
				&LaborDay,
				&ColumbusDay,
				&VeteransDay,
				&ThanksgivingDay,
				&ChristmasDay
			};

			const auto s1 = make_holiday_schedule(
				years_period{ from, 2020y },
				rules1
			);

			const auto Juneteenth = named_holiday{ June / day{ 19u } }; // Emancipation Day

			const auto rules2 = annual_holiday_storage{
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

			const auto s2 = make_holiday_schedule(
				years_period{ 2021y, until },
				rules2
			);

			auto c = calendar{
				SaturdaySundayWeekend,
				s1 + s2
			};

			c.substitute(Nearest);

			return c;
		}


		auto make_K_8_calendar() -> const calendar& // do we need the historic part explicitly?
		{
			static const auto s = _make_K_8_calendar();
			return s;
		}

	}

}
