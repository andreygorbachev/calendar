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

#include "annual_holiday_interface.h"
#include "schedule.h"

#include <chrono>
#include <utility>


namespace gregorian
{

	class named_holiday final : public annual_holiday
	{

	public:

		explicit constexpr named_holiday(std::chrono::month_day md) noexcept;

	private:

		constexpr auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_day _md;

	};



	class _easter_holiday final : public annual_holiday
	{

	private:

		constexpr auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	};



	class offset_holiday final : public annual_holiday
	{

	public:

		// offset_holiday stores a pointer to holiday - is there a better way to do this?
		explicit constexpr offset_holiday(const annual_holiday* const holiday, std::chrono::days offset) noexcept;

	private:

		constexpr auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		const annual_holiday* _holiday;
		std::chrono::days _offset;

	};



	class weekday_indexed_holiday final : public annual_holiday
	{

	public:

		explicit constexpr weekday_indexed_holiday(std::chrono::month_weekday mwd) noexcept;

	private:

		constexpr auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_weekday _mwd;

	};


	class weekday_last_holiday final : public annual_holiday
	{

	public:

		explicit constexpr weekday_last_holiday(std::chrono::month_weekday_last mwd) noexcept;

	private:

		constexpr auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_weekday_last _mwd;

	};



	inline constexpr named_holiday::named_holiday(std::chrono::month_day md) noexcept :
		_md{ std::move(md) }
	{
	}


	inline constexpr auto named_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return { y, _md.month(), _md.day() };
	}



	// from https://en.wikipedia.org/wiki/Date_of_Easter

	inline constexpr auto _easter_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		const auto Y = static_cast<int>(y);

		const auto a = Y % 19;

		const auto b = Y / 100;

		const auto c = Y % 100;

		const auto d = b / 4;

		const auto e = b % 4;

		const auto g = (8 * b + 13) / 25;

		const auto h = (19 * a + b - d - g + 15) % 30;

		const auto i = c / 4;

		const auto k = c % 4;

		const auto l = (32 + 2 * e + 2 * i - h - k) % 7;

		const auto m = (a + 11 * h + 19 * l) / 433;

		const auto n = (h + l - 7 * m + 90) / 25;

		const auto p = (h + l - 7 * m + 33 * n + 19) % 32;

		return { y, std::chrono::month{ static_cast<unsigned>(n) }, std::chrono::day{ static_cast<unsigned>(p) } };
	}



	inline constexpr offset_holiday::offset_holiday(const annual_holiday* const holiday, std::chrono::days offset) noexcept :
		_holiday{ holiday },
		_offset{ std::move(offset) }
	{
	}


	inline constexpr auto offset_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		const auto d = _holiday->make_holiday(y);
		return std::chrono::sys_days{ d } + _offset;
	}



	inline constexpr weekday_indexed_holiday::weekday_indexed_holiday(std::chrono::month_weekday mwd) noexcept :
		_mwd{ std::move(mwd) }
	{
	}


	inline constexpr auto weekday_indexed_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return { _mwd.weekday_indexed() / _mwd.month() / y };
	}



	inline constexpr weekday_last_holiday::weekday_last_holiday(std::chrono::month_weekday_last mwd) noexcept :
		_mwd{ std::move(mwd) }
	{
	}


	inline constexpr auto weekday_last_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return { _mwd.weekday_last() / _mwd.month() / y };
	}



	inline constexpr auto NewYearsDay = named_holiday{ FirstDayOfJanuary };
	inline constexpr auto ChristmasDay = named_holiday{ std::chrono::December / std::chrono::day{ 25u } };

	inline constexpr auto NewYearsEve = named_holiday{ LastDayOfDecember };
	// NewYearsEve is created as a named_holiday (instead of an offset_holiday like ChrismasEve)
	// because we do not want to cross a year's boundary, which we would have to do otherwise

	inline constexpr auto _Easter = _easter_holiday{};

	inline constexpr auto GoodFriday = offset_holiday{ &_Easter, std::chrono::days{ -2 } };
	inline constexpr auto EasterMonday = offset_holiday{ &_Easter, std::chrono::days{ 1 } };
	inline constexpr auto AscensionDay = offset_holiday{ &_Easter, std::chrono::days{ 39 } };
	inline constexpr auto WhitMonday = offset_holiday{ &_Easter, std::chrono::days{ 50 } };
	inline constexpr auto ChristmasEve = offset_holiday{ &ChristmasDay, std::chrono::days{ -1 } };
	inline constexpr auto BoxingDay = offset_holiday{ &ChristmasDay, std::chrono::days{ 1 } };

}
