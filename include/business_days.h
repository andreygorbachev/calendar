#pragma once

#include "calendar.h"

#include <chrono>



class business_days
{

public:

	constexpr explicit business_days(const calendar* cal) noexcept;

public:

	constexpr auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

	constexpr auto count(
		const std::chrono::year_month_day& start,
		const std::chrono::year_month_day& end
	) const -> std::size_t;
	// if end is before start should the function swap them around? (or return a negative number? or throw an exception)
	// if we need to return a negative number then the return should not be std::size_t (which we might want to change anyway)
	// should we consider calling start "front" and end "back" to be more consistent with STL
	// (or should we operate with "begin"/"end" ideas here instead)

private:

	const calendar* _calendar;

};



constexpr business_days::business_days(const calendar* cal) noexcept : _calendar{ cal }
{
}


constexpr auto business_days::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return _calendar->is_business_day(ymd);
	// does it mean that is_business_day should be removed from calendar? (and only exist here)
}

constexpr auto business_days::count(
	const std::chrono::year_month_day& start,
	const std::chrono::year_month_day& end
) const -> std::size_t
{
	return 0/*uz*/; // temp only
}
