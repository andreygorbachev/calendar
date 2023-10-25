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
#include <schedule.h>
#include <annual_holiday_interface.h>

#include <string>
#include <chrono>
#include <istream>
#include <fstream>
#include <stdexcept>


inline auto _parse_date(std::istream& fs) -> std::chrono::year_month_day
{
	auto ymd = std::chrono::year_month_day{};

	std::chrono::from_stream(fs, "%Y%m%d%n", ymd); // %n to read '\n' at the end of the line

	return ymd;
}


inline auto _parse_csv_schedule_storage(std::istream& fs) -> gregorian::schedule::storage
{
	auto result = gregorian::schedule::storage{};

	for (;;)
	{
		auto ymd = _parse_date(fs);
		if (!fs.fail()) // sometimes we just have an empty line at the end of the file - this should handle it
			result.insert(std::move(ymd));

		if (fs.eof())
			break;
	}

	return result;
}


inline auto parse_csv_schedule(const std::string& fileName) -> gregorian::schedule
{
	/*const*/ auto fs = std::ifstream{ fileName }; // should we handle a default .csv file extension?

	auto hols = _parse_csv_schedule_storage(fs);
	auto from_until = gregorian::make_days_period(hols);

	// we assume that csv file covers the full number of years
	return gregorian::schedule{
		std::move(from_until),
		std::move(hols)
	};
}
