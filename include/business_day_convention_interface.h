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

#include <chrono>


namespace gregorian
{

	class calendar;


	class business_day_convention
	{

	public:

		business_day_convention() noexcept = default;
		virtual ~business_day_convention() noexcept = default;

		business_day_convention(const business_day_convention&) = delete;
		business_day_convention(business_day_convention&&) noexcept = delete;

		business_day_convention& operator=(const business_day_convention&) = delete;
		business_day_convention& operator=(business_day_convention&&) noexcept = delete;

	public:

		auto adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const -> std::chrono::year_month_day;
		auto adjust(const std::chrono::sys_days& sd, const calendar& cal) const -> std::chrono::sys_days;

	private:

		virtual auto _adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const -> std::chrono::year_month_day = 0;

		// if more efficient, derived classes should also override this method, but it is not mandatory
		virtual auto _adjust(const std::chrono::sys_days& sd, const calendar& cal) const -> std::chrono::sys_days;

	};



	inline auto business_day_convention::adjust(const std::chrono::year_month_day& ymd, const calendar& cal) const -> std::chrono::year_month_day
	{
		return _adjust(ymd, cal);
	}

	inline auto business_day_convention::adjust(const std::chrono::sys_days& sd, const calendar& cal) const -> std::chrono::sys_days
	{
		return _adjust(sd, cal);
	}


	inline auto business_day_convention::_adjust(const std::chrono::sys_days& sd, const calendar& cal) const -> std::chrono::sys_days
	{
		return std::chrono::sys_days{ _adjust(std::chrono::year_month_day{ sd }, cal) };
	}

}
