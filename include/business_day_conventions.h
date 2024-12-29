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


namespace gregorian
{

	class no_adjustment final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days final;

	};


	const auto NoAdjustment = no_adjustment{};



	class following final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days final;

	};


	const auto Following = following{};



	class modified_following final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days final;

	};


	const auto ModifiedFollowing = modified_following{};



	class preceding final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days final;

	};


	const auto Preceding = preceding{};



	// EuroSTR documentation calls this "the European modified previous business day convention"
	class modified_preceding final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days final;

	};


	const auto ModifiedPreceding = modified_preceding{};



	class nearest final : public business_day_convention
	{

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day final;
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days final;

	};


	const auto Nearest = nearest{};



	inline auto make_first_business_day(
		const std::chrono::year_month& ym,
		const calendar& cal
	) -> std::chrono::year_month_day
	{
		const auto ymd = ym / std::chrono::day{ 1u };
		return Following.adjust(ymd, cal);
	}


	inline auto make_last_business_day(
		const std::chrono::year_month& ym,
		const calendar& cal
	) -> std::chrono::year_month_day
	{
		const auto ymd = std::chrono::year_month_day{ ym / std::chrono::last };
		return Preceding.adjust(ymd, cal);
	}



	inline auto no_adjustment::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		return ymd;
	}

	inline auto no_adjustment::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days
	{
		return sd;
	}



	inline auto following::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
			result = std::chrono::sys_days{ result } + std::chrono::days{ 1 };

		return result;
	}

	inline auto following::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days
	{
		auto result = sd;
		while (!cal.is_business_day(result))
			result += std::chrono::days{ 1 };

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

	inline auto modified_following::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days
	{
		return std::chrono::sys_days{ _adjust(std::chrono::year_month_day{ sd }, cal) };
	}



	inline auto preceding::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		auto result = ymd;
		while (!cal.is_business_day(result))
			result = std::chrono::sys_days{ result } - std::chrono::days{ 1 };

		return result;
	}

	inline auto preceding::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days
	{
		auto result = sd;
		while (!cal.is_business_day(result))
			result -= std::chrono::days{ 1 };

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

	inline auto modified_preceding::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days
	{
		return std::chrono::sys_days{ _adjust(std::chrono::year_month_day{ sd }, cal) };
	}



	inline auto nearest::_adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const noexcept -> std::chrono::year_month_day
	{
		const auto f = Following.adjust(ymd, cal);
		const auto p = Preceding.adjust(ymd, cal);
		if (std::chrono::sys_days{ f } - std::chrono::sys_days{ ymd } <= std::chrono::sys_days{ ymd } - std::chrono::sys_days{ p })
			return f;
		else
			return p;
	}

	inline auto nearest::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const noexcept -> std::chrono::sys_days
	{
		const auto f = Following.adjust(sd, cal);
		const auto p = Preceding.adjust(sd, cal);
		if (f - sd <= sd - p)
			return f;
		else
			return p;
	}

}
