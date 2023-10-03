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
// give this file a more distinct name? separate files per country?
// separate namespace? namespaces (per country)?
// separate library? (maybe not header only?)

#include "calendar.h"
#include "schedule.h"
#include "annual_holidays.h"
#include "weekend.h"
#include "business_day_conventions.h"

#include <chrono>
#include <memory>


namespace gregorian
{

	const auto Epoch = std::chrono::year{ 2018 } / std::chrono::January / std::chrono::day{ 1u };
	// all calendars should include holidays from at least this day


	// from https://www.gov.uk/bank-holidays

	inline auto _England_schedule() -> schedule // or should it be a "proper" function (without _)?
	{
		auto holidays = schedule::storage{
			std::chrono::year{ 2018 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2018 } / std::chrono::March / std::chrono::day{ 30u },
			std::chrono::year{ 2018 } / std::chrono::April / std::chrono::day{ 2u },
			std::chrono::year{ 2018 } / std::chrono::May / std::chrono::day{ 7u },
			std::chrono::year{ 2018 } / std::chrono::May / std::chrono::day{ 28u },
			std::chrono::year{ 2018 } / std::chrono::August / std::chrono::day{ 27u },
			std::chrono::year{ 2018 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2018 } / std::chrono::December / std::chrono::day{ 26u },

			std::chrono::year{ 2019 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2019 } / std::chrono::April / std::chrono::day{ 19u },
			std::chrono::year{ 2019 } / std::chrono::April / std::chrono::day{ 22u },
			std::chrono::year{ 2019 } / std::chrono::May / std::chrono::day{ 6u },
			std::chrono::year{ 2019 } / std::chrono::May / std::chrono::day{ 27u },
			std::chrono::year{ 2019 } / std::chrono::August / std::chrono::day{ 26u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 26u },

			std::chrono::year{ 2020 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2020 } / std::chrono::April / std::chrono::day{ 10u },
			std::chrono::year{ 2020 } / std::chrono::April / std::chrono::day{ 13u },
			std::chrono::year{ 2020 } / std::chrono::May / std::chrono::day{ 8u },
			std::chrono::year{ 2020 } / std::chrono::May / std::chrono::day{ 25u },
			std::chrono::year{ 2020 } / std::chrono::August / std::chrono::day{ 31u },
			std::chrono::year{ 2020 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2020 } / std::chrono::December / std::chrono::day{ 28u },

			std::chrono::year{ 2021 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2021 } / std::chrono::April / std::chrono::day{ 2u },
			std::chrono::year{ 2021 } / std::chrono::April / std::chrono::day{ 5u },
			std::chrono::year{ 2021 } / std::chrono::May / std::chrono::day{ 3u },
			std::chrono::year{ 2021 } / std::chrono::May / std::chrono::day{ 31u },
			std::chrono::year{ 2021 } / std::chrono::August / std::chrono::day{ 30u },
			std::chrono::year{ 2021 } / std::chrono::December / std::chrono::day{ 27u },
			std::chrono::year{ 2021 } / std::chrono::December / std::chrono::day{ 28u },

			std::chrono::year{ 2022 } / std::chrono::January / std::chrono::day{ 3u },
			std::chrono::year{ 2022 } / std::chrono::April / std::chrono::day{ 15u },
			std::chrono::year{ 2022 } / std::chrono::April / std::chrono::day{ 18u },
			std::chrono::year{ 2022 } / std::chrono::May / std::chrono::day{ 2u },
			std::chrono::year{ 2022 } / std::chrono::June / std::chrono::day{ 2u },
			std::chrono::year{ 2022 } / std::chrono::June / std::chrono::day{ 3u },
			std::chrono::year{ 2022 } / std::chrono::August / std::chrono::day{ 29u },
			std::chrono::year{ 2022 } / std::chrono::September / std::chrono::day{ 19u },
			std::chrono::year{ 2022 } / std::chrono::December / std::chrono::day{ 26u },
			std::chrono::year{ 2022 } / std::chrono::December / std::chrono::day{ 27u },

			std::chrono::year{ 2023 } / std::chrono::January / std::chrono::day{ 2u },
			std::chrono::year{ 2023 } / std::chrono::April / std::chrono::day{ 7u },
			std::chrono::year{ 2023 } / std::chrono::April / std::chrono::day{ 10u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 1u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 8u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 29u },
			std::chrono::year{ 2023 } / std::chrono::August / std::chrono::day{ 28u },
			std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 26u },
		};

		return schedule{
			days_period{ Epoch, std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 31u } },
			std::move(holidays)
		};
	}

	inline auto _make_England_calendar() -> calendar
	{
		const auto known_part = _England_schedule();

		const auto generated_part_from = known_part.get_from_until().get_until().year();
		const auto generated_part_until = generated_part_from + std::chrono::years{ 10 }; // factor out this const

		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto SummerBankHoliday = weekday_last_holiday{ std::chrono::August / std::chrono::Monday[std::chrono::last] };

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
			{ generated_part_from, generated_part_until },
			rules
		);

		// setup a calendar for the generated part only (to do substitution for the generated dates)
		// do we need operator+ for calendar instead?
		auto cal = calendar{
			SaturdaySundayWeekend,
			generated_part
		};
		cal.substitute(&Following);

		return calendar{
			SaturdaySundayWeekend,
			known_part + cal.get_holiday_schedule()
		};
	}

	inline auto make_England_calendar() -> const calendar&
	{
		static const auto s = _make_England_calendar();
		return s;
	}



	inline auto make_Wales_calendar() -> const calendar&
	{
		return make_England_calendar();
	}



	inline auto _Scotland_schedule() -> schedule
	{
		auto holidays = schedule::storage{
			std::chrono::year{ 2018 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2018 } / std::chrono::January / std::chrono::day{ 2u },
			std::chrono::year{ 2018 } / std::chrono::March / std::chrono::day{ 30u },
			std::chrono::year{ 2018 } / std::chrono::May / std::chrono::day{ 7u },
			std::chrono::year{ 2018 } / std::chrono::May / std::chrono::day{ 28u },
			std::chrono::year{ 2018 } / std::chrono::August / std::chrono::day{ 6u },
			std::chrono::year{ 2018 } / std::chrono::November / std::chrono::day{ 30u },
			std::chrono::year{ 2018 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2018 } / std::chrono::December / std::chrono::day{ 26u },

			std::chrono::year{ 2019 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2019 } / std::chrono::January / std::chrono::day{ 2u },
			std::chrono::year{ 2019 } / std::chrono::April / std::chrono::day{ 19u },
			std::chrono::year{ 2019 } / std::chrono::May / std::chrono::day{ 6u },
			std::chrono::year{ 2019 } / std::chrono::May / std::chrono::day{ 27u },
			std::chrono::year{ 2019 } / std::chrono::August / std::chrono::day{ 5u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 2u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 26u },

			std::chrono::year{ 2020 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2020 } / std::chrono::January / std::chrono::day{ 2u },
			std::chrono::year{ 2020 } / std::chrono::April / std::chrono::day{ 10u },
			std::chrono::year{ 2020 } / std::chrono::May / std::chrono::day{ 8u },
			std::chrono::year{ 2020 } / std::chrono::May / std::chrono::day{ 25u },
			std::chrono::year{ 2020 } / std::chrono::August / std::chrono::day{ 3u },
			std::chrono::year{ 2020 } / std::chrono::November / std::chrono::day{ 30u },
			std::chrono::year{ 2020 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2020 } / std::chrono::December / std::chrono::day{ 28u },

			std::chrono::year{ 2021 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2021 } / std::chrono::January / std::chrono::day{ 4u },
			std::chrono::year{ 2021 } / std::chrono::April / std::chrono::day{ 2u },
			std::chrono::year{ 2021 } / std::chrono::May / std::chrono::day{ 3u },
			std::chrono::year{ 2021 } / std::chrono::May / std::chrono::day{ 31u },
			std::chrono::year{ 2021 } / std::chrono::August / std::chrono::day{ 2u },
			std::chrono::year{ 2021 } / std::chrono::November / std::chrono::day{ 30u },
			std::chrono::year{ 2021 } / std::chrono::December / std::chrono::day{ 27u },
			std::chrono::year{ 2021 } / std::chrono::December / std::chrono::day{ 28u },

			std::chrono::year{ 2022 } / std::chrono::January / std::chrono::day{ 3u },
			std::chrono::year{ 2022 } / std::chrono::January / std::chrono::day{ 4u },
			std::chrono::year{ 2022 } / std::chrono::April / std::chrono::day{ 15u },
			std::chrono::year{ 2022 } / std::chrono::May / std::chrono::day{ 2u },
			std::chrono::year{ 2022 } / std::chrono::June / std::chrono::day{ 2u },
			std::chrono::year{ 2022 } / std::chrono::June / std::chrono::day{ 3u },
			std::chrono::year{ 2022 } / std::chrono::August / std::chrono::day{ 1u },
			std::chrono::year{ 2022 } / std::chrono::September / std::chrono::day{ 19u },
			std::chrono::year{ 2022 } / std::chrono::November / std::chrono::day{ 30u },
			std::chrono::year{ 2022 } / std::chrono::December / std::chrono::day{ 26u },
			std::chrono::year{ 2022 } / std::chrono::December / std::chrono::day{ 27u },

			std::chrono::year{ 2023 } / std::chrono::January / std::chrono::day{ 2u },
			std::chrono::year{ 2023 } / std::chrono::January / std::chrono::day{ 3u },
			std::chrono::year{ 2023 } / std::chrono::April / std::chrono::day{ 7u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 1u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 8u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 29u },
			std::chrono::year{ 2023 } / std::chrono::August / std::chrono::day{ 7u },
			std::chrono::year{ 2023 } / std::chrono::November / std::chrono::day{ 30u },
			std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 26u },
		};

		return schedule{
			days_period{ Epoch, std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 31u } },
			std::move(holidays)
		};
	}

	inline auto _make_Scotland_calendar() -> calendar
	{
		const auto known_part = _Scotland_schedule();

		const auto generated_part_from = known_part.get_from_until().get_until().year();
		const auto generated_part_until = generated_part_from + std::chrono::years{ 10 }; // factor out this const

		const auto SecondJanuary = offset_holiday<named_holiday>{ NewYearsDay, std::chrono::days{ 1 } };
		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto SummerBankHoliday = weekday_indexed_holiday{ std::chrono::August / std::chrono::Monday[1] };
		const auto StAndrewsDay = named_holiday{ std::chrono::November / std::chrono::day{ 30u } };

		const auto rules = annual_holiday_storage{
			&NewYearsDay,
			&SecondJanuary,
			&GoodFriday,
			&EarlyMayBankHoliday,
			&SpringBankHoliday,
			&SummerBankHoliday,
			&StAndrewsDay,
			&ChristmasDay,
			&BoxingDay
		};

		const auto generated_part = make_holiday_schedule(
			{ generated_part_from, generated_part_until },
			rules
		);

		// setup a calendar for the generated part only (to do substitution for the generated dates)
		// do we need operator+ for calendar instead?
		auto cal = calendar{
			SaturdaySundayWeekend,
			generated_part
		};
		cal.substitute(&Following);

		return calendar{
			SaturdaySundayWeekend,
			known_part + cal.get_holiday_schedule()
		};
	}

	inline auto make_Scotland_calendar() -> const calendar&
	{
		static const auto s = _make_Scotland_calendar();
		return s;
	}



	inline auto _Northern_Ireland_schedule() -> schedule
	{
		auto holidays = schedule::storage{
			std::chrono::year{ 2018 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2018 } / std::chrono::March / std::chrono::day{ 19u },
			std::chrono::year{ 2018 } / std::chrono::March / std::chrono::day{ 30u },
			std::chrono::year{ 2018 } / std::chrono::April / std::chrono::day{ 2u },
			std::chrono::year{ 2018 } / std::chrono::May / std::chrono::day{ 7u },
			std::chrono::year{ 2018 } / std::chrono::May / std::chrono::day{ 28u },
			std::chrono::year{ 2018 } / std::chrono::July / std::chrono::day{ 12u },
			std::chrono::year{ 2018 } / std::chrono::August / std::chrono::day{ 27u },
			std::chrono::year{ 2018 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2018 } / std::chrono::December / std::chrono::day{ 26u },

			std::chrono::year{ 2019 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2019 } / std::chrono::March / std::chrono::day{ 18u },
			std::chrono::year{ 2019 } / std::chrono::April / std::chrono::day{ 19u },
			std::chrono::year{ 2019 } / std::chrono::April / std::chrono::day{ 22u },
			std::chrono::year{ 2019 } / std::chrono::May / std::chrono::day{ 6u },
			std::chrono::year{ 2019 } / std::chrono::May / std::chrono::day{ 27u },
			std::chrono::year{ 2019 } / std::chrono::July / std::chrono::day{ 12u },
			std::chrono::year{ 2019 } / std::chrono::August / std::chrono::day{ 26u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2019 } / std::chrono::December / std::chrono::day{ 26u },

			std::chrono::year{ 2020 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2020 } / std::chrono::March / std::chrono::day{ 17u },
			std::chrono::year{ 2020 } / std::chrono::April / std::chrono::day{ 10u },
			std::chrono::year{ 2020 } / std::chrono::April / std::chrono::day{ 13u },
			std::chrono::year{ 2020 } / std::chrono::May / std::chrono::day{ 8u },
			std::chrono::year{ 2020 } / std::chrono::May / std::chrono::day{ 25u },
			std::chrono::year{ 2020 } / std::chrono::July / std::chrono::day{ 13u },
			std::chrono::year{ 2020 } / std::chrono::August / std::chrono::day{ 31u },
			std::chrono::year{ 2020 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2020 } / std::chrono::December / std::chrono::day{ 28u },

			std::chrono::year{ 2021 } / std::chrono::January / std::chrono::day{ 1u },
			std::chrono::year{ 2021 } / std::chrono::March / std::chrono::day{ 17u },
			std::chrono::year{ 2021 } / std::chrono::April / std::chrono::day{ 2u },
			std::chrono::year{ 2021 } / std::chrono::April / std::chrono::day{ 5u },
			std::chrono::year{ 2021 } / std::chrono::May / std::chrono::day{ 3u },
			std::chrono::year{ 2021 } / std::chrono::May / std::chrono::day{ 31u },
			std::chrono::year{ 2021 } / std::chrono::July / std::chrono::day{ 12u },
			std::chrono::year{ 2021 } / std::chrono::August / std::chrono::day{ 30u },
			std::chrono::year{ 2021 } / std::chrono::December / std::chrono::day{ 27u },
			std::chrono::year{ 2021 } / std::chrono::December / std::chrono::day{ 28u },

			std::chrono::year{ 2022 } / std::chrono::January / std::chrono::day{ 3u },
			std::chrono::year{ 2022 } / std::chrono::March / std::chrono::day{ 17u },
			std::chrono::year{ 2022 } / std::chrono::April / std::chrono::day{ 15u },
			std::chrono::year{ 2022 } / std::chrono::April / std::chrono::day{ 18u },
			std::chrono::year{ 2022 } / std::chrono::May / std::chrono::day{ 2u },
			std::chrono::year{ 2022 } / std::chrono::June / std::chrono::day{ 2u },
			std::chrono::year{ 2022 } / std::chrono::June / std::chrono::day{ 3u },
			std::chrono::year{ 2022 } / std::chrono::July / std::chrono::day{ 12u },
			std::chrono::year{ 2022 } / std::chrono::August / std::chrono::day{ 29u },
			std::chrono::year{ 2022 } / std::chrono::September / std::chrono::day{ 19u },
			std::chrono::year{ 2022 } / std::chrono::December / std::chrono::day{ 26u },
			std::chrono::year{ 2022 } / std::chrono::December / std::chrono::day{ 27u },

			std::chrono::year{ 2023 } / std::chrono::January / std::chrono::day{ 2u },
			std::chrono::year{ 2023 } / std::chrono::March / std::chrono::day{ 17u },
			std::chrono::year{ 2023 } / std::chrono::April / std::chrono::day{ 7u },
			std::chrono::year{ 2023 } / std::chrono::April / std::chrono::day{ 10u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 1u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 8u },
			std::chrono::year{ 2023 } / std::chrono::May / std::chrono::day{ 29u },
			std::chrono::year{ 2023 } / std::chrono::July / std::chrono::day{ 12u },
			std::chrono::year{ 2023 } / std::chrono::August / std::chrono::day{ 28u },
			std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 25u },
			std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 26u },
		};

		return schedule{
			days_period{ Epoch, std::chrono::year{ 2023 } / std::chrono::December / std::chrono::day{ 31u } },
			std::move(holidays)
		};
	}

	inline auto _make_Northern_Ireland_calendar() -> calendar
	{
		const auto known_part = _Northern_Ireland_schedule();

		const auto generated_part_from = known_part.get_from_until().get_until().year();
		const auto generated_part_until = generated_part_from + std::chrono::years{ 10 }; // factor out this const

		const auto StPatricsDay = named_holiday{ std::chrono::March / std::chrono::day{ 18u } };
		const auto EarlyMayBankHoliday = weekday_indexed_holiday{ std::chrono::May / std::chrono::Monday[1] };
		const auto SpringBankHoliday = weekday_last_holiday{ std::chrono::May / std::chrono::Monday[std::chrono::last] };
		const auto OrangemensDay = named_holiday{ std::chrono::July / std::chrono::day{ 12u } };
		const auto SummerBankHoliday = weekday_last_holiday{ std::chrono::August / std::chrono::Monday[std::chrono::last] };

		const auto rules = annual_holiday_storage{
			&NewYearsDay,
			&StPatricsDay,
			&GoodFriday,
			&EasterMonday,
			&EarlyMayBankHoliday,
			&SpringBankHoliday,
			&OrangemensDay,
			&SummerBankHoliday,
			&ChristmasDay,
			&BoxingDay
		};

		const auto generated_part = make_holiday_schedule(
			{ generated_part_from, generated_part_until },
			rules
		);

		// setup a calendar for the generated part only (to do substitution for the generated dates)
		// do we need operator+ for calendar instead?
		auto cal = calendar{
			SaturdaySundayWeekend,
			generated_part
		};
		cal.substitute(&Following);

		return calendar{
			SaturdaySundayWeekend,
			known_part + cal.get_holiday_schedule()
		};
	}

	inline auto make_Norther_Ireland_calendar() -> const calendar&
	{
		static const auto s = _make_Northern_Ireland_calendar();
		return s;
	}

}
