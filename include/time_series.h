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

// this is an internal header (nothing here is expected to be used directly for now)

#include "period.h"

#include <chrono>
#include <vector>
#include <memory>
#include <stdexcept>
#include <compare>
#include <bitset>


namespace gregorian
{

	template<typename T>
	class _time_series final
	{

	public:

		_time_series() noexcept = delete; // or we'll have to figure out what an "empty" _time_series is (especially as there is no default constructor for days_period)
		_time_series(const _time_series&) = default;
		_time_series(_time_series&&) noexcept = default;

		~_time_series() noexcept = default;

		_time_series& operator=(const _time_series&) = default;
		_time_series& operator=(_time_series&&) noexcept = default;

		explicit _time_series(const gregorian::days_period& period) noexcept;

	public:

		friend auto operator==(const _time_series& ts1, const _time_series& ts2) noexcept -> bool = default;
		friend auto operator<=>(const _time_series& ts1, const _time_series& ts2) noexcept -> std::strong_ordering = delete;

	public:

		auto operator[](const std::chrono::year_month_day& ymd) -> T&;
		auto operator[](const std::chrono::year_month_day& ymd) const -> const T&;

		auto operator[](const std::chrono::sys_days& sd) -> T&;
		auto operator[](const std::chrono::sys_days& sd) const -> const T&;

	public:

		auto get_period() const noexcept -> gregorian::days_period;

	private:

		auto _index(const std::chrono::sys_days& sd) const -> std::size_t;

	private:

		gregorian::period<std::chrono::sys_days> _period;

		std::vector<T> _observations;

	};



	template<>
	class _time_series<bool>
	{

	private:

		static const auto _chunk_size = std::size_t{ 64u }; // uz // maybe consider 128/256/512 to align with SSE/AVX
		// we store bools in bitset chunks of this size (such that we can popcount them efficiently)

	public:

		using _chunk = std::bitset<_chunk_size>;

		using reference = _chunk::reference;

	public:

		_time_series() noexcept = delete;
		_time_series(const _time_series&) = default;
		_time_series(_time_series&&) noexcept = default;

		~_time_series() noexcept = default;

		_time_series& operator=(const _time_series&) = default;
		_time_series& operator=(_time_series&&) noexcept = default;

		explicit _time_series(const gregorian::days_period& period) noexcept;

	public:

		friend auto operator==(const _time_series& ts1, const _time_series& ts2) noexcept -> bool = default;
		friend auto operator<=>(const _time_series& ts1, const _time_series& ts2) noexcept -> std::strong_ordering = delete;

	public:

		auto operator[](const std::chrono::year_month_day& ymd) -> reference;
		auto operator[](const std::chrono::year_month_day& ymd) const -> bool;

		auto operator[](const std::chrono::sys_days& sd) -> reference;
		auto operator[](const std::chrono::sys_days& sd) const -> bool;

	public:

		auto get_period() const noexcept -> gregorian::days_period;

	public:

		auto count(const days_period& from_until) const -> std::size_t;
		auto count(const period<std::chrono::sys_days>& from_until) const -> std::size_t;

	public:

		// to help with testing
		static auto get_chunk_size() noexcept -> std::size_t;

	private:

		auto _index_outer(const std::chrono::sys_days& sd) const -> std::size_t;
		auto _index_inner(const std::chrono::sys_days& sd) const -> std::size_t;

	private:

		gregorian::period<std::chrono::sys_days> _period;

		using _storage = std::vector<_chunk>;

		_storage _observations;

	};



	template<typename T>
	_time_series<T>::_time_series(const gregorian::days_period& period) noexcept :
		_period{ period.get_from(), period.get_until() },
		_observations(_index(_period.get_until()) + 1/*uz*/)
	{
	}


	template<typename T>
	auto _time_series<T>::operator[](const std::chrono::year_month_day& ymd) -> T&
	{
		return _observations[_index(ymd)];
	}

	template<typename T>
	auto _time_series<T>::operator[](const std::chrono::year_month_day& ymd) const -> const T&
	{
		return _observations[_index(ymd)];
	}

	template<typename T>
	auto _time_series<T>::operator[](const std::chrono::sys_days& sd) -> T&
	{
		return _observations[_index(sd)];
	}

	template<typename T>
	auto _time_series<T>::operator[](const std::chrono::sys_days& sd) const -> const T&
	{
		return _observations[_index(sd)];
	}


	template<typename T>
	auto _time_series<T>::get_period() const noexcept -> gregorian::days_period
	{
		return gregorian::days_period{ _period.get_from(), _period.get_until() };
	}


	template<typename T>
	auto _time_series<T>::_index(const std::chrono::sys_days& sd) const -> std::size_t
	{
		if (sd < _period.get_from() || sd > _period.get_until())
			throw std::out_of_range{ "Request is not consistent with from/until" };

		const auto days = sd - _period.get_from();
		return days.count();
	}



	inline _time_series<bool>::_time_series(const gregorian::days_period& period) noexcept :
		_period{ period.get_from(), period.get_until() },
		_observations(_index_outer(_period.get_until()) + 1/*zu*/)
	{
	}


	inline auto _time_series<bool>::operator[](const std::chrono::year_month_day& ymd) -> reference
	{
		return _observations[_index_outer(ymd)][_index_inner(ymd)];
	}

	inline auto _time_series<bool>::operator[](const std::chrono::year_month_day& ymd) const -> bool
	{
		return _observations[_index_outer(ymd)][_index_inner(ymd)];
	}

	inline auto _time_series<bool>::operator[](const std::chrono::sys_days& sd) -> reference
	{
		return _observations[_index_outer(sd)][_index_inner(sd)];
	}

	inline auto _time_series<bool>::operator[](const std::chrono::sys_days& sd) const -> bool
	{
		return _observations[_index_outer(sd)][_index_inner(sd)];
	}


	inline auto _time_series<bool>::get_period() const noexcept -> gregorian::days_period
	{
		return gregorian::days_period{ _period.get_from(), _period.get_until() };
	}


	inline auto _time_series<bool>::get_chunk_size() noexcept -> std::size_t
	{
		return _chunk_size;
	}


	inline auto _time_series<bool>::_index_outer(const std::chrono::sys_days& sd) const -> std::size_t
	{
		if (sd < _period.get_from() || sd > _period.get_until())
			throw std::out_of_range{ "Request is not consistent with from/until" };

		const auto days = sd - _period.get_from();
		return days.count() / _chunk_size;
	}

	inline auto _time_series<bool>::_index_inner(const std::chrono::sys_days& sd) const -> std::size_t
	{
		if (sd < _period.get_from() || sd > _period.get_until())
			throw std::out_of_range{ "Request is not consistent with from/until" };

		const auto days = sd - _period.get_from();
		return days.count() % _chunk_size;
	}

	inline auto _time_series<bool>::count(const days_period& from_until) const -> std::size_t
	{
		auto result = std::size_t{ 0 };

		// naive implementation to start with
		for (
			auto d = from_until.get_from();
			d <= from_until.get_until();
			d = std::chrono::sys_days{ d } + std::chrono::days{ 1 }
		)
			if (operator[](d))
				result++;

		return result;
	}

	inline auto _time_series<bool>::count(const period<std::chrono::sys_days>& from_until) const -> std::size_t
	{
		auto result = std::size_t{ 0 };

		// naive implementation to start with
		for (
			auto d = from_until.get_from();
			d <= from_until.get_until();
			d += std::chrono::days{ 1 }
		)
			if (operator[](d))
				result++;

		return result;
	}

}
