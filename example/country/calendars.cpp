// The MIT License (MIT)
//
// Copyright (c) 2023-2024 Andrey Gorbachev
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

#include "calendars.h"

#include <schedule.h>
#include <annual_holidays.h>
#include <weekend.h>
#include <business_day_adjusters.h>

#include <utility>

using namespace std;
using namespace std::chrono;

using namespace gregorian;
using namespace gregorian::util;



auto _England_schedule() -> schedule // or should it be a "proper" function (without _)?
{
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

		year{ 2024 } / January / day{ 1u },
		year{ 2024 } / March / day{ 29u },
		year{ 2024 } / April / day{ 1u },
		year{ 2024 } / May / day{ 6u },
		year{ 2024 } / May / day{ 27u },
		year{ 2024 } / August / day{ 26u },
		year{ 2024 } / December / day{ 25u },
		year{ 2024 } / December / day{ 26u },

		year{ 2025 } / January / day{ 1u },
		year{ 2025 } / April / day{ 18u },
		year{ 2025 } / April / day{ 21u },
		year{ 2025 } / May / day{ 5u },
		year{ 2025 } / May / day{ 26u },
		year{ 2025 } / August / day{ 25u },
		year{ 2025 } / December / day{ 25u },
		year{ 2025 } / December / day{ 26u },

		year{ 2026 } / January / day{ 1u },
		year{ 2026 } / April / day{ 3u },
		year{ 2026 } / April / day{ 6u },
		year{ 2026 } / May / day{ 4u },
		year{ 2026 } / May / day{ 25u },
		year{ 2026 } / August / day{ 31u },
		year{ 2026 } / December / day{ 25u },
		year{ 2026 } / December / day{ 28u },

		year{ 2027 } / January / day{ 1u },
		year{ 2027 } / March / day{ 26u },
		year{ 2027 } / March / day{ 29u },
		year{ 2027 } / May / day{ 3u },
		year{ 2027 } / May / day{ 31u },
		year{ 2027 } / August / day{ 30u },
		year{ 2027 } / December / day{ 27u },
		year{ 2027 } / December / day{ 28u },
	};

	return schedule{
		days_period{ Epoch, year{ 2027 } / LastDayOfDecember },
		move(holidays)
	};
}

auto _make_England_calendar() -> calendar
{
	const auto known_part = _England_schedule();

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



auto _Scotland_schedule() -> schedule
{
	auto holidays = schedule::dates{
		year{ 2018 } / January / day{ 1u },
		year{ 2018 } / January / day{ 2u },
		year{ 2018 } / March / day{ 30u },
		year{ 2018 } / May / day{ 7u },
		year{ 2018 } / May / day{ 28u },
		year{ 2018 } / August / day{ 6u },
		year{ 2018 } / November / day{ 30u },
		year{ 2018 } / December / day{ 25u },
		year{ 2018 } / December / day{ 26u },

		year{ 2019 } / January / day{ 1u },
		year{ 2019 } / January / day{ 2u },
		year{ 2019 } / April / day{ 19u },
		year{ 2019 } / May / day{ 6u },
		year{ 2019 } / May / day{ 27u },
		year{ 2019 } / August / day{ 5u },
		year{ 2019 } / December / day{ 2u },
		year{ 2019 } / December / day{ 25u },
		year{ 2019 } / December / day{ 26u },

		year{ 2020 } / January / day{ 1u },
		year{ 2020 } / January / day{ 2u },
		year{ 2020 } / April / day{ 10u },
		year{ 2020 } / May / day{ 8u },
		year{ 2020 } / May / day{ 25u },
		year{ 2020 } / August / day{ 3u },
		year{ 2020 } / November / day{ 30u },
		year{ 2020 } / December / day{ 25u },
		year{ 2020 } / December / day{ 28u },

		year{ 2021 } / January / day{ 1u },
		year{ 2021 } / January / day{ 4u },
		year{ 2021 } / April / day{ 2u },
		year{ 2021 } / May / day{ 3u },
		year{ 2021 } / May / day{ 31u },
		year{ 2021 } / August / day{ 2u },
		year{ 2021 } / November / day{ 30u },
		year{ 2021 } / December / day{ 27u },
		year{ 2021 } / December / day{ 28u },

		year{ 2022 } / January / day{ 3u },
		year{ 2022 } / January / day{ 4u },
		year{ 2022 } / April / day{ 15u },
		year{ 2022 } / May / day{ 2u },
		year{ 2022 } / June / day{ 2u },
		year{ 2022 } / June / day{ 3u },
		year{ 2022 } / August / day{ 1u },
		year{ 2022 } / September / day{ 19u },
		year{ 2022 } / November / day{ 30u },
		year{ 2022 } / December / day{ 26u },
		year{ 2022 } / December / day{ 27u },

		year{ 2023 } / January / day{ 2u },
		year{ 2023 } / January / day{ 3u },
		year{ 2023 } / April / day{ 7u },
		year{ 2023 } / May / day{ 1u },
		year{ 2023 } / May / day{ 8u },
		year{ 2023 } / May / day{ 29u },
		year{ 2023 } / August / day{ 7u },
		year{ 2023 } / November / day{ 30u },
		year{ 2023 } / December / day{ 25u },
		year{ 2023 } / December / day{ 26u },

		year{ 2024 } / January / day{ 1u },
		year{ 2024 } / January / day{ 2u },
		year{ 2024 } / March / day{ 29u },
		year{ 2024 } / May / day{ 6u },
		year{ 2024 } / May / day{ 27u },
		year{ 2024 } / August / day{ 5u },
		year{ 2024 } / December / day{ 2u },
		year{ 2024 } / December / day{ 25u },
		year{ 2024 } / December / day{ 26u },

		year{ 2025 } / January / day{ 1u },
		year{ 2025 } / January / day{ 2u },
		year{ 2025 } / April / day{ 18u },
		year{ 2025 } / May / day{ 5u },
		year{ 2025 } / May / day{ 26u },
		year{ 2025 } / August / day{ 4u },
		year{ 2025 } / December / day{ 1u },
		year{ 2025 } / December / day{ 25u },
		year{ 2025 } / December / day{ 26u },

		year{ 2026 } / January / day{ 1u },
		year{ 2025 } / January / day{ 2u },
		year{ 2026 } / April / day{ 3u },
		year{ 2026 } / May / day{ 4u },
		year{ 2026 } / May / day{ 25u },
		year{ 2026 } / August / day{ 3u },
		year{ 2026 } / November / day{ 30u },
		year{ 2026 } / December / day{ 25u },
		year{ 2026 } / December / day{ 28u },

		year{ 2027 } / January / day{ 1u },
		year{ 2025 } / January / day{ 4u },
		year{ 2027 } / March / day{ 26u },
		year{ 2027 } / May / day{ 3u },
		year{ 2027 } / May / day{ 31u },
		year{ 2027 } / August / day{ 30u }, // is this correct?
		year{ 2026 } / November / day{ 30u },
		year{ 2027 } / December / day{ 27u },
		year{ 2027 } / December / day{ 28u },
	};

	return schedule{
		days_period{ Epoch, year{ 2027 } / LastDayOfDecember },
		move(holidays)
	};
}

auto _make_Scotland_calendar() -> calendar
{
	const auto known_part = _Scotland_schedule();

	const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
	const auto generated_part_until = generated_part_from + years{ 10 }; // factor out this const

	const auto SecondJanuary = offset_holiday{ &NewYearsDay, days{ 1 } };
	const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
	const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
	const auto SummerBankHoliday = weekday_indexed_holiday{ August / Monday[1] };
	const auto StAndrewsDay = named_holiday{ November / day{ 30u } };

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



auto _Northern_Ireland_schedule() -> schedule
{
	auto holidays = schedule::dates{
		year{ 2018 } / January / day{ 1u },
		year{ 2018 } / March / day{ 19u },
		year{ 2018 } / March / day{ 30u },
		year{ 2018 } / April / day{ 2u },
		year{ 2018 } / May / day{ 7u },
		year{ 2018 } / May / day{ 28u },
		year{ 2018 } / July / day{ 12u },
		year{ 2018 } / August / day{ 27u },
		year{ 2018 } / December / day{ 25u },
		year{ 2018 } / December / day{ 26u },

		year{ 2019 } / January / day{ 1u },
		year{ 2019 } / March / day{ 18u },
		year{ 2019 } / April / day{ 19u },
		year{ 2019 } / April / day{ 22u },
		year{ 2019 } / May / day{ 6u },
		year{ 2019 } / May / day{ 27u },
		year{ 2019 } / July / day{ 12u },
		year{ 2019 } / August / day{ 26u },
		year{ 2019 } / December / day{ 25u },
		year{ 2019 } / December / day{ 26u },

		year{ 2020 } / January / day{ 1u },
		year{ 2020 } / March / day{ 17u },
		year{ 2020 } / April / day{ 10u },
		year{ 2020 } / April / day{ 13u },
		year{ 2020 } / May / day{ 8u },
		year{ 2020 } / May / day{ 25u },
		year{ 2020 } / July / day{ 13u },
		year{ 2020 } / August / day{ 31u },
		year{ 2020 } / December / day{ 25u },
		year{ 2020 } / December / day{ 28u },

		year{ 2021 } / January / day{ 1u },
		year{ 2021 } / March / day{ 17u },
		year{ 2021 } / April / day{ 2u },
		year{ 2021 } / April / day{ 5u },
		year{ 2021 } / May / day{ 3u },
		year{ 2021 } / May / day{ 31u },
		year{ 2021 } / July / day{ 12u },
		year{ 2021 } / August / day{ 30u },
		year{ 2021 } / December / day{ 27u },
		year{ 2021 } / December / day{ 28u },

		year{ 2022 } / January / day{ 3u },
		year{ 2022 } / March / day{ 17u },
		year{ 2022 } / April / day{ 15u },
		year{ 2022 } / April / day{ 18u },
		year{ 2022 } / May / day{ 2u },
		year{ 2022 } / June / day{ 2u },
		year{ 2022 } / June / day{ 3u },
		year{ 2022 } / July / day{ 12u },
		year{ 2022 } / August / day{ 29u },
		year{ 2022 } / September / day{ 19u },
		year{ 2022 } / December / day{ 26u },
		year{ 2022 } / December / day{ 27u },

		year{ 2023 } / January / day{ 2u },
		year{ 2023 } / March / day{ 17u },
		year{ 2023 } / April / day{ 7u },
		year{ 2023 } / April / day{ 10u },
		year{ 2023 } / May / day{ 1u },
		year{ 2023 } / May / day{ 8u },
		year{ 2023 } / May / day{ 29u },
		year{ 2023 } / July / day{ 12u },
		year{ 2023 } / August / day{ 28u },
		year{ 2023 } / December / day{ 25u },
		year{ 2023 } / December / day{ 26u },

		year{ 2024 } / January / day{ 1u },
		year{ 2024 } / March / day{ 18u },
		year{ 2024 } / March / day{ 29u },
		year{ 2024 } / April / day{ 1u },
		year{ 2024 } / May / day{ 6u },
		year{ 2024 } / May / day{ 27u },
		year{ 2024 } / July / day{ 12u },
		year{ 2024 } / August / day{ 26u },
		year{ 2024 } / December / day{ 25u },
		year{ 2024 } / December / day{ 26u },

		year{ 2025 } / January / day{ 1u },
		year{ 2025 } / March / day{ 17u },
		year{ 2025 } / April / day{ 18u },
		year{ 2025 } / April / day{ 21u },
		year{ 2025 } / May / day{ 5u },
		year{ 2025 } / May / day{ 26u },
		year{ 2025 } / July / day{ 14u },
		year{ 2025 } / August / day{ 25u },
		year{ 2025 } / December / day{ 25u },
		year{ 2025 } / December / day{ 26u },

		year{ 2026 } / January / day{ 1u },
		year{ 2025 } / March / day{ 17u },
		year{ 2026 } / April / day{ 3u },
		year{ 2026 } / April / day{ 6u },
		year{ 2026 } / May / day{ 4u },
		year{ 2026 } / May / day{ 25u },
		year{ 2025 } / July / day{ 13u },
		year{ 2026 } / August / day{ 31u },
		year{ 2026 } / December / day{ 25u },
		year{ 2026 } / December / day{ 28u },

		year{ 2027 } / January / day{ 1u },
		year{ 2025 } / March / day{ 17u },
		year{ 2027 } / March / day{ 26u },
		year{ 2027 } / March / day{ 29u },
		year{ 2027 } / May / day{ 3u },
		year{ 2027 } / May / day{ 31u },
		year{ 2025 } / July / day{ 12u },
		year{ 2027 } / August / day{ 30u },
		year{ 2027 } / December / day{ 27u },
		year{ 2027 } / December / day{ 28u },
	};

	return schedule{
		days_period{ Epoch, year{ 2027 } / LastDayOfDecember },
		move(holidays)
	};
}

auto _make_Northern_Ireland_calendar() -> calendar
{
	const auto known_part = _Northern_Ireland_schedule();

	const auto generated_part_from = known_part.get_period().get_until().year() + years{ 1 };
	const auto generated_part_until = generated_part_from + years{ 10 }; // factor out this const

	const auto StPatricsDay = named_holiday{ March / day{ 18u } };
	const auto EarlyMayBankHoliday = weekday_indexed_holiday{ May / Monday[1] };
	const auto SpringBankHoliday = weekday_last_holiday{ May / Monday[last] };
	const auto OrangemensDay = named_holiday{ July / day{ 12u } };
	const auto SummerBankHoliday = weekday_last_holiday{ August / Monday[last] };

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



auto make_England_calendar() -> const calendar&
{
	static const auto s = _make_England_calendar();
	return s;
}

auto make_Wales_calendar() -> const calendar&
{
	return make_England_calendar();
}

auto make_Scotland_calendar() -> const calendar&
{
	static const auto s = _make_Scotland_calendar();
	return s;
}

auto make_Northern_Ireland_calendar() -> const calendar&
{
	static const auto s = _make_Northern_Ireland_calendar();
	return s;
}
