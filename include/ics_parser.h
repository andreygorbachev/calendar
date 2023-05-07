#pragma once

#include "calendar.h"

#include <string>
#include <chrono>
#include <istream>
#include <fstream>


// is it possible that a single event codes multiple (subsequent) days?
// (if not assert against it)
inline auto _parse_event(std::istream& fs) -> std::chrono::year_month_day
{
	auto ymd = std::chrono::year_month_day{};

	auto b = std::string{};
	std::getline(fs, b);
	if (b != "VEVENT") // BEGIN: was already read
		throw std::exception{}; // what exception do we want here?

	// should we somehow check that only "daily" events are supplied?
	// (or does the format of parse already does it for us?)
	// or maybe we do not want that as sometimes we have 1/2 day events

	for (;;)
	{
		auto s = std::string{};
		std::getline(fs, s, ':'); // get the start of the line

		if (s == "DTSTART;VALUE=DATE")
		{
			if (ymd != std::chrono::year_month_day{})
				throw std::exception{}; // multiple DTSTART

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
		throw std::exception{}; // what exception do we want here?

	if (ymd == std::chrono::year_month_day{})
		throw std::exception{}; // no DTSTART

	return ymd;
}


inline auto _parse_ics(std::istream& fs) -> calendar::holidays_storage
{
	auto result = calendar::holidays_storage{};

	auto b = std::string{};
	std::getline(fs, b);
	if (b != "BEGIN:VCALENDAR")
		throw std::exception{}; // what exception do we want here?

	// handle "PRODID" and "VERSION" - do we just support version 2.0?

	// should we check that there is at least one event? - no need (empty calendars should be allowed)

	// if the same event is in the file more than once - is it a problem? (should be ok to allow for duplicates)

	for (;;)
	{
		auto s = std::string{};
		std::getline(fs, s, ':'); // get the start of the line

		if (s == "BEGIN")
		{
			auto ymd = _parse_event(fs);
			result.push_back(std::move(ymd));
		}
		else if (s == "END")
			break;
		else
			std::getline(fs, s); // skip the rest of the line
	}

	auto e = std::string{};
	std::getline(fs, e);
	if (e != "VCALENDAR") // END: was already read
		throw std::exception{}; // what exception do we want here?

	return result;
}


// we assume that holidays are sorted
inline auto _start(const calendar::holidays_storage& holidays) noexcept -> std::chrono::year_month_day
{
	const auto h = holidays.empty() ? std::chrono::year_month_day{} : holidays.front();
	// or should we have smallest possible year_month_day if the holidays are empty?

	return { h.year(), std::chrono::January, std::chrono::day{ 1u } };
}

inline auto _end(const calendar::holidays_storage& holidays) noexcept -> std::chrono::year_month_day
{
	const auto h = holidays.empty() ? std::chrono::year_month_day{} : holidays.back();
	// or should we have largest possible year_month_day if the holidays are empty? (or is it ok for it to be the same as _start?)

	return { h.year(), std::chrono::December, std::chrono::day{ 31u } };
}


inline auto parse_ics(const std::string& fileName) -> calendar
{
	/*const*/ auto fs = std::ifstream{ fileName }; // should we handle a default .ics file extension?

	auto holidays = _parse_ics(fs);

	// we assume that ics file covers the full number of years
	return calendar{
		_start(holidays),
		_end(holidays),
		std::move(holidays)
	};
	// do we ever have weekend info in the ics files, which we should also process here?
}
