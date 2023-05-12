#pragma once

#include "business_day_convention_interface.h"
#include "calendar.h"

#include <chrono>


namespace calendar
{

	class no_adjustment final : public business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto NoAdjustment = no_adjustment{};



	class following final : public business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Following = following{};



	class previous final : public business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Previous = previous{};



	class friday_if_saturday_and_monday_if_sunday final : public business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto FridayIfSaturdayAndMondayIfSunday = friday_if_saturday_and_monday_if_sunday{};



	// we might also need monday_if_sunday



	inline auto no_adjustment::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		return ymd;
	}



	inline auto following::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
			result = std::chrono::sys_days{ result } + std::chrono::days{ 1 };

		return result;
	}



	inline auto previous::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
			result = std::chrono::sys_days{ result } - std::chrono::days{ 1 };

		return result;
	}



	inline auto friday_if_saturday_and_monday_if_sunday::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		if (std::chrono::weekday{ ymd } == std::chrono::Sunday)
			return std::chrono::sys_days{ ymd } + std::chrono::days{ 1 };
		else if (std::chrono::weekday{ ymd } == std::chrono::Saturday)
			return std::chrono::sys_days{ ymd } - std::chrono::days{ 1 };
		else
			return ymd;
	}

}
