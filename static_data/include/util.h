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

// these are internal utilities, which are not expected to be used directly by the users of the library
// (but we would like to untit test them)

#include "makers.h"

#include <period.h>
#include <annual_holiday_interface.h>

#include <chrono>
#include <optional>
#include <set>


namespace gregorian
{

	namespace static_data
	{

		auto make_generated_period(
			const std::optional<util::days_period>& known, // we might not have any known period at all
			const util::days_period& epoch
		) -> std::optional<util::days_period>; // we might not have any generated period at all


		class _compare_subsequent_periods
		{
		public:
			auto operator()(
				const util::days_period& lhs,
				const util::days_period& rhs
			) const -> bool
			{
				// assert that rhs.get_from() is the next day after lhs.get_until()
				return lhs.get_from() < rhs.get_from();
			}
		};

		using days_period_set = std::set<util::days_period, _compare_subsequent_periods>;
		// is it correct to return set here? // should we be using yers_period instead of days_period?

		auto make_generated_periods_as_of_date(
			const _annual_holiday_period_storage& storage,
			const std::chrono::year_month_day& as_of_date
		) -> days_period_set;
			
			
		auto make_holiday_schedule_as_of_date(
			const _annual_holiday_period_storage& storage, // should it be "_"?
			const std::chrono::year_month_day& as_of_date
		) -> annual_holiday_storage;
		// what should it return? annual_holiday_storage with applicable periods? periods with applicable annual_holiday_storage?

	}

}
