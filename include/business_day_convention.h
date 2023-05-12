#pragma once

#include "calendar.h"

#include <chrono>


namespace calendar
{

	// what we expect to happen is that all historical holiday are provided as explicit dates
	// current year and maybe 1-2 years in the future are also provided as explicit dates
	// afterwards we have rule based calendar and if we want to be exact there (at least for known holidays)
	// we need to adjusty for a good business day
	// but at the same time there is some uncertainty about additional holidays that far in the future
	// so maybe we do not care for the exactness of the known holidays (hence the below is not yet used)


	class business_day_convention {

	public:

		virtual ~business_day_convention() noexcept = default;

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day = 0;

	};



	class no_adjustment final : business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto NoAdjustment = no_adjustment{};



	class following final : business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Following = following{};



	class previous final : business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Previous = previous{};



	class monday_if_sunday final : business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto MondayIfSunday = monday_if_sunday{};



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



	inline auto monday_if_sunday::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		if (std::chrono::weekday{ ymd } == std::chrono::Sunday)
			return std::chrono::sys_days{ ymd } + std::chrono::days{ 1 };
		else
			return ymd;
	}

}
