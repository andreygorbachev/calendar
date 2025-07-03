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

#include <period.h>
#include <calendar.h>
#include <schedule.h>

#include <chrono>


namespace gregorian
{

	namespace static_data
	{

		constexpr auto Epoch = util::period{
			std::chrono::year{ 2018 } / FirstDayOfJanuary, // all calendars should include holidays from at least this day
			std::chrono::year{ 2118 } / LastDayOfDecember
		}; // or should it be in years?


		// from https://www.gov.uk/bank-holidays

		auto make_England_calendar() -> const calendar&;

		auto make_Wales_calendar() -> const calendar&;

		auto make_Scotland_calendar() -> const calendar&;

		auto make_Northern_Ireland_calendar() -> const calendar&;


		// from https://www.ecb.europa.eu/paym/target/t2/html/index.en.html

		auto make_T2_calendar() -> const calendar&; // actually started in November 2007


		// from https://www.opm.gov/policy-data-oversight/pay-leave/federal-holidays/

		auto make_USA_Federal_calendar() -> const calendar&;

		auto make_Washington_DC_Federal_calendar() -> const calendar&;


		//

		auto make_ANBIMA_calendar() -> const calendar&;

	}

}
