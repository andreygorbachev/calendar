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
#include <schedule.h>
#include <calendar.h>
#include <weekend.h>
#include <annual_holiday_interface.h>
#include <annual_holidays.h>

#include <utility>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		// should these be in their own namespace?

		static auto _make_SHIR_known_schedule_part0() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?
				2022y / March / 17d, // Purim (Tel Aviv)
				2022y / March / 18d, // Purim (Jerusalem)
				2022y / April / 15d, // Eve of Passover and Holiday abroad
				2022y / April / 18d, // Holiday abroad
				2022y / April / 22d, // Last day of Passover
				2022y / May / 5d, // Israel Independence Day
				2022y / June / 3d, // Holiday abroad
				2022y / September / 26d, // Rosh Hashanah (New Year) 1st Day
				2022y / September / 27d, // Rosh Hashanah (New Year) 2nd Day
				2022y / October / 4d, // Eve of Day of Atonement (Yom Kippur)
				2022y / October / 5d, // Day of Atonement (Yom Kippur)
				2022y / October / 10d, // First Day of Sukkot (Tabernacles)
				2022y / October / 17d, // Rejoicing of the Law Festival (Simchat Torah)
				2022y / November / 1d, // Election Day
				2022y / December / 26d, // Holiday abroad

				2023y / January / 2d, // Holiday abroad
				2023y / March / 7d, // Purim (Tel Aviv)
				2023y / March / 8d, // Purim (Jerusalem)
				2023y / April / 5d, // Eve of Passover
				2023y / April / 6d, // Passover
				2023y / April / 7d, // Holiday abroad
				2023y / April / 10d, // Holiday abroad
				2023y / April / 12d, // Last day of Passover
				2023y / April / 26d, // Israel Independence Day
				2023y / May / 26d, // Holiday of Shavout
				2023y / May / 29d, // Holiday abroad
				2023y / July / 27d, // Fast of Ninth of Av
				2023y / September / 15d, // Eve of Rosh Hashanah (New Year)
				2023y / September / 25d, // Day of Atonement (Yom Kippur)
				2023y / October / 31d, // Municipals Elections
				2023y / December / 25d, // Holiday abroad
				2023y / December / 26d, // Holiday abroad

				2024y / January / 1d, // Holiday abroad
				2024y / February / 27d, // Municipals Elections
				2024y / March / 25d, // Purim (Jerusalem)
				2024y / March / 29d, // Holiday abroad
				2024y / April / 22d, // Eve of Passover
				2024y / April / 23d, // Passover 1st day
				2024y / April / 29d, // Last day of Passover
				2024y / May / 14d, // Israel Independence Day
				2024y / May / 27d, // Holiday abroad
				2024y / June / 12d, // Shavout (Pentecost)
				2024y / August / 13d, // Fast of Ninth of Av
				2024y / October / 2d, // Eve of Rosh Hashanah (New Year)
				2024y / October / 3d, // Rosh Hashanah (New Year) 1st Day
				2024y / October / 4d, // Rosh Hashanah (New Year) 2nd Day
				2024y / October / 11d, // Eve of Day of Atonement (Yom Kippur)
				2024y / October / 17d, // First Day of Sukkot (Tabernacles)
				2024y / October / 24d, // Rejoicing of the Law Festival (Simchat Torah)
				2024y / December / 25d, // Holiday abroad
				2024y / December / 26d, // Holiday abroad

				2025y / January / 1d, // Holiday abroad
				2025y / March / 14d, // Purim
				2025y / April / 18d, // Holiday abroad
				2025y / May / 1d, // Israel Independence Day
				2025y / May / 26d, // Holiday abroad
				2025y / June / 2d, // Shavout (Pentecost)
				2025y / September / 22d, // Eve of Rosh Hashanah (New Year)
				2025y / September / 23d, // Rosh Hashanah (New Year) 1st Day
				2025y / September / 24d, // Rosh Hashanah (New Year) 2nd Day
				2025y / October / 1d, // Eve of Day of Atonement (Yom Kippur)
				2025y / October / 2d, // Day of Atonement (Yom Kippur)
				2025y / October / 7d, // First Day of Sukkot (Tabernacles)
				2025y / October / 14d, // Rejoicing of the Law Festival (Simchat Torah)
				2025y / December / 25d, // Holiday abroad
				2025y / December / 26d, // Holiday abroad

				2026y / January / 1d, // Holiday abroad
				2026y / March / 3d, // Purim
				2026y / March / 4d, // Purim
				2026y / April / 1d, // Eve of Passover
				2026y / April / 2d, // Passover 1st day
				2026y / April / 3d, // Holiday abroad
				2026y / April / 6d, // Holiday abroad
				2026y / April / 8d, // Last day of Passover
				2026y / April / 22d, // Israel Independence Day
				2026y / May / 22d, // Shavout (Pentecost)
				2026y / May / 25d, // Holiday abroad
				2026y / July / 23d, // Fast of Ninth of Av
				2026y / September / 11d, // Eve of Rosh Hashanah (New Year)
				2026y / September / 21d, // Day of Atonement (Yom Kippur)
				2026y / October / 27d, // General Election day
				2026y / December / 25d, // Holiday abroad
				2026y / December / 28d, // Holiday abroad
			};

			return schedule{
				days_period{ 2022y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}


		auto make_SHIR_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_SHIR_known_schedule_part0()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}