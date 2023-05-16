#pragma once

#include "weekend.h"
#include "holiday_schedule.h"
#include "business_day_convention_interface.h"

#include <cstddef>
#include <memory>
#include <chrono>
#include <vector>
//#include <stdexcept>


namespace calendar
{

	class calendar
	{

	public:

		explicit calendar(weekend we, holiday_schedule hols);

	public:

		friend auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool;

	public:

		auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

		auto count_business_days(
			const std::chrono::year_month_day& start,
			const std::chrono::year_month_day& end
		) const -> std::size_t;
		// if end is before start should the function swap them around? (or return a negative number? or throw an exception)
		// if we need to return a negative number then the return should not be std::size_t (which we might want to change anyway)
		// should we consider calling start "front" and end "back" to be more consistent with STL
		// (or should we operate with "begin"/"end" ideas here instead)
		// there is also std::chrono::last

		// would "*" and "[]" make some sence here?
		// iterators?
		// serial dates?

	public:

		// think about better names
		auto front() const noexcept -> const std::chrono::year_month_day&;
		auto back() const noexcept -> const std::chrono::year_month_day&;

	public:

		void substitute(const business_day_convention* const bdc);

		// should we be thinking about subsets?
		// (for example if cal1 is a wider calendar than cal2,
		// but cal2 matches cal1 over its range)

	public:

		auto get_weekend() const noexcept -> const weekend&;
		auto get_holiday_schedule() const noexcept -> const holiday_schedule&;

	private:

		void _make_bd_cache();

		auto _get_index(const std::chrono::year_month_day& ymd) const noexcept -> std::size_t;

		auto _is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

		// we can try to factor out the cache as an (inner) class
		// (to make it clear what is what)

	private:

		weekend _we;
		holiday_schedule _hols;

	private:

		using _business_day_storage = std::vector<bool>;
		// do we need some notion of a "time series"?
		// (where we have a value for each day, etc)

		_business_day_storage _bd_cache;

	};



	inline auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool
	{
		return cal1._bd_cache == cal2._bd_cache;
	}


	inline auto operator|(const calendar& cal1, const calendar& cal2) -> calendar
	{
		return calendar{
			cal1.get_weekend() | cal2.get_weekend(),
			cal2.get_holiday_schedule() | cal2.get_holiday_schedule()
		};
	}

	inline auto operator&(const calendar& cal1, const calendar& cal2) -> calendar
	{
		return calendar{
			cal1.get_weekend() & cal2.get_weekend(),
			cal2.get_holiday_schedule() & cal2.get_holiday_schedule()
		}; // is this right?
	}



	inline calendar::calendar(
		weekend we,
		holiday_schedule hols
	) :
		_we{ we },
		_hols{ hols }
	{
		_make_bd_cache();
	}


	inline void calendar::_make_bd_cache()
	{
		const auto size = _get_index(back()) + 1/*uz*/;

		_bd_cache.resize(size);

		const auto& f = front();

		for (auto i = std::size_t{ 0/*uz*/ }; i < size; ++i)
		{
			const auto d = std::chrono::sys_days{ f } + std::chrono::days{ i };
			_bd_cache[i] = _is_business_day(d);
		}
	}

	inline auto calendar::_get_index(const std::chrono::year_month_day& ymd) const noexcept -> std::size_t
	{
		const auto days = std::chrono::sys_days{ ymd } - std::chrono::sys_days{ front() };
		return days.count();
	}

	inline auto calendar::_is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
//		if (ymd < front() || ymd > back())
//			throw std::out_of_range{ "" }; // complete the message
		// we should decide if this is an exception or not
		// if it is an exception - should it go to holiday_schedule?

		return !_we.is_weekend(ymd) && !_hols.is_holiday(ymd);
		// we allow a holiday on a weekend
	}


	inline void calendar::substitute(const business_day_convention* const bdc)
	{
		const auto hols = _hols.get_hols();
		for (const auto& holiday : hols)
		{
			_hols -= holiday;
			if (!_is_business_day(holiday))
			{
				const auto substitute_day = bdc->adjust(holiday, *this);
				_hols += substitute_day;
				_make_bd_cache(); // we do not actually need to fully rebuild the cache, so this could be optimised
			}
			else
			{
				_hols += holiday;
			}
		}

		// what happens if we have an exception?
	}


	inline auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
//		if (ymd < front() || ymd > back())
//			throw std::out_of_range{ "" }; // complete the message
		// we should decide if this is an exception or not
		// if it is an exception - should it go to holiday_schedule?

		return _bd_cache[_get_index(ymd)];
	}

	inline auto calendar::count_business_days(
		const std::chrono::year_month_day& start,
		const std::chrono::year_month_day& end
	) const -> std::size_t
	{
		auto result = std::size_t{ 0 };

		// naive implementation to start with
		for (auto d = start; d <= end; d = std::chrono::sys_days{ d } + std::chrono::days{ 1 })
			if (is_business_day(d))
				result++;

		return result;
	}


	inline auto calendar::front() const noexcept -> const std::chrono::year_month_day&
	{
		return _hols.get_front();
	}

	inline auto calendar::back() const noexcept -> const std::chrono::year_month_day&
	{
		return _hols.get_back();
	}


	inline auto calendar::get_weekend() const noexcept -> const weekend&
	{
		return _we;
	}

	inline auto calendar::get_holiday_schedule() const noexcept -> const holiday_schedule&
	{
		return _hols;
	}

}
