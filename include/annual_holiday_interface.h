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

#include "schedule.h"

#include <chrono>
#include <unordered_set>


namespace gregorian
{

	class annual_holiday
	{

	public:

		virtual ~annual_holiday() noexcept = default;

	public:

		auto make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day;

	private:

		virtual auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day = 0;

	};
	// we can add a list of years where an annual holiday should not apply (skip a year)
	// (as rule based holidays at the moment are only directed for the future this is probably not needed)
	// would that lead us to "first year" and "last year" as well?



	using annual_holiday_storage = std::unordered_set<const annual_holiday*>;

	inline auto make_holiday_schedule(
		const years_period& from_until,
		const annual_holiday_storage& rules // or should it be a variadic template?
	) noexcept -> schedule
	{
		auto hols = schedule::storage{};

		for (auto y = from_until.get_from(); y <= from_until.get_until(); ++y)
			for (const auto& rule : rules)
				hols.insert(rule->make_holiday(y));

		return schedule{
			{
				from_until.get_from() / std::chrono::January / std::chrono::day{ 1u },
				from_until.get_until() / std::chrono::December / std::chrono::day{ 31u }
			},
			std::move(hols)
		};
	}

	inline auto make_holiday_schedule(
		const std::chrono::year& front_year,
		const annual_holiday_storage& rules // or should it be a variadic template?
	) noexcept -> schedule
	{
		return make_holiday_schedule({ front_year, front_year }, rules);
	}



	inline auto annual_holiday::make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return _make_holiday(y);
	}

}
