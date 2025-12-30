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

#include "static_data.h"

#include <calendar.h>
#include <schedule.h>
#include <annual_holiday_interface.h>
#include <period.h>

#include <vector>
#include <chrono>
#include <map> // for _get_calendar_registry only
#include <string_view> // for _get_calendar_registry only


namespace gregorian
{

	namespace static_data // should these functions to be internal function only?
	{

		using _calendar_versions = std::map<std::chrono::year_month_day, calendar>;

		// below are exposed for testing purposes only
		using _calendar_registry = std::map<std::string_view, _calendar_versions>;
		// should it be string rather than string_view?
		// is map a correct data structure for this?

		auto _get_calendar_registry() -> const _calendar_registry&;



		struct _annual_holiday_period final
		{
			const annual_holiday* holiday;
			util::days_period period{ Epoch }; // if we deal in annual calendars, should this be in years?
			std::chrono::year_month_day announced{ Epoch.get_from() }; // do we need time as well?
			// we should also have a cancellation date (but we need to find a good example first)
			// is creation and cancellation immidiately effective (how tzdata deals with the same)?
		};
		// how do we handle a situation when Saturday "moves" to another day (and actually is a business day)?

		using _annual_holiday_period_storage = std::vector<_annual_holiday_period>;

		auto _make_sub_epochs(
			const _annual_holiday_period_storage& storage,
			const util::days_period& epoch,
			const std::chrono::year_month_day& as_of_date
		) -> std::vector<util::days_period>; // do we need to expose this function?

		auto _make_holiday_schedule(
			const _annual_holiday_period_storage& storage,
			const util::years_period& epoch
		) -> schedule; // do we need to expose this function?



		// from https://www.gov.uk/bank-holidays

		auto make_England_calendar() -> const calendar&;

		auto make_Wales_calendar() -> const calendar&;

		auto make_Scotland_calendar() -> const calendar&;

		auto make_Northern_Ireland_calendar() -> const calendar&;

		// from: https://www.bankofengland.co.uk/monetary-policy/upcoming-mpc-dates

		auto make_MPC_calendar() -> const calendar&; // should this go to the fin-calendar?
		// does not correspond to Epoch


		// from https://www.ecb.europa.eu/paym/target/t2/html/index.en.html

		auto make_T2_calendar() -> const calendar&; // example of a calendar which did not exist in 2000 // should this go to the fin-calendar?


		// from https://www.opm.gov/policy-data-oversight/pay-leave/federal-holidays/

		auto make_USA_Federal_calendar() -> const calendar&;

		auto make_Washington_DC_Federal_calendar() -> const calendar&;


		// from https://www.canada.ca/en/revenue-agency/services/tax/public-holidays.html

		auto make_Canada_Federal_calendar() -> const calendar&; // should it be called National? (like in https://www.bankofcanada.ca/press/upcoming-events/bank-of-canada-holiday-schedule/)

		auto make_Ontario_calendar() -> const calendar&;

		auto make_Quebec_calendar() -> const calendar&;


		//

		auto make_ANBIMA_calendar_versions() -> _calendar_versions; // should this go to the fin-calendar?
		// does not correspond to Epoch

	}

}
