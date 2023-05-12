#pragma once

#include <chrono>


namespace calendar
{

	class calendar;


	class business_day_convention {

	public:

		virtual ~business_day_convention() noexcept = default;

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day = 0;

	};

}
