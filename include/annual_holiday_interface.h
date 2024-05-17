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
#include <vector>
#include <memory>


namespace gregorian
{

	class annual_holiday
	{

	public:

		annual_holiday() noexcept = default;
		virtual ~annual_holiday() noexcept = default;

		annual_holiday(const annual_holiday&) = delete;
		annual_holiday(annual_holiday&&) noexcept = delete;

		annual_holiday& operator=(const annual_holiday&) = delete;
		annual_holiday& operator=(annual_holiday&&) noexcept = delete;

	public:

		auto make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day;

	private:

		virtual auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day = 0;

	};



	using annual_holiday_storage = std::vector<const annual_holiday*>;
	// choice here is influenced by a desire to eventualy be able to apply annual_holiday rules at compile time (constexpr)

	inline auto make_holiday_schedule(
		const years_period& from_until,
		const annual_holiday_storage& rules
	) noexcept -> schedule
	{
		auto hols = schedule::storage{};

		for (auto y = from_until.get_from(); y <= from_until.get_until(); ++y)
			for (const auto& rule : rules)
				hols.insert(rule->make_holiday(y));

		return schedule{
			days_period{
				from_until.get_from() / FirstDayOfJanuary,
				from_until.get_until() / LastDayOfDecember
			},
			std::move(hols)
		};
	}

	inline auto make_holiday_schedule(
		const std::chrono::year& y,
		const annual_holiday_storage& rules
	) noexcept -> schedule
	{
		return make_holiday_schedule(years_period{ y, y }, rules);
	}



	inline auto annual_holiday::make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return _make_holiday(y);
	}

}
