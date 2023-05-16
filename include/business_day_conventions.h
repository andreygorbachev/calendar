// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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



	class modified_following final : public business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto ModifiedFollowing = modified_following{};



	class preceding final : public business_day_convention
	{

	public:

		virtual auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Preceding = preceding{};



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



	inline auto modified_following::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		const auto f = Following.adjust(ymd, cal);
		if (f.month() == ymd.month())
			return f;
		else
			return Preceding.adjust(ymd, cal);
	}



	inline auto preceding::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
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
