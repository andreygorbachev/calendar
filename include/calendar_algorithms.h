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

#include "calendar.h"
#include "business_day_adjusters.h"

#include <chrono>


namespace gregorian
{

	inline auto shift_business_days(
		const std::chrono::sys_days& sd,
		const std::chrono::days& n, // is this a desirable type here?
		const calendar& cal
	) -> std::chrono::sys_days
	{
		auto result = sd;

		const auto _n = n.count();
		if (_n > std::chrono::days::rep{ 0 })
			for (auto i = std::chrono::days::rep{ 0 }; i < _n; ++i)
				result = Following.adjust(result + std::chrono::days{ 1 }, cal);
		else if (_n < std::chrono::days::rep{ 0 })
			for (auto i = std::chrono::days::rep{ 0 }; i > _n; --i)
				result = Preceding.adjust(result - std::chrono::days{ 1 }, cal);

		return result;
	}

	inline auto shift_business_days(
		const std::chrono::year_month_day& ymd,
		const std::chrono::days& n, // is this a desirable type here?
		const calendar& cal
	) -> std::chrono::year_month_day
	{
		// or implement directly?
		return shift_business_days(std::chrono::sys_days{ ymd }, n, cal);
	}

}
