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
#include <algorithm>
#include <stdexcept>
#include <compare>


namespace gregorian
{

	template<typename T> class period
	{

	public:

		period() noexcept = delete;
		period(const period&) = default;
		period(period&&) noexcept = default;

		period(const T& from, const T& until);

		~period() noexcept = default;

		period& operator=(const period&) = default;
		period& operator=(period&&) noexcept = default;

	public:

		friend auto operator==(const period& p1, const period& p2) noexcept -> bool = default;
		friend auto operator<=>(const period& p1, const period& p2) noexcept -> std::strong_ordering = delete;

	public:

		auto get_from() const noexcept -> const T&;
		auto get_until() const noexcept -> const T&;

	public:

		auto contains(const T& x) const noexcept -> bool;

	private:

		T _from;
		T _until;

	};


	using days_period = period<std::chrono::year_month_day>;
	using months_period = period<std::chrono::year_month>;
	using years_period = period<std::chrono::year>;


	inline auto operator+(const days_period& p1, const days_period& p2) -> days_period
	{
		if (std::chrono::sys_days{ p2.get_from() } - std::chrono::sys_days{ p1.get_until() } != std::chrono::days{ 1 })
			throw std::out_of_range{ "From and until are not consistent" };

		return { p1.get_from(), p2.get_until() };
	}

	inline auto operator+(const months_period& p1, const months_period& p2) -> months_period
	{
		if (p2.get_from() - p1.get_until() != std::chrono::months{ 1 })
			throw std::out_of_range{ "From and until are not consistent" };

		return { p1.get_from(), p2.get_until() };
	}

	inline auto operator+(const years_period& p1, const years_period& p2) -> years_period
	{
		if (p2.get_from() - p1.get_until() != std::chrono::years{ 1 })
			throw std::out_of_range{ "From and until are not consistent" };

		return { p1.get_from(), p2.get_until() };
	}


	inline auto operator&(const days_period& p1, const days_period& p2) -> days_period
	{
		if (p1.get_from() > p2.get_from())
			return p2 & p1;

		return { std::max(p1.get_from(), p2.get_from()), std::min(p1.get_until(), p2.get_until()) };
	}

	inline auto operator|(const days_period& p1, const days_period& p2) -> days_period
	{
		if (p1.get_from() > p2.get_from())
			return p2 | p1;

		if (p1.get_until() < p2.get_from())
			throw std::out_of_range{ "From and until are not consistent" };

		return { std::min(p1.get_from(), p2.get_from()), std::max(p1.get_until(), p2.get_until()) };
	}


	template<typename T>
	period<T>::period(const T& from, const T& until) :
		_from{ from },
		_until{ until }
	{
		if (_from > _until)
			throw std::out_of_range{ "From and until are not consistent" };
	}


	template<typename T>
	auto period<T>::get_from() const noexcept -> const T&
	{
		return _from;
	}

	template<typename T>
	auto period<T>::get_until() const noexcept -> const T&
	{
		return _until;
	}


	template<typename T>
	auto period<T>::contains(const T& x) const noexcept -> bool
	{
		return _from <= x && x <= _until;
	}

}
