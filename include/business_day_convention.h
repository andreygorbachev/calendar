#pragma once

#include "calendar.h"

#include <chrono>


class business_day_convention {

public:

	virtual ~business_day_convention() noexcept = default;

public:

	virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& c) const noexcept -> std::chrono::year_month_day = 0;

};



class following final : business_day_convention
{

public:

	virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& c) const noexcept -> std::chrono::year_month_day override;

};


const auto Following = following{};



inline auto following::adjust(const std::chrono::year_month_day& ymd, const calendar& c) const noexcept -> std::chrono::year_month_day
{
	return ymd; // temp
}
