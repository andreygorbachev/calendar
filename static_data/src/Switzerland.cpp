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

		// https://www.zuerich.com/en/inform-plan/useful-information-and-services/opening-hours-and-public-holidays/feiertage

		// should these be in their own namespace?
		const auto _BerchtoldsDay = named_holiday{ January / 2d };
		const auto _LabourDay = named_holiday{ May / 1d };
		const auto _SwissNationalDay = named_holiday{ August / 1d };

		static auto _make_Zurich_known_schedule_part0() -> schedule // or should it be a "proper" function (without _)?
		{
			auto holidays = schedule::dates{ // should we include day of the week into comments?

				// Implied from SARON history

				// 1999 (partial 1999)

				// 2000
				2000y / April / 21d, // Friday
				2000y / April / 24d, // Monday
				2000y / May / 1d, // Monday
				2000y / June / 1d, // Thursday
				2000y / June / 12d, // Monday
				2000y / August / 1d, // Tuesday
				2000y / December / 25d, // Monday
				2000y / December / 26d, // Tuesday

				// 2001
				2001y / January / 1d, // Monday
				2001y / January / 2d, // Tuesday
				2001y / April / 13d, // Friday
				2001y / April / 16d, // Monday
				2001y / May / 1d, // Tuesday
				2001y / May / 24d, // Thursday
				2001y / June / 4d, // Monday
				2001y / August / 1d, // Wednesday
				2001y / December / 25d, // Tuesday
				2001y / December / 26d, // Wednesday

				// 2002
				2002y / January / 1d, // Tuesday
				2002y / January / 2d, // Wednesday
				2002y / March / 29d, // Friday
				2002y / April / 1d, // Monday
				2002y / May / 1d, // Wednesday
				2002y / May / 9d, // Thursday
				2002y / May / 20d, // Monday
				2002y / August / 1d, // Thursday
				2002y / December / 25d, // Wednesday
				2002y / December / 26d, // Thursday

				// 2003
				2003y / January / 1d, // Wednesday
				2003y / January / 2d, // Thursday
				2003y / April / 18d, // Friday
				2003y / April / 21d, // Monday
				2003y / May / 1d, // Thursday
				2003y / May / 29d, // Thursday
				2003y / June / 9d, // Monday
				2003y / August / 1d, // Friday
				2003y / December / 25d, // Thursday
				2003y / December / 26d, // Friday

				// 2004
				2004y / January / 1d, // Thursday
				2004y / January / 2d, // Friday
				2004y / April / 9d, // Friday
				2004y / April / 12d, // Monday
				2004y / May / 20d, // Thursday
				2004y / May / 31d, // Monday

				// 2005
				2005y / March / 25d, // Friday
				2005y / March / 28d, // Monday
				2005y / May / 5d, // Thursday
				2005y / May / 16d, // Monday
				2005y / August / 1d, // Monday
				2005y / December / 26d, // Monday

				// 2006
				2006y / January / 2d, // Monday
				2006y / April / 14d, // Friday
				2006y / April / 17d, // Monday
				2006y / May / 1d, // Monday
				2006y / May / 25d, // Thursday
				2006y / June / 5d, // Monday
				2006y / August / 1d, // Tuesday
				2006y / December / 25d, // Monday
				2006y / December / 26d, // Tuesday

				// 2007
				2007y / January / 1d, // Monday
				2007y / January / 2d, // Tuesday
				2007y / April / 6d, // Friday
				2007y / April / 9d, // Monday
				2007y / May / 1d, // Tuesday
				2007y / May / 17d, // Thursday
				2007y / May / 28d, // Monday
				2007y / August / 1d, // Wednesday
				2007y / December / 25d, // Tuesday
				2007y / December / 26d, // Wednesday

				// 2008
				2008y / January / 1d, // Tuesday
				2008y / January / 2d, // Wednesday
				2008y / March / 21d, // Friday
				2008y / March / 24d, // Monday
				2008y / May / 1d, // Thursday
				2008y / May / 12d, // Monday
				2008y / August / 1d, // Friday
				2008y / December / 25d, // Thursday
				2008y / December / 26d, // Friday

				// 2009
				2009y / January / 1d, // Thursday
				2009y / January / 2d, // Friday
				2009y / April / 10d, // Friday
				2009y / April / 13d, // Monday
				2009y / May / 1d, // Friday
				2009y / May / 21d, // Thursday
				2009y / June / 1d, // Monday
				2009y / December / 25d, // Friday

				// 2010
				2010y / January / 1d, // Friday
				2010y / April / 2d, // Friday
				2010y / April / 5d, // Monday
				2010y / May / 13d, // Thursday
				2010y / May / 24d, // Monday

				// 2011
				2011y / April / 22d, // Friday
				2011y / April / 25d, // Monday
				2011y / June / 2d, // Thursday
				2011y / June / 13d, // Monday
				2011y / August / 1d, // Monday
				2011y / December / 26d, // Monday

				// 2012
				2012y / January / 2d, // Monday
				2012y / April / 6d, // Friday
				2012y / April / 9d, // Monday
				2012y / May / 1d, // Tuesday
				2012y / May / 17d, // Thursday
				2012y / May / 28d, // Monday
				2012y / August / 1d, // Wednesday
				2012y / December / 25d, // Tuesday
				2012y / December / 26d, // Wednesday

				// 2013
				2013y / January / 1d, // Tuesday
				2013y / January / 2d, // Wednesday
				2013y / March / 29d, // Friday
				2013y / April / 1d, // Monday
				2013y / May / 1d, // Wednesday
				2013y / May / 9d, // Thursday
				2013y / May / 20d, // Monday
				2013y / August / 1d, // Thursday
				2013y / December / 25d, // Wednesday
				2013y / December / 26d, // Thursday

				// 2014
				2014y / January / 1d, // Wednesday
				2014y / January / 2d, // Thursday
				2014y / April / 18d, // Friday
				2014y / April / 21d, // Monday
				2014y / May / 1d, // Thursday
				2014y / May / 29d, // Thursday
				2014y / June / 9d, // Monday
				2014y / August / 1d, // Friday
				2014y / December / 25d, // Thursday
				2014y / December / 26d, // Friday

				// 2015
				2015y / January / 1d, // Thursday
				2015y / January / 2d, // Friday
				2015y / April / 3d, // Friday
				2015y / April / 6d, // Monday
				2015y / May / 1d, // Friday
				2015y / May / 14d, // Thursday
				2015y / May / 25d, // Monday
				2015y / December / 25d, // Friday

				// 2016
				2016y / January / 1d, // Friday
				2016y / March / 25d, // Friday
				2016y / March / 28d, // Monday
				2016y / May / 5d, // Thursday
				2016y / May / 16d, // Monday
				2016y / August / 1d, // Monday
				2016y / December / 26d, // Monday

				// 2017
				2017y / January / 2d, // Monday
				2017y / April / 14d, // Friday
				2017y / April / 17d, // Monday
				2017y / May / 1d, // Monday
				2017y / May / 25d, // Thursday
				2017y / June / 5d, // Monday
				2017y / August / 1d, // Tuesday
				2017y / December / 25d, // Monday
				2017y / December / 26d, // Tuesday

				// 2018
				2018y / January / 1d, // Monday
				2018y / January / 2d, // Tuesday
				2018y / March / 30d, // Friday
				2018y / April / 2d, // Monday
				2018y / May / 1d, // Tuesday
				2018y / May / 10d, // Thursday
				2018y / May / 21d, // Monday
				2018y / August / 1d, // Wednesday
				2018y / December / 25d, // Tuesday
				2018y / December / 26d, // Wednesday

				// 2019
				2019y / January / 1d, // Tuesday
				2019y / January / 2d, // Wednesday
				2019y / April / 19d, // Friday
				2019y / April / 22d, // Monday
				2019y / May / 1d, // Wednesday
				2019y / May / 30d, // Thursday
				2019y / June / 10d, // Monday
				2019y / August / 1d, // Thursday
				2019y / December / 25d, // Wednesday
				2019y / December / 26d, // Thursday

				// 2020
				2020y / January / 1d, // Wednesday
				2020y / January / 2d, // Thursday
				2020y / April / 10d, // Friday
				2020y / April / 13d, // Monday
				2020y / May / 1d, // Friday
				2020y / May / 21d, // Thursday
				2020y / June / 1d, // Monday
				2020y / December / 25d, // Friday

				// 2021
				2021y / January / 1d, // Friday
				2021y / April / 2d, // Friday
				2021y / April / 5d, // Monday
				2021y / May / 13d, // Thursday
				2021y / May / 24d, // Monday

				// 2022
				2022y / April / 15d, // Friday
				2022y / April / 18d, // Monday
				2022y / May / 26d, // Thursday
				2022y / June / 6d, // Monday
				2022y / August / 1d, // Monday
				2022y / December / 26d, // Monday

				// 2023
				2023y / January / 2d, // Monday
				2023y / April / 7d, // Friday
				2023y / April / 10d, // Monday
				2023y / May / 1d, // Monday
				2023y / May / 18d, // Thursday
				2023y / May / 29d, // Monday
				2023y / August / 1d, // Tuesday
				2023y / December / 25d, // Monday
				2023y / December / 26d, // Tuesday

				2024y / January / 1d, // New Year's Day
				2024y / January / 2d, // Berchtholdstag
				2024y / March / 29d, // Good Friday
				2024y / April / 1d, // Easter Monday
				2024y / May / 1d, // Labour Day
				2024y / May / 9d, // Ascension Day
				2024y / May / 20d, // Whitmonday
				2024y / August / 1d, // National Day
//				2024y / December / 24d, // Christmas Eve
				2024y / December / 25d, // Christmas
				2024y / December / 26d, // St. Stephen's Day
//				2024y / December / 31d, // New Year's Eve

				2025y / January / 1d, // New Year's Day
				2025y / January / 2d, // Berchtholdstag
				2025y / April / 18d, // Good Friday
				2025y / April / 21d, // Easter Monday
				2025y / May / 1d, // Labour Day
				2025y / May / 29d, // Ascension Day
				2025y / June / 9d, // Whitmonday
				2025y / August / 1d, // National Day
//				2025y / December / 24d, // Christmas Eve
				2025y / December / 25d, // Christmas
				2025y / December / 26d, // St. Stephen's Day
//				2025y / December / 31d, // New Year's Eve

				2026y / January / 1d, // New Year's Day
				2026y / January / 2d, // Berchtholdstag
				2026y / April / 3d, // Good Friday
				2026y / April / 6d, // Easter Monday
				2026y / May / 1d, // Labour Day
				2026y / May / 14d, // Ascension Day
				2026y / May / 25d, // Whitmonday
//				2026y / December / 24d, // Christmas Eve
				2026y / December / 25d, // Christmas
//				2026y / December / 31d, // New Year's Eve
			};

			return schedule{
				days_period{ 1999y / FirstDayOfJanuary, 2026y / LastDayOfDecember },
				std::move(holidays)
			};
		}

		static auto _make_Zurich_generated_schedule_part0() -> schedule
		{
			const auto rules = annual_holiday_storage{
				&NewYearsDay,
				&_BerchtoldsDay,
				&GoodFriday,
				&EasterMonday,
				// Sechseläuten (afternoon only)
				&_LabourDay,
				&AscensionDay,
				&WhitMonday,
				&_SwissNationalDay,
				// Knabenschiessen (afternoon only)
				&ChristmasDay,
				&BoxingDay, // St.Stephen’s Day
				// &NewYearsEve // Most businesses in Zurich are open on New Year’s Eve but usually shut between 4 PM and 6 PM.
			};

			return make_holiday_schedule(
				util::years_period{ 2027y, Epoch.get_until().year() },
				rules
			);
		}


		auto make_Zurich_calendar_versions() -> _calendar_versions
		{
			auto cal0 = calendar{
				SaturdaySundayWeekend,
				_make_Zurich_known_schedule_part0() +
				_make_Zurich_generated_schedule_part0()
			};

			return {
				{ cal0.get_schedule().get_period().get_from(), std::move(cal0) },
			};
		}

	}

}