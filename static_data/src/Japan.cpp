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
				2011y / January / 1d, // New Year's Day
				2011y / January / 2d, // Bank Holidays
				2011y / January / 3d,
				2011y / January / 10d, // Coming-of-Age Day
				2011y / February / 11d, // National Foundation Day
				2011y / March / 21d, // Vernal Equinox Day
				2011y / April / 29d, // Showa Day
				2011y / May / 3d, // Constitution Day
				2011y / May / 4d, // Greenery Day
				2011y / May / 5d, // Children's Day
				2011y / July / 18d, // Marine Day
				2011y / September / 19d, // Respect-for-the-Aged Day
				2011y / September / 23d, // Autumnal Equinox Day
				2011y / October / 10d, // Health-Sports Day
				2011y / November / 3d, // Culture Day
				2011y / November / 23d, // Labor Thanksgiving Day
				2011y / December / 23d, // The Emperor's Birthday
				2011y / December / 31d, // Bank Holiday

				2012y / January / 1d, // New Year's Day
				2012y / January / 2d, // New Year's Day Observed
				2012y / January / 3d, // Bank Holiday
				2012y / January / 9d, // Coming-of-Age Day
				2012y / February / 11d, // National Foundation Day
				2012y / March / 20d, // Vernal Equinox Day
				2012y / April / 29d, // Showa Day
				2012y / April / 30d, // Showa Day Observed
				2012y / May / 3d, // Constitution Day
				2012y / May / 4d, // Greenery Day
				2012y / May / 5d, // Children's Day
				2012y / July / 16d, // Marine Day
				2012y / September / 17d, // Respect-for-the-Aged Day
				2012y / September / 22d, // Autumnal Equinox Day
				2012y / October / 8d, // Health-Sports Day
				2012y / November / 3d, // Culture Day
				2012y / November / 23d, // Labor Thanksgiving Day
				2012y / December / 23d, // The Emperor's Birthday
				2012y / December / 24d, // The Emperor's Birthday Observed
				2012y / December / 31d, // Bank Holiday

				2013y / January / 1d, // New Year's Day
				2013y / January / 2d, // Bank Holidays
				2013y / January / 3d,
				2013y / January / 14d, // Coming-of-Age Day
				2013y / February / 11d, // National Foundation Day
				2013y / March / 20d, // Vernal Equinox Day
				2013y / April / 29d, // Showa Day
				2013y / May / 3d, // Constitution Day
				2013y / May / 4d, // Greenery Day
				2013y / May / 5d, // Children's Day
				2013y / May / 6d, // Children's Day Observed
				2013y / July / 15d, // Marine Day
				2013y / September / 16d, // Respect-for-the-Aged Day
				2013y / September / 23d, // Autumnal Equinox Day
				2013y / October / 14d, // Health-Sports Day
				2013y / November / 3d, // Culture Day
				2013y / November / 4d, // Culture Day Observed
				2013y / November / 23d, // Labor Thanksgiving Day
				2013y / December / 23d, // The Emperor's Birthday
				2013y / December / 31d, // Bank Holiday

				2014y / January / 1d, // New Year's Day
				2014y / January / 2d, // Bank Holidays
				2014y / January / 3d,
				2014y / January / 13d, // Coming-of-Age Day
				2014y / February / 11d, // National Foundation Day
				2014y / March / 21d, // Vernal Equinox Day
				2014y / April / 29d, // Showa Day
				2014y / May / 3d, // Constitution Day
				2014y / May / 4d, // Greenery Day
				2014y / May / 5d, // Children's Day
				2014y / May / 6d, // Greenery Day Observed
				2014y / July / 21d, // Marine Day
				2014y / September / 15d, // Respect-for-the-Aged Day
				2014y / September / 23d, // Autumnal Equinox Day
				2014y / October / 13d, // Health-Sports Day
				2014y / November / 3d, // Culture Day
				2014y / November / 23d, // Labor Thanksgiving Day
				2014y / November / 24d, // Labor Thanksgiving Day Observed
				2014y / December / 23d, // The Emperor's Birthday
				2014y / December / 31d, // Bank Holiday

				2015y / January / 1d, // New Year's Day
				2015y / January / 2d, // Bank Holidays
				2015y / January / 3d,
				2015y / January / 12d, // Coming-of-Age Day
				2015y / February / 11d, // National Foundation Day
				2015y / March / 21d, // Vernal Equinox Day
				2015y / April / 29d, // Showa Day
				2015y / May / 3d, // Constitution Day
				2015y / May / 4d, // Greenery Day
				2015y / May / 5d, // Children's Day
				2015y / May / 6d, // Constitution Day Observed
				2015y / July / 20d, // Marine Day
				2015y / September / 21d, // Respect-for-the-Aged Day
				2015y / September / 22d, // National Holiday
				2015y / September / 23d, // Autumnal Equinox Day
				2015y / October / 12d, // Health-Sports Day
				2015y / November / 3d, // Culture Day
				2015y / November / 23d, // Labor Thanksgiving Day
				2015y / December / 23d, // The Emperor's Birthday
				2015y / December / 31d, // Bank Holiday

				2016y / January / 1d, // New Year's Day
				2016y / January / 2d, // Bank Holidays
				2016y / January / 3d,
				2016y / January / 11d, // Coming-of-Age Day
				2016y / February / 11d, // National Foundation Day
				2016y / March / 20d, // Vernal Equinox Day
				2016y / March / 21d, // Vernal Equinox Day Observed
				2016y / April / 29d, // Showa Day
				2016y / May / 3d, // Constitution Day
				2016y / May / 4d, // Greenery Day
				2016y / May / 5d, // Children's Day
				2016y / July / 18d, // Marine Day
				2016y / August / 11d, // Mountain Day
				2016y / September / 19d, // Respect-for-the-Aged Day
				2016y / September / 22d, // Autumnal Equinox Day
				2016y / October / 10d, // Health-Sports Day
				2016y / November / 3d, // Culture Day
				2016y / November / 23d, // Labor Thanksgiving Day
				2016y / December / 23d, // The Emperor's Birthday
				2016y / December / 31d, // Bank Holiday

				2017y / January / 1d, // New Year's Day
				2017y / January / 2d, // Bank Holidays
				2017y / January / 3d,
				2017y / January / 9d, // Coming-of-Age Day
				2017y / February / 11d, // National Foundation Day
				2017y / March / 20d, // Vernal Equinox Day
				2017y / April / 29d, // Showa Day
				2017y / May / 3d, // Constitution Day
				2017y / May / 4d, // Greenery Day
				2017y / May / 5d, // Children's Day
				2017y / July / 17d, // Marine Day
				2017y / August / 11d, // Mountain Day
				2017y / September / 18d, // Respect-for-the-Aged Day
				2017y / September / 23d, // Autumnal Equinox Day
				2017y / October / 9d, // Health-Sports Day
				2017y / November / 3d, // Culture Day
				2017y / November / 23d, // Labor Thanksgiving Day
				2017y / December / 23d, // The Emperor's Birthday
				2017y / December / 31d, // Bank Holiday

				2018y / January / 1d, // New Year's Day
				2018y / January / 2d, // Bank Holidays
				2018y / January / 3d,
				2018y / January / 8d, // Coming-of-Age Day
				2018y / February / 11d, // National Foundation Day
				2018y / February / 11d, // National Foundation Day Observed
				2018y / March / 21d, // Vernal Equinox Day
				2018y / April / 29d, // Showa Day
				2018y / April / 30d, // Showa Day Observed
				2018y / May / 3d, // Constitution Day
				2018y / May / 4d, // Greenery Day
				2018y / May / 5d, // Children's Day
				2018y / July / 16d, // Marine Day
				2018y / August / 11d, // Mountain Day
				2018y / September / 17d, // Respect-for-the-Aged Day
				2018y / September / 23d, // Autumnal Equinox Day
				2018y / September / 24d, // Autumnal Equinox Day
				2018y / November / 3d, // Culture Day
				2018y / November / 23d, // Labor Thanksgiving Day
				2018y / December / 23d, // The Emperor's Birthday
				2018y / December / 23d, // The Emperor's Birthday Observed
				2018y / December / 31d, // Bank Holiday

				2019y / January / 1d, // New Year's Day
				2019y / January / 2d, // Bank Holidays
				2019y / January / 3d,
				2019y / January / 14d, // Coming-of-Age Day
				2019y / February / 11d, // National Foundation Day
				2019y / March / 21d, // Vernal Equinox Day
				2019y / April / 29d, // Showa Day
				2019y / May / 3d, // Constitution Day
				2019y / May / 4d, // Greenery Day
				2019y / May / 5d, // Children's Day
				2019y / May / 6d, // Children's Day Observed
				2019y / July / 15d, // Marine Day
				2019y / August / 11d, // Mountain Day
				2019y / August / 12d, // Mountain Day Observed
				2019y / September / 16d, // Respect-for-the-Aged Day
				2019y / September / 23d, // Autumnal Equinox Day
				2019y / November / 3d, // Culture Day
				2019y / November / 4d, // Culture Day Observed
				2019y / November / 23d, // Labor Thanksgiving Day
				2019y / December / 31d, // Bank Holiday

				2020y / January / 1d,
				2020y / January / 2d,
				2020y / January / 3d,
				2020y / January / 13d,
				2020y / February / 11d,
				2020y / February / 23d,
				2020y / February / 24d,
				2020y / March / 20d,
				2020y / April / 29d,
				2020y / May / 3d,
				2020y / May / 4d,
				2020y / May / 5d,
				2020y / May / 6d,
				2020y / July / 23d,
				2020y / July / 24d,
				2020y / August / 10d,
				2020y / September / 21d,
				2020y / September / 22d,
				2020y / November / 3d,
				2020y / November / 23d,
				2020y / December / 31d,

				2021y / January / 1d,
				2021y / January / 2d,
				2021y / January / 3d,
				2021y / January / 11d,
				2021y / February / 11d,
				2021y / February / 23d,
				2021y / March / 20d,
				2021y / April / 29d,
				2021y / May / 3d,
				2021y / May / 4d,
				2021y / May / 5d,
				2021y / July / 19d,
				2021y / August / 11d,
				2021y / September / 20d,
				2021y / September / 23d,
				2021y / October / 11d,
				2021y / November / 3d,
				2021y / November / 23d,
				2021y / December / 31d,

				2022y / January / 1d,
				2022y / January / 2d,
				2022y / January / 3d,
				2022y / January / 10d,
				2022y / February / 11d,
				2022y / February / 23d,
				2022y / March / 21d,
				2022y / April / 29d,
				2022y / May / 3d,
				2022y / May / 4d,
				2022y / May / 5d,
				2022y / July / 18d,
				2022y / August / 11d,
				2022y / September / 19d,
				2022y / September / 23d,
				2022y / October / 10d,
				2022y / November / 3d,
				2022y / November / 23d,
				2022y / December / 31d,

				2023y / January / 1d,
				2023y / January / 2d,
				2023y / January / 3d,
				2023y / January / 9d,
				2023y / February / 11d,
				2023y / February / 23d,
				2023y / March / 21d,
				2023y / April / 29d,
				2023y / May / 3d,
				2023y / May / 4d,
				2023y / May / 5d,
				2023y / July / 17d,
				2023y / August / 11d,
				2023y / September / 18d,
				2023y / September / 23d,
				2023y / October / 9d,
				2023y / November / 3d,
				2023y / November / 23d,
				2023y / December / 31d,

				2024y / January / 1d,
				2024y / January / 2d,
				2024y / January / 3d,
				2024y / January / 8d,
				2024y / February / 11d,
				2024y / February / 12d,
				2024y / February / 23d,
				2024y / March / 20d,
				2024y / April / 29d,
				2024y / May / 3d,
				2024y / May / 4d,
				2024y / May / 5d,
				2024y / May / 6d,
				2024y / July / 15d,
				2024y / August / 11d,
				2024y / August / 12d,
				2024y / September / 16d,
				2024y / September / 22d,
				2024y / September / 23d,
				2024y / October / 14d,
				2024y / November / 3d,
				2024y / November / 4d,
				2024y / November / 23d,
				2024y / December / 31d,

				2025y / January / 1d,
				2025y / January / 2d,
				2025y / January / 3d,
				2025y / January / 13d,
				2025y / February / 11d,
				2025y / February / 23d,
				2025y / February / 24d,
				2025y / March / 20d,
				2025y / April / 29d,
				2025y / May / 3d,
				2025y / May / 4d,
				2025y / May / 5d,
				2025y / May / 6d,
				2025y / July / 21d,
				2025y / August / 11d,
				2025y / September / 15d,
				2025y / September / 23d,
				2025y / October / 13d,
				2025y / November / 3d,
				2025y / November / 23d,
				2025y / November / 24d,
				2025y / December / 31d,

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
				days_period{ 2011y / FirstDayOfJanuary, 2027y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		auto make_Tokyo_calendar_versions() -> _calendar_versions
		{
			const auto known_part = _make_Tokyo_known_schedule_part0();

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