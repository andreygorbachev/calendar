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

#include <string>
#include <chrono>
#include <istream>
#include <fstream>
#include <utility>
#include <stdexcept> // only for !_MSC_BUILD


inline auto _parse_date(std::istream& fs) -> std::chrono::year_month_day
{
	auto ymd = std::chrono::year_month_day{};

#ifdef _MSC_BUILD
	std::chrono::from_stream(fs, "%d/%m/%Y", ymd);
#else
	throw std::domain_error{ "Not implemented" };
#endif

	return ymd;
}


inline auto _parse_csv_schedule_storage(std::istream& fs) -> gregorian::schedule::dates
{
	auto result = gregorian::schedule::dates{};

	// skip headers
	auto b = std::string{};
	std::getline(fs, b); // we can check that the headers are as expected

	for (;;)
	{
		auto ymd = _parse_date(fs);
		if (!ymd.ok())
			break;
		// we assume that at the end of the file there are some comments

		result.insert(std::move(ymd));
		std::getline(fs, b); // skip the rest of the line
	}

	return result;
}


// there is no info on [from, until] in this XLS file, so we'll have to specify them
inline auto parse_csv_schedule(
	const std::string& fileName,
	std::chrono::year y_from,
	std::chrono::year y_until
) -> gregorian::schedule
{
	/*const*/ auto fs = std::ifstream{ fileName }; // should we handle a default .csv file extension?

	auto hols = _parse_csv_schedule_storage(fs);

	const auto from = y_from / gregorian::FirstDayOfJanuary;
	const auto until = y_until / gregorian::LastDayOfDecember;

	return gregorian::schedule{ gregorian::util::days_period{ from, until }, std::move(hols) };
}
