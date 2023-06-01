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
#include <memory>
#include <stdexcept>


namespace calendar
{

	class period
	{

	public:

		period() noexcept = delete;
		period(const period&) = default;
		period(period&&) noexcept = default;

		period(
			std::chrono::year_month_day f,
			std::chrono::year_month_day u
		);

		~period() noexcept = default;

		period& operator=(const period&) = default;
		period& operator=(period&&) noexcept = default;

	public:

		friend auto operator==(const period& p1, const period& p2) noexcept -> bool = default;

	public:

		auto get_from() const noexcept -> const std::chrono::year_month_day&;
		auto get_until() const noexcept -> const std::chrono::year_month_day&;

	private:

		std::chrono::year_month_day _f;
		std::chrono::year_month_day _u;

	};



	inline auto operator+(const period& p1, const period& p2) -> period
	{
		if (p1.get_from() > p2.get_from())
			return p2 + p1;

		if (p1.get_until() <= p2.get_from()) // for now we assume that until is included
			throw std::out_of_range{ "Periods are not consistent" };

		return { p1.get_from(), p2.get_until() };
	}



	inline period::period(
		std::chrono::year_month_day f,
		std::chrono::year_month_day u
	) :
		_f{ std::move(f) },
		_u{ std::move(u) }
	{
		if (f > u)
			throw std::out_of_range{ "From and until are not consistent" };
	}


	inline auto period::get_from() const noexcept -> const std::chrono::year_month_day&
	{
		return _f;
	}

	inline auto period::get_until() const noexcept -> const std::chrono::year_month_day&
	{
		return _u;
	}

}
