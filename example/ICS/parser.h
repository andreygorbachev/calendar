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


inline auto _parse_event(std::istream& fs) -> std::chrono::year_month_day
{
	auto ymd = std::chrono::year_month_day{};

	auto b = std::string{};
	std::getline(fs, b);
	if (b != "VEVENT") // BEGIN: was already read
		throw std::domain_error{ "Missing VEVENT" };

	// add handling of the events, which are not full day
	// add handling of the events spanning more than one day

	for (;;)
	{
		auto s = std::string{};
		std::getline(fs, s, ':'); // get the start of the line

		if (s == "DTSTART;VALUE=DATE")
		{
			if (ymd != std::chrono::year_month_day{})
				throw std::domain_error{ "Multiple DTSTART" };

			std::chrono::from_stream(fs, "%Y%m%d%n", ymd); // %n to read '\n' at the end of the line
		}
		else if (s == "END")
			break;
		else
			std::getline(fs, s); // skip the rest of the line
	}

	auto e = std::string{};
	std::getline(fs, e);
	if (e != "VEVENT") // END: was already read
		throw std::domain_error{ "Missing VEVENT" };

	if (ymd == std::chrono::year_month_day{})
		throw std::domain_error{ "Missing year_month_day" };

	return ymd;
}


inline auto _parse_ics(std::istream& fs) -> gregorian::schedule::dates
{
	auto result = gregorian::schedule::dates{};

	auto b = std::string{};
	std::getline(fs, b);
	if (b != "BEGIN:VCALENDAR")
		throw std::domain_error{ "Badly formed ICS" };

	// add handling of "PRODID" and "VERSION" - do we just support version 2.0?

	for (;;)
	{
		auto s = std::string{};
		std::getline(fs, s, ':'); // get the start of the line

		if (s == "BEGIN")
		{
			auto ymd = _parse_event(fs);
			result.insert(std::move(ymd));
		}
		else if (s == "END")
			break;
		else
			std::getline(fs, s); // skip the rest of the line
	}

	auto e = std::string{};
	std::getline(fs, e);
	if (e != "VCALENDAR") // END: was already read
		throw std::domain_error{ "Badly formed ICS" };

	return result;
}


inline auto parse_ics(const std::string& fileName) -> gregorian::schedule
{
	/*const*/ auto fs = std::ifstream{ fileName }; // should we handle a default .ics file extension?

	auto hols = _parse_ics(fs);

	// we assume that ics file covers the full number of years
	return gregorian::schedule{	std::move(hols)	};
	// do we ever have weekend info in the ics files, which we should also process here?
}
