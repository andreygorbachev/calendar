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

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto NoAdjustment = no_adjustment{};



	class following final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Following = following{};



	class modified_following final : public business_day_convention // could be moved out if it does not fit here
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto ModifiedFollowing = modified_following{};



	class preceding final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Preceding = preceding{};



	// EuroSTR documentation calls this "the European modified previous business day convention"
	class modified_preceding final : public business_day_convention // could be moved out if it does not fit here
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto ModifiedPreceding = modified_preceding{};



	class nearest final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;

	};


	const auto Nearest = nearest{};



	// we might also need monday_if_sunday



	inline auto no_adjustment::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		return ymd;
	}



	inline auto following::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
			result = std::chrono::sys_days{ result } + std::chrono::days{ 1 };

		return result;
	}



	inline auto modified_following::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		const auto f = Following.adjust(ymd, cal);
		if (f.month() == ymd.month())
			return f;
		else
			return Preceding.adjust(ymd, cal);
	}



	inline auto preceding::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
			result = std::chrono::sys_days{ result } - std::chrono::days{ 1 };

		return result;
	}



	inline auto modified_preceding::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		const auto f = Preceding.adjust(ymd, cal);
		if (f.month() == ymd.month())
			return f;
		else
			return Following.adjust(ymd, cal);
	}



	inline auto nearest::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		if (std::chrono::weekday{ ymd } == std::chrono::Sunday)
			return std::chrono::sys_days{ ymd } + std::chrono::days{ 1 };
		else if (std::chrono::weekday{ ymd } == std::chrono::Saturday)
			return std::chrono::sys_days{ ymd } - std::chrono::days{ 1 };
		else
			return ymd;

		// I think a more generic definition is to do following if ymd a non-business day and either Sunday or Monday
		// and previous for all other cases
	}

}
