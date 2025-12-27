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
#include <string_view>


namespace gregorian
{

	namespace static_data
	{

		// we should probably label every holiday with a time frame it is applicable
		// (and have a singleton for the "as of date" so a calendar from that date can be created)

		auto locate_calendar(std::string_view tz_name) -> const calendar&; // or should it return const calendar* like locate_zone?
		// or is it more of a locale thing, rather than a time zone?

		constexpr auto Epoch = util::period{
			std::chrono::year{ 2018 } / FirstDayOfJanuary, // all calendars should include holidays from at least this day
			std::chrono::year{ 2118 } / LastDayOfDecember
		}; // or should it be in years?
		// we probably want 2000-2100 (or until 2099)

	}

}
