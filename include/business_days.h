#pragma once

#include "calendar.h"

#include <chrono>



class business_days
{

public:

	constexpr explicit business_days(const calendar* cal);

public:

	constexpr auto is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool;

private:

	const calendar* _calendar;

};



constexpr business_days::business_days(const calendar* cal) : _calendar{ cal }
{
}


constexpr auto business_days::is_business_day(const std::chrono::year_month_day& ymd) const noexcept -> bool
{
	return _calendar->is_business_day(ymd);
	// does it mean that is_business_day should be removed from calendar? (and only exist here)
}
