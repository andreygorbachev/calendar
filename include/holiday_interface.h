#pragma once

#include <chrono>


namespace calendar
{

	class annual_holiday
	{

	public:

		virtual ~annual_holiday() noexcept = default;

	public:

		virtual auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day = 0;

	};
	// we can add a list of years where an annual holiday should not apply (skip a year)
	// (as rule based holidays at the moment are only directed for the future this is probably not needed)
	// would that lead us to "first year" and "last year" as well?

}
