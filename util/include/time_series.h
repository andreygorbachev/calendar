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

#include <chrono>
#include <vector>
#include <utility>
#include <stdexcept>
#include <compare>
#include <bitset>


namespace gregorian
{

	namespace util
	{

		template<typename T>
		class time_series final
		{

		public:

			explicit time_series(const util::days_period& period) noexcept;

		private:

			explicit time_series(const util::period<std::chrono::sys_days> period) noexcept;
			// at the moment we have year/month/day interface,
			// but maybe we should have both year/month/day and sys_days interfaces
			// (what should get_period return in this case?)
			// we already have a sys_days interface for operator[] and _time_series<bool>::count

		public:

			friend auto operator==(const time_series& ts1, const time_series& ts2) noexcept -> bool = default;
			friend auto operator<=>(const time_series& ts1, const time_series& ts2) noexcept -> std::strong_ordering = delete;

		public:

			auto operator[](const std::chrono::year_month_day& ymd)->T&;
			auto operator[](const std::chrono::year_month_day& ymd) const -> const T&;

			auto operator[](const std::chrono::sys_days& sd)->T&;
			auto operator[](const std::chrono::sys_days& sd) const -> const T&;

		public:

			auto get_period() const noexcept -> util::days_period;

		private:

			auto _index(const std::chrono::sys_days& sd) const -> std::size_t;

		private:

			util::period<std::chrono::sys_days> _period;

			std::vector<T> _observations;

		};



		template<>
		class time_series<bool>
		{

		private:

			static const auto _chunk_size = std::size_t{ 64u }; // maybe consider 128/256/512 to align with SSE/AVX
			// we store bools in bitset chunks of this size (such that we can popcount them efficiently)

		public:

			using _chunk = std::bitset<_chunk_size>;

			using reference = _chunk::reference;

		public:

			explicit time_series(const util::days_period& period) noexcept;

		private:

			explicit time_series(const util::period<std::chrono::sys_days> period) noexcept;

		public:

			friend auto operator==(const time_series& ts1, const time_series& ts2) noexcept -> bool = default;
			friend auto operator<=>(const time_series& ts1, const time_series& ts2) noexcept -> std::strong_ordering = delete;

		public:

			auto operator[](const std::chrono::year_month_day& ymd) -> reference;
			auto operator[](const std::chrono::year_month_day& ymd) const -> bool;

			auto operator[](const std::chrono::sys_days& sd) -> reference;
			auto operator[](const std::chrono::sys_days& sd) const -> bool;

		public:

			auto get_period() const noexcept -> util::days_period;

		public:

			auto count(const util::days_period& p) const -> std::size_t;
			auto count(const util::period<std::chrono::sys_days>& p) const -> std::size_t;

		public:

			// to help with testing
			static auto get_chunk_size() noexcept -> std::size_t;

		private:

			auto _index_outer(const std::chrono::sys_days& sd) const -> std::size_t;
			auto _index_inner(const std::chrono::sys_days& sd) const -> std::size_t;

		private:

			util::period<std::chrono::sys_days> _period;

			using _storage = std::vector<_chunk>;

			_storage _observations;

		};



		template<typename T>
		time_series<T>::time_series(const util::days_period& period) noexcept :
			time_series{ util::period<std::chrono::sys_days>{ period.get_from(), period.get_until() } }
		{
		}

		template<typename T>
		time_series<T>::time_series(const util::period<std::chrono::sys_days> period) noexcept :
			_period{ std::move(period) },
			_observations(_index(_period.get_until()) + std::size_t{ 1u })
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
		auto time_series<T>::operator[](const std::chrono::sys_days& sd) -> T&
		{
			return _observations[_index(sd)];
		}

		template<typename T>
		auto time_series<T>::operator[](const std::chrono::sys_days& sd) const -> const T&
		{
			return _observations[_index(sd)];
		}


		template<typename T>
		auto time_series<T>::get_period() const noexcept -> util::days_period
		{
			return util::days_period{ _period.get_from(), _period.get_until() };
		}


		template<typename T>
		auto time_series<T>::_index(const std::chrono::sys_days& sd) const -> std::size_t
		{
			if (sd < _period.get_from() || sd > _period.get_until())
				throw std::out_of_range{ "Request is not consistent with from/until" };

			const auto days = sd - _period.get_from();
			return days.count();
		}



		inline time_series<bool>::time_series(const util::days_period& period) noexcept :
			time_series{ util::period<std::chrono::sys_days>{ period.get_from(), period.get_until() } }
		{
		}

		inline time_series<bool>::time_series(const util::period<std::chrono::sys_days> period) noexcept :
			_period{ std::move(period) },
			_observations(_index_outer(_period.get_until()) + std::size_t{ 1u })
		{
		}


		inline auto time_series<bool>::operator[](const std::chrono::year_month_day& ymd) -> reference
		{
			return _observations[_index_outer(ymd)][_index_inner(ymd)];
		}

		inline auto time_series<bool>::operator[](const std::chrono::year_month_day& ymd) const -> bool
		{
			return _observations[_index_outer(ymd)][_index_inner(ymd)];
		}

		inline auto time_series<bool>::operator[](const std::chrono::sys_days& sd) -> reference
		{
			return _observations[_index_outer(sd)][_index_inner(sd)];
		}

		inline auto time_series<bool>::operator[](const std::chrono::sys_days& sd) const -> bool
		{
			return _observations[_index_outer(sd)][_index_inner(sd)];
		}


		inline auto time_series<bool>::get_period() const noexcept -> util::days_period
		{
			return util::days_period{ _period.get_from(), _period.get_until() };
		}


		inline auto time_series<bool>::get_chunk_size() noexcept -> std::size_t
		{
			return _chunk_size;
		}


		inline auto time_series<bool>::_index_outer(const std::chrono::sys_days& sd) const -> std::size_t
		{
			if (sd < _period.get_from() || sd > _period.get_until())
				throw std::out_of_range{ "Request is not consistent with from/until" };

			const auto days = sd - _period.get_from();
			return days.count() / _chunk_size;
		}

		inline auto time_series<bool>::_index_inner(const std::chrono::sys_days& sd) const -> std::size_t
		{
			if (sd < _period.get_from() || sd > _period.get_until())
				throw std::out_of_range{ "Request is not consistent with from/until" };

			const auto days = sd - _period.get_from();
			return days.count() % _chunk_size;
		}

		inline auto time_series<bool>::count(const util::days_period& p) const -> std::size_t
		{
			return count(util::period<std::chrono::sys_days>{ p.get_from(), p.get_until() });
		}

		// possible faster implementation could be to have another cache of _hols
		// if we are to have them as a sorted vector and make sure none of them duplicate weekends
		// we should be able to compute number of full weeks between from and until
		// (which would give us 5 business days each),
		// adjust for (possibly) incomplete from and until weeks
		// and then addjust for a number of _hols that fall into the period
		//
		// for rule based calendars with adjustments for holidays that fall on weekends
		// we also know the number of additional holidays per year (which is just the number of rules)
		// which can further optimise the calculation
		inline auto time_series<bool>::count(const util::period<std::chrono::sys_days>& p) const -> std::size_t
		{
			using namespace std::chrono;

			auto result = 0uz;

			const auto from = p.get_from();
			const auto from_chunk_index = _index_outer(from);

			const auto until = p.get_until();
			const auto until_chunk_index = _index_outer(until);

			// handle the chunk that contains from
			const auto& from_chunk = _observations[from_chunk_index];
			for (auto i = _index_inner(from); i < _chunk_size; ++i)
				if (from_chunk[i])
					result++;
			// naive implementation to start with

			// full chunks in the middle (after the from chunk, but including the chunk that contains until)
			for (
				auto j = from_chunk_index + 1uz;
				j <= until_chunk_index;
				++j
			)
				result += _observations[j].count();
			// naive implementation to start with

			// handle the chunk that contains until
			const auto& until_chunk = _observations[until_chunk_index];
			for (auto i = _index_inner(until) + 1uz; i < _chunk_size; ++i)
				if (until_chunk[i])
					result--;
			// naive implementation to start with

			// can we factor out some common code for the first and last parts?

			return result;
		}

	}

}
