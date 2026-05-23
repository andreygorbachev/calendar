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

		auto make_Warsaw_calendar_versions() -> _calendar_versions
		{
			const auto ThreeKingsDay = named_holiday{ January / 6d };
			const auto LabourDay = named_holiday{ May / 1d };
			const auto ConstitutionDay = named_holiday{ May / 3d };
			const auto CorpusChristi = offset_holiday{ &_Easter, days{ 60 } }; // should it be in the main library?
			const auto AssumptionDay = named_holiday{ August / 15d };
			const auto AllSaintsDay = named_holiday{ November / 1d };
			const auto IndependenceDay = named_holiday{ November / 11d };

			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&ThreeKingsDay,
				&LabourDay,
				&ConstitutionDay,
				// &_Easter,
				&EasterMonday,
				&CorpusChristi,
				&AssumptionDay,
				&ChristmasDay,
				&BoxingDay,
				&AllSaintsDay,
				&IndependenceDay
			};

			const auto s = make_holiday_schedule(
				years_period{ Epoch.get_from().year(), Epoch.get_until().year() },
				rules
			);

			auto cal = calendar{
				SaturdaySundayWeekend,
				s
			};

			return {
				{ cal.get_schedule().get_period().get_from(), std::move(cal) },
			};
		}

	}

}