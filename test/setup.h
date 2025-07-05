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

#pragma once

#include <utility>

#include <period.h>

#include <schedule.h>
#include <annual_holidays.h>
#include <calendar.h>
#include <business_day_adjusters.h>


namespace gregorian
{

	inline auto _make_holiday_schedule_england() -> schedule
	{
		using namespace std::chrono;

		auto holidays = schedule::dates{
			year{ 2018 } / January / day{ 1u },
			year{ 2018 } / March / day{ 30u },
			year{ 2018 } / April / day{ 2u },
			year{ 2018 } / May / day{ 7u },
			year{ 2018 } / May / day{ 28u },
			year{ 2018 } / August / day{ 27u },
			year{ 2018 } / December / day{ 25u },
			year{ 2018 } / December / day{ 26u },

			year{ 2019 } / January / day{ 1u },
			year{ 2019 } / April / day{ 19u },
			year{ 2019 } / April / day{ 22u },
			year{ 2019 } / May / day{ 6u },
			year{ 2019 } / May / day{ 27u },
			year{ 2019 } / August / day{ 26u },
			year{ 2019 } / December / day{ 25u },
			year{ 2019 } / December / day{ 26u },

			year{ 2020 } / January / day{ 1u },
			year{ 2020 } / April / day{ 10u },
			year{ 2020 } / April / day{ 13u },
			year{ 2020 } / May / day{ 8u },
			year{ 2020 } / May / day{ 25u },
			year{ 2020 } / August / day{ 31u },
			year{ 2020 } / December / day{ 25u },
			year{ 2020 } / December / day{ 28u },

			year{ 2021 } / January / day{ 1u },
			year{ 2021 } / April / day{ 2u },
			year{ 2021 } / April / day{ 5u },
			year{ 2021 } / May / day{ 3u },
			year{ 2021 } / May / day{ 31u },
			year{ 2021 } / August / day{ 30u },
			year{ 2021 } / December / day{ 27u },
			year{ 2021 } / December / day{ 28u },

			year{ 2022 } / January / day{ 3u },
			year{ 2022 } / April / day{ 15u },
			year{ 2022 } / April / day{ 18u },
			year{ 2022 } / May / day{ 2u },
			year{ 2022 } / June / day{ 2u },
			year{ 2022 } / June / day{ 3u },
			year{ 2022 } / August / day{ 29u },
			year{ 2022 } / September / day{ 19u },
			year{ 2022 } / December / day{ 26u },
			year{ 2022 } / December / day{ 27u },

			year{ 2023 } / January / day{ 2u },
			year{ 2023 } / April / day{ 7u },
			year{ 2023 } / April / day{ 10u },
			year{ 2023 } / May / day{ 1u },
			year{ 2023 } / May / day{ 8u },
			year{ 2023 } / May / day{ 29u },
			year{ 2023 } / August / day{ 28u },
			year{ 2023 } / December / day{ 25u },
			year{ 2023 } / December / day{ 26u },
		};

		return schedule{
			util::days_period{ year{ 2018 } / gregorian::FirstDayOfJanuary, year{ 2023 } / gregorian::LastDayOfDecember },
			std::move(holidays)
		};
	}

	inline auto make_holiday_schedule_england() -> const schedule&
	{
		static const auto s = _make_holiday_schedule_england();

		return s;
	}

	inline auto _make_calendar_england() -> calendar
	{
		using namespace std::chrono;

		const auto known_part = _make_holiday_schedule_england();

		const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
		const auto generated_part_until = generated_part_from + years{ 10 }; // factor out this const

		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
		const auto SummerBankHoliday = weekday_last_holiday{ August / Monday[last] };

		const auto rules = annual_holiday_storage{
			&NewYearsDay,
			&GoodFriday,
			&EasterMonday,
			&EarlyMayBankHoliday,
			&SpringBankHoliday,
			&SummerBankHoliday,
			&ChristmasDay,
			&BoxingDay
		};

		const auto generated_part = make_holiday_schedule(
			util::years_period{ generated_part_from, generated_part_until },
			rules
		);

		// setup a calendar for the generated part only (to do substitution for the generated dates)
		auto cal = calendar{
			SaturdaySundayWeekend,
			generated_part
		};
		cal.substitute(Following);

		return calendar{
			SaturdaySundayWeekend,
			known_part + cal.get_schedule()
		};
	}

	inline auto make_calendar_england() -> const calendar&
	{
		static const auto s = _make_calendar_england();
		return s;
	}

	inline auto _make_calendar_starts_ends_with_holidays() -> calendar
	{
		using namespace std::chrono;

		auto hols = schedule::dates{
			2024y / FirstDayOfJanuary,
			2024y / LastDayOfDecember,
		};
		auto s = schedule{ util::days_period{ 2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, std::move(hols) };
		return calendar{ NoWeekend, std::move(s) };
	}

	inline auto make_calendar_starts_ends_with_holidays() -> const calendar&
	{
		static const auto s = _make_calendar_starts_ends_with_holidays();
		return s;
	}

	inline auto _make_calendar_all_holidays() -> calendar
	{
		using namespace std::chrono;

		auto s = schedule{ util::days_period{
			2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember },
			schedule::dates{}
		};
		return calendar{ NoWeekend, ~s };
	}

	inline auto make_calendar_all_holidays() -> const calendar&
	{
		static const auto s = _make_calendar_all_holidays();
		return s;
	}


	inline auto make_mpc_dates_may_2023() -> schedule
	{
		using namespace std::chrono;

		auto meeting_dates = schedule::dates{
			2023y / May / 11d, // May MPC Summary and minutes and May Monetary Policy Report
		};

		return schedule{ util::days_period{ 2023y / May / 1d, 2023y / May / 31d }, std::move(meeting_dates) };
	}


	inline auto make_holiday_schedule_england_april_2023() -> schedule
	{
		using namespace std::chrono;

		auto hols = schedule::dates{
			2023y / April / 7d,
			2023y / April / 10d,
		};

		return schedule{ util::days_period{ 2023y / April / 1d, 2023y / April / 30d }, std::move(hols) };
	}

	inline auto make_holiday_schedule_england_may_2023() -> schedule
	{
		using namespace std::chrono;

		auto hols = schedule::dates{
			2023y / May / 1d,
			2023y / May / 8d,
			2023y / May / 29d,
		};

		return schedule{ util::days_period{ 2023y / May / 1d, 2023y / May / 31d }, std::move(hols) };
	}

	inline auto make_holiday_schedule_united_states_may_2023() -> schedule
	{
		using namespace std::chrono;

		auto hols = schedule::dates{
			2023y / May / 29d,
		};

		return schedule{ util::days_period{ 2023y / May / 1d, 2023y / May / 31d }, std::move(hols) };
	}

}
