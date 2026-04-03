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
		// is there a different (and better) approach out there - make a templated periodic_holiday (templated on priodicity)
		// then annual_holiday would follow from that
		class _cyclical_holiday final : public annual_holiday // should it be moved to annual_holidays.h?
		{

		public:

			explicit _cyclical_holiday(
				const annual_holiday* const holiday,
				const std::chrono::year start,
				const std::chrono::years period
			) noexcept;

		private:

			auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

		private:

			const annual_holiday* _holiday; // rule to apply
			std::chrono::year _start; // first year when the cyclical rule becomes effective
			std::chrono::years _period; // number of years between occurrences

		};


		inline _cyclical_holiday::_cyclical_holiday(
			const annual_holiday* const holiday,
			const std::chrono::year start,
			const std::chrono::years period
		) noexcept :
			_holiday{ holiday },
			_start{ start },
			_period{ period }
		{
			// should we check that _period is above 0? (or how else do we handle that?)
		}

		inline auto _cyclical_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
		{
			// assert that _hoiday is not nullptr?
			// assert that y is after _start (or handle is somehow)?

			const auto diff = y - _start;
			if (diff % _period != std::chrono::years{ 0 })
				return y / std::chrono::January / std::chrono::day{ 32u }; // intentionally invalid date to indicate that there is no holiday in this year
			else
				return _holiday->make_holiday(y);
		}
		// is it too convoluted to rely on a "magic" invalid date to indicate that there is no holiday in a given year?

	}

}
