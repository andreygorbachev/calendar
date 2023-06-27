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


namespace gregorian
{

	inline auto _make_holiday_schedule_england() -> schedule
	{
		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto SummerBankHoliday = weekday_last_holiday{ std::chrono::August / std::chrono::Monday[std::chrono::last] };

		auto rules = annual_holiday_storage{};
		rules.insert(&NewYearsDay);
		rules.insert(&GoodFriday);
		rules.insert(&EasterMonday);
		rules.insert(&EarlyMayBankHoliday);
		rules.insert(&SpringBankHoliday);
		rules.insert(&SummerBankHoliday);
		rules.insert(&ChristmasDay);
		rules.insert(&BoxingDay);

		const auto hs2018_2019 = make_holiday_schedule(
			{ std::chrono::year{ 2018 }, std::chrono::year{ 2019 } },
			rules
		);

		const auto VictoryInEuropeDay = named_holiday{ std::chrono::May / std::chrono::day{ 8u } };

		auto rules2020 = annual_holiday_storage{};
		rules2020.insert(&NewYearsDay);
		rules2020.insert(&GoodFriday);
		rules2020.insert(&EasterMonday);
		rules2020.insert(&VictoryInEuropeDay);
		rules2020.insert(&SpringBankHoliday);
		rules2020.insert(&SummerBankHoliday);
		rules2020.insert(&ChristmasDay);
		rules2020.insert(&BoxingDay);

		const auto hs2020 = make_holiday_schedule(
			std::chrono::year{ 2020 },
			rules2020
		);

		const auto hs2021 = make_holiday_schedule(
			std::chrono::year{ 2021 },
			rules
		);

		const auto SpringBankHoliday2 = named_holiday{ std::chrono::June / std::chrono::day{ 2u } };
		const auto PlatinumJubileeHoliday = named_holiday{ std::chrono::June / std::chrono::day{ 3u } };
		const auto StateFuneral = named_holiday{ std::chrono::September / std::chrono::day{ 19u } }; // Bank Holiday for the State Funeral of Queen Elizabeth II

		auto rules2022 = annual_holiday_storage{};
		rules2022.insert(&NewYearsDay);
		rules2022.insert(&GoodFriday);
		rules2022.insert(&EasterMonday);
		rules2022.insert(&EarlyMayBankHoliday);
		rules2022.insert(&SpringBankHoliday2);
		rules2022.insert(&PlatinumJubileeHoliday);
		rules2022.insert(&SummerBankHoliday);
		rules2022.insert(&StateFuneral);
		rules2022.insert(&ChristmasDay);
		rules2022.insert(&BoxingDay);

		const auto hs2022 = make_holiday_schedule(
			std::chrono::year{ 2022 },
			rules2022
		);

		const auto Coronation = named_holiday{ std::chrono::May / std::chrono::day{ 8u } }; // Bank holiday for the coronation of King Charles III

		auto rules2023 = annual_holiday_storage{};
		rules2023.insert(&NewYearsDay);
		rules2023.insert(&GoodFriday);
		rules2023.insert(&EasterMonday);
		rules2023.insert(&EarlyMayBankHoliday);
		rules2023.insert(&Coronation);
		rules2023.insert(&SpringBankHoliday);
		rules2023.insert(&SummerBankHoliday);
		rules2023.insert(&ChristmasDay);
		rules2023.insert(&BoxingDay);

		const auto hs2023 = make_holiday_schedule(
			std::chrono::year{ 2023 },
			rules2023
		);

		const auto hs2024_2025 = make_holiday_schedule(
			{ std::chrono::year{ 2024 }, std::chrono::year{ 2025 } },
			rules
		);

		return hs2018_2019 + hs2020 + hs2021 + hs2022 + hs2023 + hs2024_2025;
	}

	inline auto make_holiday_schedule_england() -> const schedule&
	{
		static const auto s = _make_holiday_schedule_england();

		return s;
	}


	inline auto _make_holiday_schedule_united_states() -> schedule
	{
		const auto MartinLutherKing = weekday_indexed_holiday{ std::chrono::January / std::chrono::Monday[3] }; // Birthday Of Martin Luther King, Jr.
		const auto Washington = weekday_indexed_holiday{ std::chrono::February / std::chrono::Monday[3] }; // Washington's Birthday
		const auto MemorialDay = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto Juneteenth = named_holiday{ std::chrono::June / std::chrono::day{ 19u } }; // Juneteenth National Independence Day
		const auto IndependenceDay = named_holiday{ std::chrono::July / std::chrono::day{ 4u } };
		const auto LaborDay = weekday_indexed_holiday{ std::chrono::September / std::chrono::Monday[1] };
		const auto ColumbusDay = weekday_indexed_holiday{ std::chrono::October / std::chrono::Monday[2] };
		const auto VeteransDay = named_holiday{ std::chrono::November / std::chrono::day{ 11u } };
		const auto ThanksgivingDay = weekday_indexed_holiday{ std::chrono::November / std::chrono::Thursday[4] };

		auto rules = annual_holiday_storage{};
		rules.insert(&NewYearsDay);
		rules.insert(&MartinLutherKing);
		rules.insert(&Washington);
		rules.insert(&MemorialDay);
		rules.insert(&Juneteenth);
		rules.insert(&IndependenceDay);
		rules.insert(&LaborDay);
		rules.insert(&ColumbusDay);
		rules.insert(&VeteransDay);
		rules.insert(&ThanksgivingDay);
		rules.insert(&ChristmasDay);

		const auto InaugurationDay = named_holiday{ std::chrono::January / std::chrono::day{ 20u } };

		auto rules2 = annual_holiday_storage{};
		rules2.insert(&NewYearsDay);
		rules2.insert(&MartinLutherKing);
		rules2.insert(&InaugurationDay); // what if it is the same as MartinLutherKing?
		rules2.insert(&Washington);
		rules2.insert(&MemorialDay);
		rules2.insert(&Juneteenth);
		rules2.insert(&IndependenceDay);
		rules2.insert(&LaborDay);
		rules2.insert(&ColumbusDay);
		rules2.insert(&VeteransDay);
		rules2.insert(&ThanksgivingDay);
		rules2.insert(&ChristmasDay);

		const auto hs2021 = make_holiday_schedule(
			std::chrono::year{ 2021 },
			rules2
		);

		const auto hs2022_2024 = make_holiday_schedule(
			{ std::chrono::year{ 2022 }, std::chrono::year{ 2024 } },
			rules
		);

		const auto hs2025 = make_holiday_schedule(
			std::chrono::year{ 2025 },
			rules2
		);

		const auto hs2026_2028 = make_holiday_schedule(
			{ std::chrono::year{ 2026 }, std::chrono::year{ 2028 } },
			rules
		);

		const auto hs2029 = make_holiday_schedule(
			std::chrono::year{ 2029 },
			rules//rules2
		);

		const auto hs2030 = make_holiday_schedule(
			std::chrono::year{ 2030 },
			rules
		);

		return hs2021 + hs2022_2024 + hs2025 + hs2026_2028 + hs2029 + hs2030;
	}

	inline auto make_holiday_schedule_united_states() -> const schedule&
	{
		static const auto s = _make_holiday_schedule_united_states();

		return s;
	}


	inline auto _make_calendar_england() -> calendar
	{
		auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_england() };
		c.substitute(&Following);

		return c;
	}

	inline auto make_calendar_england() -> const calendar&
	{
		static const auto c = _make_calendar_england();

		return c;
	}


	inline auto _make_calendar_united_states() -> calendar
	{
		auto c = calendar{ SaturdaySundayWeekend, make_holiday_schedule_united_states() };
		c.substitute(&Nearest);

		return c;
	}

	inline auto make_calendar_united_states() -> const calendar&
	{
		static const auto c = _make_calendar_united_states();

		return c;
	}



	inline auto make_holiday_schedule_england_april_2023() -> schedule
	{
		using namespace std::chrono;

		auto hols = schedule::storage{
			2023y / April / 7d,
			2023y / April / 10d,
		};

		return schedule{ { 2023y / April / 1d, 2023y / April / 30d }, std::move(hols) };
	}

	inline auto make_holiday_schedule_england_may_2023() -> schedule
	{
		using namespace std::chrono;

		auto hols = schedule::storage{
			2023y / May / 1d,
			2023y / May / 8d,
			2023y / May / 29d,
		};

		return schedule{ { 2023y / May / 1d, 2023y / May / 31d }, std::move(hols) };
	}

	inline auto make_holiday_schedule_united_states_may_2023() -> schedule
	{
		using namespace std::chrono;

		auto hols = schedule::storage{
			2023y / May / 29d,
		};

		return schedule{ { 2023y / May / 1d, 2023y / May / 31d }, std::move(hols) };
	}


	// from: https://www.bankofengland.co.uk/monetary-policy/upcoming-mpc-dates
	inline auto make_mpc_schedule_2023_2024() -> schedule
	{
		using namespace std::chrono;

		auto meeting_dates = schedule::storage{
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

		return schedule{ { 2023y / January / 1d, 2024y / December / 31d }, std::move(meeting_dates) };
	}

	inline auto make_mpc_holiday_schedule_2023_2024() -> schedule
	{
		return ~make_mpc_schedule_2023_2024();
	}
	
}
