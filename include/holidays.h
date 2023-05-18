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

#include "holiday_interface.h"

#include <chrono>
#include <cmath>


namespace calendar
{

	// we can add one_off_holiday to capture things like coronation
	// (at the moment it is not clear if we want to do so at all - rule base calendars are expected for the future only
	// where one offs do not exist)



	class good_friday_holiday final : public annual_holiday
	{

	public:

		auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	};


	const auto GoodFriday = good_friday_holiday{};


	// or should this be combined with good_friday_holiday?
	// (so we have easter_holiday and some number of days offsetting holidays)
	// (the same would be helpful for boxing day as well)
	class easter_monday_holiday final : public annual_holiday
	{

	public:

		auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	};


	const auto EasterMonday = easter_monday_holiday{};



	class named_holiday final : public annual_holiday
	{

	public:

		explicit named_holiday(std::chrono::month_day md) noexcept;

	public:

		auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_day _md;

	};


	const auto NewYearsDay = named_holiday{ std::chrono::January / std::chrono::day{ 1u } };
	const auto ChristmasDay = named_holiday{ std::chrono::December / std::chrono::day{ 25u } };
	const auto BoxingDay = named_holiday{ std::chrono::December / std::chrono::day{ 26u } };



	class weekday_indexed_holiday final : public annual_holiday
	{

	public:

		explicit weekday_indexed_holiday(std::chrono::month_weekday mwd) noexcept;

	public:

		auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_weekday _mwd;

	};


	class weekday_last_holiday final : public annual_holiday
	{

	public:

		explicit weekday_last_holiday(std::chrono::month_weekday_last mwd) noexcept;

	public:

		auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_weekday_last _mwd;

	};



	// https://en.wikipedia.org/wiki/Date_of_Easter

	inline auto make_easter(const std::chrono::year& y) noexcept -> std::chrono::year_month_day
	{
		const auto Y = static_cast<int>(y);

		const auto a = Y % 19;

		const auto b = static_cast<int>(std::floor(static_cast<double>(Y) / 100.0));

		const auto c = Y % 100;

		const auto d = static_cast<int>(std::floor(static_cast<double>(b) / 4.0));

		const auto e = b % 4;

		const auto g = static_cast<int>(std::floor((8.0 * static_cast<double>(b) + 13.0) / 25.0));

		const auto h = (19 * a + b - d - g + 15) % 30;

		const auto i = static_cast<int>(std::floor(static_cast<double>(c) / 4.0));

		const auto k = c % 4;

		const auto l = (32 + 2 * e + 2 * i - h - k) % 7;

		const auto m = static_cast<int>(std::floor((static_cast<double>(a) + 11.0 * static_cast<double>(h) + 19.0 * static_cast<double>(l)) / 433.0));

		const auto n = static_cast<int>(std::floor((static_cast<double>(h) + static_cast<double>(l) - 7.0 * static_cast<double>(m) + 90.0) / 25.0));

		const auto p = (h + l - 7 * m + 33 * n + 19) % 32;

		return { y, std::chrono::month{ static_cast<unsigned>(n) }, std::chrono::day{ static_cast<unsigned>(p) } };
	}



	inline auto good_friday_holiday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		const auto easterSunday = make_easter(y);

		return std::chrono::sys_days{ easterSunday } - std::chrono::days{ 2 };
	}


	inline auto easter_monday_holiday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		const auto easterSunday = make_easter(y);

		return std::chrono::sys_days{ easterSunday } + std::chrono::days{ 1 };
	}



	inline named_holiday::named_holiday(std::chrono::month_day md) noexcept :
		_md{ std::move(md) }
	{
	}


	inline auto named_holiday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return { y, _md.month(), _md.day() };
	}



	inline weekday_indexed_holiday::weekday_indexed_holiday(std::chrono::month_weekday mwd) noexcept :
		_mwd{ std::move(mwd) }
	{
	}


	inline auto weekday_indexed_holiday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return { _mwd.weekday_indexed() / _mwd.month() / y };
	}



	inline weekday_last_holiday::weekday_last_holiday(std::chrono::month_weekday_last mwd) noexcept :
		_mwd{ std::move(mwd) }
	{
	}


	inline auto weekday_last_holiday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return { _mwd.weekday_last() / _mwd.month() / y };
	}

}
