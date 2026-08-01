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

#include <annual_holiday_interface.h>

#include <chrono>
#include <utility>
#include <vector>


namespace gregorian
{

	namespace static_data
	{

		// is file's name consistent with the name of the class?
		class _employment_situation_publication_day_holiday final : public annual_holiday // should it be generalized and moved to annual_holidays.h?
		{

		public:

			explicit constexpr _employment_situation_publication_day_holiday(std::chrono::month reference_month) noexcept;

		private:

			/*constexpr*/ auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

		private:

			std::chrono::month _reference_month;

		};



		inline constexpr _employment_situation_publication_day_holiday::_employment_situation_publication_day_holiday(std::chrono::month reference_month) noexcept :
			_reference_month{ std::move(reference_month) }
		{
		}


		inline /*constexpr*/ auto _employment_situation_publication_day_holiday::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
		{
			const auto reference_year_month = _reference_month != std::chrono::December ?
				y / _reference_month :
				y / _reference_month - std::chrono::years{ 1 };

			const auto _12th_of_reference_month = reference_year_month / std::chrono::day{ 12u };

			const auto _12th_of_reference_month_weekday = std::chrono::weekday{ _12th_of_reference_month }; // week Sunday to Saturday
			const auto start_of_reference_period =
				std::chrono::sys_days{ _12th_of_reference_month } -
				std::chrono::days{ _12th_of_reference_month_weekday.c_encoding() };

			auto release_date = start_of_reference_period +
				std::chrono::days{ std::chrono::Friday.c_encoding() } + // move to the Friday of the reference week
				std::chrono::weeks{ 3 }; // move to the third Friday after the reference week

			// Generally, the Employment Situation publication date is the third Friday after the week that includes the 12th.
			// This usually results in the release being scheduled for the first Friday of the month following the reference month.
			// 
			// However, when the 12th of the month falls on a Sunday and there are 30 days or less in the month, the release date will be the second Friday of the month.
			// In addition, if the third Friday after the December reference period falls on January 1–3, the release date will be the second Friday of the month.
			//
			// If the normal release day Friday happens to be a federal holiday, such as July 4th, the release date will be the Thursday immediately preceding the holiday.
			// The Employment Situation release dates are adjusted only for designated federal holidays.
			//
			// The Employment Situation release dates are approved by the Office of Management and Budget and published in advance.

			const auto days_in_reference_month = static_cast<unsigned>(std::chrono::year_month_day_last{ reference_year_month / std::chrono::last }.day());

			const auto release_year_month_day = std::chrono::year_month_day{ release_date };
			const auto release_year = release_year_month_day.year();
			const auto release_month = release_year_month_day.month();
			const auto release_day = release_year_month_day.day();
			if ((_12th_of_reference_month_weekday == std::chrono::Sunday && days_in_reference_month <= 30u) ||
				(release_month == std::chrono::January && (release_day == std::chrono::day{ 1u } || release_day == std::chrono::day{ 2u } || release_day == std::chrono::day{ 1u }))
			)
				release_date = release_year / release_month / std::chrono::Friday[2];

			return release_date;
		}



		constexpr auto _EmploymentSituationJanuaryRelease = _employment_situation_publication_day_holiday{ std::chrono::December };
		constexpr auto _EmploymentSituationFebruaryRelease = _employment_situation_publication_day_holiday{ std::chrono::January };
		constexpr auto _EmploymentSituationMarchRelease = _employment_situation_publication_day_holiday{ std::chrono::February };
		constexpr auto _EmploymentSituationAprilRelease = _employment_situation_publication_day_holiday{ std::chrono::March };
		constexpr auto _EmploymentSituationMayRelease = _employment_situation_publication_day_holiday{ std::chrono::April };
		constexpr auto _EmploymentSituationJuneRelease = _employment_situation_publication_day_holiday{ std::chrono::May };
		constexpr auto _EmploymentSituationJulyRelease = _employment_situation_publication_day_holiday{ std::chrono::June };
		constexpr auto _EmploymentSituationAugustRelease = _employment_situation_publication_day_holiday{ std::chrono::July };
		constexpr auto _EmploymentSituationSeptemberRelease = _employment_situation_publication_day_holiday{ std::chrono::August };
		constexpr auto _EmploymentSituationOctoberRelease = _employment_situation_publication_day_holiday{ std::chrono::September };
		constexpr auto _EmploymentSituationNovemberRelease = _employment_situation_publication_day_holiday{ std::chrono::October };
		constexpr auto _EmploymentSituationDecemberRelease = _employment_situation_publication_day_holiday{ std::chrono::November };

		const auto _EmploymentSituationRules = annual_holiday_storage{
			&_EmploymentSituationJanuaryRelease,
			&_EmploymentSituationFebruaryRelease,
			&_EmploymentSituationMarchRelease,
			&_EmploymentSituationAprilRelease,
			&_EmploymentSituationMayRelease,
			&_EmploymentSituationJuneRelease,
			&_EmploymentSituationJulyRelease,
			&_EmploymentSituationAugustRelease,
			&_EmploymentSituationSeptemberRelease,
			&_EmploymentSituationOctoberRelease,
			&_EmploymentSituationNovemberRelease,
			&_EmploymentSituationDecemberRelease
		};

	}

}
