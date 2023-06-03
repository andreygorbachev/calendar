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

	template<typename T> class period
	{

	public:

		period() noexcept = delete;
		period(const period&) = default;
		period(period&&) noexcept = default;

		period(T from, T until);

		~period() noexcept = default;

		period& operator=(const period&) = default;
		period& operator=(period&&) noexcept = default;

	public:

		friend auto operator==(const period& p1, const period& p2) noexcept -> bool = default;

	public:

		auto get_from() const noexcept -> const T&;
		auto get_until() const noexcept -> const T&;

	private:

		T _from;
		T _until;

	};


	using days_period = period<std::chrono::year_month_day>;
	using months_period = period<std::chrono::year_month>;
	using years_period = period<std::chrono::year>;


	// maybe consider a method for an intersection of 2 periods?


	template<typename T>
	period<T>::period(T from, T until) :
		_from{ std::move(from) },
		_until{ std::move(until) }
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

}
