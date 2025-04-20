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

#include <schedule.h>
#include <annual_holidays.h>
#include <calendar.h>
#include <business_day_conventions.h>


namespace business_day_convention
{

	inline auto _make_holiday_schedule_united_states() -> gregorian::schedule
	{
		using namespace std::chrono;
		using namespace gregorian;

		const auto MartinLutherKing = weekday_indexed_holiday{ January / Monday[3] }; // Birthday Of Martin Luther King, Jr.
		const auto Washington = weekday_indexed_holiday{ February / Monday[3] }; // Washington's Birthday
		const auto MemorialDay = weekday_last_holiday{ May / Monday[last] };
		const auto Juneteenth = named_holiday{ June / day{ 19u } }; // Juneteenth National Independence Day
		const auto IndependenceDay = named_holiday{ July / day{ 4u } };
		const auto LaborDay = weekday_indexed_holiday{ September / Monday[1] };
		const auto ColumbusDay = weekday_indexed_holiday{ October / Monday[2] };
		const auto VeteransDay = named_holiday{ November / day{ 11u } };
		const auto ThanksgivingDay = weekday_indexed_holiday{ November / Thursday[4] };

		const auto rules = annual_holiday_storage{
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

		const auto InaugurationDay = named_holiday{ January / day{ 20u } };

		const auto rules2 = annual_holiday_storage{
			&NewYearsDay,
			&MartinLutherKing,
			&InaugurationDay, // what if it is the same as MartinLutherKing?
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

		const auto hs2021 = make_holiday_schedule(
			year{ 2021 },
			rules2
		);

		const auto hs2022_2024 = make_holiday_schedule(
			years_period{ year{ 2022 }, year{ 2024 } },
			rules
		);

		const auto hs2025 = make_holiday_schedule(
			year{ 2025 },
			rules2
		);

		const auto hs2026_2028 = make_holiday_schedule(
			years_period{ year{ 2026 }, year{ 2028 } },
			rules
		);

		const auto hs2029 = make_holiday_schedule(
			year{ 2029 },
			rules//rules2
		);

		const auto hs2030 = make_holiday_schedule(
			year{ 2030 },
			rules
		);

		return hs2021 + hs2022_2024 + hs2025 + hs2026_2028 + hs2029 + hs2030;
	}

	inline auto make_holiday_schedule_united_states() -> const gregorian::schedule&
	{
		static const auto s = _make_holiday_schedule_united_states();

		return s;
	}


	inline auto _make_calendar_united_states() -> gregorian::calendar
	{
		auto c = gregorian::calendar{ gregorian::SaturdaySundayWeekend, make_holiday_schedule_united_states() };
		c.substitute(gregorian::Nearest);

		return c;
	}

	inline auto make_calendar_united_states() -> const gregorian::calendar&
	{
		static const auto c = _make_calendar_united_states();

		return c;
	}


	inline auto _make_holiday_schedule_england() -> gregorian::schedule
	{
		using namespace std::chrono;
		using namespace gregorian;

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
			days_period{ year{ 2018 } / gregorian::FirstDayOfJanuary, year{ 2023 } / gregorian::LastDayOfDecember },
			std::move(holidays)
		};
	}

	inline auto make_holiday_schedule_england() -> const gregorian::schedule&
	{
		static const auto s = _make_holiday_schedule_england();

		return s;
	}

	inline auto _make_calendar_england() -> gregorian::calendar
	{
		using namespace std::chrono;
		using namespace gregorian;

		const auto known_part = _make_holiday_schedule_england();

		const auto generated_part_from = known_part.get_from_until().get_until().year() + years{ 1 };
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
			years_period{ generated_part_from, generated_part_until },
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

	inline auto make_calendar_england() -> const gregorian::calendar&
	{
		static const auto s = _make_calendar_england();
		return s;
	}

	inline auto _make_calendar_starts_ends_with_holidays() -> gregorian::calendar
	{
		using namespace std;
		using namespace std::chrono;
		using namespace gregorian;

		auto hols = schedule::dates{
			2024y / FirstDayOfJanuary,
			2024y / LastDayOfDecember,
		};
		auto s = schedule{ days_period{ 2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, move(hols) };
		return calendar{ NoWeekend, move(s) };
	}

	inline auto make_calendar_starts_ends_with_holidays() -> const gregorian::calendar&
	{
		static const auto s = _make_calendar_starts_ends_with_holidays();
		return s;
	}

	inline auto _make_calendar_all_holidays() -> gregorian::calendar
	{
		using namespace std;
		using namespace std::chrono;
		using namespace gregorian;

		auto s = schedule{ days_period{
			2024y / FirstDayOfJanuary, 2024y / LastDayOfDecember },
			schedule::dates{}
		};
		return calendar{ NoWeekend, ~s };
	}

	inline auto make_calendar_all_holidays() -> const gregorian::calendar&
	{
		static const auto s = _make_calendar_all_holidays();
		return s;
	}


	// from: https://www.bankofengland.co.uk/monetary-policy/upcoming-mpc-dates
	inline auto make_mpc_schedule_2023_2024() -> gregorian::schedule // should this also be an example?
	{
		using namespace std;
		using namespace std::chrono;
		using namespace gregorian;

		auto meeting_dates = schedule::dates{
			// 2023 confirmed dates
			2023y / February / 2d, // February MPC Summary and minutes and February Monetary Policy Report
			2023y / March / 23d, // March MPC Summary and minutes
			2023y / May / 11d, // May MPC Summary and minutes and May Monetary Policy Report
			2023y / June / 22d, // June MPC Summary and minutes
			2023y / August / 3d, // August MPC Summary and minutes and August Monetary Policy Report
			2023y / September / 21d, // September MPC Summary and minutes
			2023y / November / 2d, // November MPC Summary and minutes and November Monetary Policy Report
			2023y / December / 14d, // December MPC Summary and minutes
			// 2024 provisional dates
			2024y / February / 1d, //February MPC Summary and minutes and February Monetary Policy Report
			2024y / March / 21d, // March MPC Summary and minutes
			2024y / May	/ 9d, // May MPC Summary and minutes and May Monetary Policy Report
			2024y / June / 20d, // June MPC Summary and minutes
			2024y / August / 1d, // August MPC Summary and minutes and August Monetary Policy Report
			2024y / September / 19d, // September MPC Summary and minutes
			2024y / November / 7d, // November MPC Summary and minutes and November Monetary Policy Report
			2024y / December / 19d, // December MPC Summary and minutes
		};

		return schedule{ days_period{ 2023y / FirstDayOfJanuary, 2024y / LastDayOfDecember }, move(meeting_dates) };
	}

	inline auto make_mpc_holiday_schedule_2023_2024() -> gregorian::schedule
	{
		return ~make_mpc_schedule_2023_2024();
	}


	inline auto make_holiday_schedule_england_april_2023() -> gregorian::schedule
	{
		using namespace std;
		using namespace std::chrono;
		using namespace gregorian;

		auto hols = schedule::dates{
			2023y / April / 7d,
			2023y / April / 10d,
		};

		return schedule{ days_period{ 2023y / April / 1d, 2023y / April / 30d }, move(hols) };
	}

	inline auto make_holiday_schedule_england_may_2023() -> gregorian::schedule
	{
		using namespace std;
		using namespace std::chrono;
		using namespace gregorian;

		auto hols = schedule::dates{
			2023y / May / 1d,
			2023y / May / 8d,
			2023y / May / 29d,
		};

		return schedule{ days_period{ 2023y / May / 1d, 2023y / May / 31d }, move(hols) };
	}

	inline auto make_holiday_schedule_united_states_may_2023() -> gregorian::schedule
	{
		using namespace std;
		using namespace std::chrono;
		using namespace gregorian;

		auto hols = schedule::dates{
			2023y / May / 29d,
		};

		return schedule{ days_period{ 2023y / May / 1d, 2023y / May / 31d }, move(hols) };
	}

}
