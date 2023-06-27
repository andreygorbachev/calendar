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

#include "period.h"

#include <chrono>
#include <vector>
#include <memory>
#include <stdexcept>


namespace gregorian
{

	template<typename T>
	class time_series // or should we use an existing library like tslib (GitHub)?
	{

	public:

		time_series() noexcept = delete; // or we'll have to figure out what an "empty" time_series is (especially as there is no default constructor for days_period)
		time_series(const time_series&) = default;
		time_series(time_series&&) noexcept = default;

		~time_series() noexcept = default;

		time_series& operator=(const time_series&) = default;
		time_series& operator=(time_series&&) noexcept = default;

		explicit time_series(gregorian::days_period period) noexcept;

	public:

		friend auto operator==(const time_series& ts1, const time_series& ts2) noexcept -> bool = default;

	public:

		auto operator[](const std::chrono::year_month_day& ymd) -> T&;
		auto operator[](const std::chrono::year_month_day& ymd) const -> const T&;

	public:

		auto get_period() const noexcept -> const gregorian::days_period&;

	private:

		auto _index(const std::chrono::year_month_day& ymd) const -> std::size_t;

	private:

		gregorian::days_period _period; // or should we consider other time steps (rather than just daily)?

		std::vector<T> _observations;

	};



	template<>
	class time_series<bool>
	{

	public:

		time_series() noexcept = delete;
		time_series(const time_series&) = default;
		time_series(time_series&&) noexcept = default;

		~time_series() noexcept = default;

		time_series& operator=(const time_series&) = default;
		time_series& operator=(time_series&&) noexcept = default;

		explicit time_series(gregorian::days_period period) noexcept;

	public:

		friend auto operator==(const time_series& ts1, const time_series& ts2) noexcept -> bool = default;

	public:

		auto operator[](const std::chrono::year_month_day& ymd) -> std::vector<bool>::reference;
		auto operator[](const std::chrono::year_month_day& ymd) const -> std::vector<bool>::const_reference;

	public:

		auto get_period() const noexcept -> const gregorian::days_period&;

	private:

		auto _index(const std::chrono::year_month_day& ymd) const->std::size_t;

	private:

		gregorian::days_period _period; // or should we consider other time steps (rather than just daily)?

		std::vector<bool> _observations;

	};



	template<typename T>
	time_series<T>::time_series(gregorian::days_period period) noexcept :
		_period{ std::move(period) },
		_observations(_index(_period.get_until()) + 1/*uz*/)
	{
	}


	template<typename T>
	auto time_series<T>::operator[](const std::chrono::year_month_day& ymd) -> T&
	{
		return _observations[_index(ymd)];
	}

	template<typename T>
	auto time_series<T>::operator[](const std::chrono::year_month_day& ymd) const -> const T&
	{
		return _observations[_index(ymd)];
	}


	template<typename T>
	auto time_series<T>::get_period() const noexcept -> const gregorian::days_period&
	{
		return _period;
	}


	template<typename T>
	auto time_series<T>::_index(const std::chrono::year_month_day& ymd) const -> std::size_t
	{
		if (ymd < _period.get_from() || ymd > _period.get_until())
			throw std::out_of_range{ "Request is not consistent with from/until" };

		const auto days = std::chrono::sys_days{ ymd } - std::chrono::sys_days{ _period.get_from() };
		return days.count();
	}



	inline time_series<bool>::time_series(gregorian::days_period period) noexcept :
		_period{ std::move(period) },
		_observations(_index(_period.get_until()) + 1/*uz*/)
	{
	}


	inline auto time_series<bool>::operator[](const std::chrono::year_month_day& ymd) -> std::vector<bool>::reference
	{
		return _observations[_index(ymd)];
	}

	inline auto time_series<bool>::operator[](const std::chrono::year_month_day& ymd) const -> std::vector<bool>::const_reference
	{
		return _observations[_index(ymd)];
	}


	inline auto time_series<bool>::get_period() const noexcept -> const gregorian::days_period&
	{
		return _period;
	}


	inline auto time_series<bool>::_index(const std::chrono::year_month_day& ymd) const -> std::size_t
	{
		if (ymd < _period.get_from() || ymd > _period.get_until())
			throw std::out_of_range{ "Request is not consistent with from/until" };

		const auto days = std::chrono::sys_days{ ymd } - std::chrono::sys_days{ _period.get_from() };
		return days.count();
	}

}
