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

#include <chrono>
#include <bitset>
#include <utility>
#include <compare>


namespace gregorian
{

	constexpr auto week_length = std::size_t{ std::chrono::Sunday.iso_encoding() };


	class weekend final
	{

	public:

		using storage = std::bitset<week_length>;

	public:

		// should Saturday/Sunday be a default?

		constexpr explicit weekend(storage we) noexcept;

	public:

		constexpr friend auto operator==(const weekend& w1, const weekend& w2) noexcept -> bool = default;
		constexpr friend auto operator<=>(const weekend& w1, const weekend& w2) noexcept -> std::strong_ordering = delete;

	public:

		constexpr auto is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool;

		constexpr auto is_weekend(const std::chrono::sys_days& sd) const noexcept -> bool;

	public:

		constexpr auto get_we() const noexcept -> const storage&;

	private:

		storage _we;

	};


	const auto SaturdaySundayWeekend = weekend{ weekend::storage{ 0b1000001 } };
	const auto FridaySaturdayWeekend = weekend{ weekend::storage{ 0b1100000 } };
	const auto SundayWeekend = weekend{ weekend::storage{ 0b0000001 } };
	const auto NoWeekend = weekend{ weekend::storage{ 0b0000000 } };



	constexpr auto operator|(const weekend& w1, const weekend& w2) noexcept -> weekend
	{
		auto we = w1.get_we() | w2.get_we();

		return weekend{ std::move(we) };
	}

	constexpr auto operator&(const weekend& w1, const weekend& w2) noexcept -> weekend
	{
		auto we = w1.get_we() & w2.get_we();

		return weekend{ std::move(we) };
	}



	constexpr weekend::weekend(storage we) noexcept : _we{ std::move(we) }
	{
	}


	constexpr auto weekend::is_weekend(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		return is_weekend(std::chrono::sys_days{ ymd });
	}

	constexpr auto weekend::is_weekend(const std::chrono::sys_days& sd) const noexcept -> bool
	{
		const auto wd = std::chrono::weekday{ sd };

		return _we[wd.c_encoding()];
	}

	constexpr auto weekend::get_we() const noexcept -> const storage&
	{
		return _we;
	}

}
