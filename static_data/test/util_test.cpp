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

#include <gtest/gtest.h>

#include <util.h>
#include <makers.h>
#include <static_data.h>

#include <period.h>
#include <schedule.h>
#include <annual_holidays.h>

#include <chrono>
#include <stdexcept>
#include <optional>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	using namespace util;

	namespace static_data
	{

		TEST(util, make_generated_period1)
		{
			// common case: we have both known and generated periods
			// knwon from is the same as Epoch from
			// and knwon until is before Epoch until

			const auto known_period = days_period{
				Epoch.get_from(),
				2025y / LastDayOfDecember
			};

			const auto generated_period = make_generated_period(
				known_period,
				Epoch
			);

			EXPECT_TRUE(generated_period.has_value());
			EXPECT_EQ(Epoch, known_period + *generated_period);
		}

		TEST(util, make_generated_period2)
		{
			// known period is before the Epoch from
			// (we do not allow such case and it should throw)

			const auto known_period = days_period{
				Epoch.get_from() - years{ 1 },
				2025y / LastDayOfDecember
			};

			EXPECT_THROW(make_generated_period(known_period, Epoch), out_of_range);
		}

		TEST(util, make_generated_period3)
		{
			// known until is after Epoch until

			const auto known_period = days_period{
				Epoch.get_from(),
				Epoch.get_until() + years{ 1 }
			};

			const auto generated_period = make_generated_period(
				known_period,
				Epoch
			);

			EXPECT_FALSE(generated_period.has_value());
		}

		TEST(util, make_generated_period4)
		{
			// known until is before Epoch from

			const auto known_period = days_period{
				Epoch.get_from() - years{ 2 },
				Epoch.get_from() - years{ 1 }
			};

			const auto generated_period = make_generated_period(
				known_period,
				Epoch
			);

			EXPECT_TRUE(generated_period.has_value());
			EXPECT_EQ(Epoch, *generated_period);
		}

		TEST(util, make_generated_period5)
		{
			// no known period

			const auto generated_period = make_generated_period(
				nullopt,
				Epoch
			);

			EXPECT_TRUE(generated_period.has_value());
			EXPECT_EQ(Epoch, *generated_period);
		}



		TEST(util, make_generated_sub_periods_as_of_date1)
		{
			const auto hol1 = named_holiday{ January / 1d };
			const auto hol2 = named_holiday{ January / 2d };

			const auto hol2_announcement = 2025y / January / 1d;
			const auto hol2_period = period{
				2026y / FirstDayOfJanuary,
				2026y / LastDayOfDecember,
			};

			const auto rules = _annual_holiday_period_storage{
				{
					&hol1,
					Epoch,
					Epoch.get_from()
				},
				{
					&hol2,
					hol2_period,
					hol2_announcement
				}
			};

			const auto periods1 = make_generated_sub_periods_as_of_date(
				rules,
				Epoch.get_from()
			);
			EXPECT_EQ(1u, periods1.size());
			// add an actual check that we only have Epoch here

			const auto periods2 = make_generated_sub_periods_as_of_date(
				rules,
				hol2_announcement
			);
			EXPECT_EQ(3u, periods2.size());
			// add an actual check of what we got

			const auto periods3 = make_generated_sub_periods_as_of_date(
				rules,
				2027y / January / 1d
			);
			EXPECT_EQ(3u, periods3.size()); // at this point we do not have a konwn part, so need to generate all historial periods
			// add an actual check of what we got
		}


		TEST(util, make_holiday_schedule_as_of_date1)
		{
			const auto hol1 = named_holiday{ January / 1d };
			const auto hol2 = named_holiday{ January / 2d };

			const auto hol2_announcement = 2025y / January / 1d;
			const auto hol2_period = period{
				2026y / FirstDayOfJanuary,
				2026y / LastDayOfDecember,
			};

			const auto rules = _annual_holiday_period_storage{
				{
					&hol1,
					Epoch,
					Epoch.get_from()
				},
				{
					&hol2,
					hol2_period,
					hol2_announcement
				}
			};

			const auto rules_as_of_date = make_holiday_schedule_as_of_date(
				rules,
				Epoch.get_from()
			);
		}

	}

}
