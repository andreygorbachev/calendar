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

#include <annual_holiday_interface.h>

#include <chrono>


namespace gregorian
{

	namespace static_data
	{

		// is file's name consistent with the name of the class?
		class _victoria_day_holiday final : public annual_holiday // should it be generalized and moved to annual_holidays.h?
		{

		private:

			// from Wikipedia:
			// observed on the last Monday preceding May 25
			auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

		};

		const auto _VictoriaDay = _victoria_day_holiday{};


		inline auto _victoria_day_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
		{
			// GitHub Copilot suggested this implementation based on the description of Victoria Day - maybe review it later
			const auto d25 = std::chrono::sys_days{ y / std::chrono::May / std::chrono::day{ 25u } };
			const auto wd = std::chrono::weekday{ d25 };
			const auto days_back = (wd.iso_encoding() + 6u) % 7u; // iso_encoding(): Mon=1..Sun=7
			return d25 - std::chrono::days{ days_back };
		}

	}

}
