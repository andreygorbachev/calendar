#pragma once

#include "weekend.h"
#include "holiday_schedule.h"

#include <cstddef>
#include <memory>
#include <chrono>



class calendar
{

public:

	explicit calendar(const weekend* we, const holiday_schedule* hols) noexcept;
	// keep a copy?

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

	// would "*" and "[]" make soe sence here?
	// iterators?
	// serial dates?

private:

	const weekend* _we;
	const holiday_schedule* _hols;

};



inline calendar::calendar(
	const weekend* we,
	const holiday_schedule* hols
) noexcept :
	_we{ we },
	_hols{ hols }
{
}


inline auto calendar::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return !_we->is_weekend(ymd) && !_hols->is_holiday(ymd);
	// we allow a holiday on a weekend
}

inline auto calendar::count_business_days(
	const std::chrono::year_month_day& start,
	const std::chrono::year_month_day& end
) const -> std::size_t
{
	auto result = 0/*uz*/;

	// naive implementation to start with
	for (auto d = start; d <= end; d = std::chrono::sys_days{ d } + std::chrono::days{ 1 })
		if (is_business_day(d))
			result++;

	return result;
}
