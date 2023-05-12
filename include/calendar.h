#pragma once

#include "weekend.h"
#include "holiday_schedule.h"
#include "business_day_convention_interface.h"

#include <cstddef>
#include <memory>
#include <chrono>


namespace calendar
{

	class calendar
	{

	public:

		explicit calendar(weekend we, holiday_schedule hols) noexcept;

	public:

		friend auto operator==(const calendar& cal1, const calendar& cal2) noexcept -> bool = default;

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

		void substitute(const business_day_convention* const bdc);

	public:

		auto get_weekend() const noexcept -> const weekend&;
		auto get_holiday_schedule() const noexcept -> const holiday_schedule&;

	private:

		weekend _we;
		holiday_schedule _hols;

	};



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
	) noexcept :
		_we{ we },
		_hols{ hols }
	{
	}


	inline void calendar::substitute(const business_day_convention* const bdc)
	{
		// when we add a business day cache to calendar we should be careful with this function
		const auto hols = _hols.get_holidays();
		for (const auto& holiday : hols)
		{
			_hols -= holiday;
			if (!is_business_day(holiday))
			{
				const auto substitute_day = bdc->adjust(holiday, *this);
				_hols += substitute_day;
			}
			else
			{
				_hols += holiday;
			}
		}
	}


	inline auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
	{
		return !_we.is_weekend(ymd) && !_hols.is_holiday(ymd);
		// we allow a holiday on a weekend
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


	inline auto calendar::get_weekend() const noexcept -> const weekend&
	{
		return _we;
	}

	inline auto calendar::get_holiday_schedule() const noexcept -> const holiday_schedule&
	{
		return _hols;
	}

}
