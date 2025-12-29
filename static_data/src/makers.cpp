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

#include "makers.h"

#include <calendar.h>
#include <schedule.h>

#include <string>
#include <string_view>
#include <stdexcept>
#include <chrono>
#include <cassert>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		static auto _make_calendar_registry() -> _calendar_registry
		{
			// at the moment we create all calendars (needed or not), which might or might not be what we want
			// this could be changed to lazy creation if needed, but we'll have to deal with synchronization then
			return _calendar_registry{
				{ "Europe/London", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_England_calendar() } } }, // from UK, only London is in tzdata
				{ "Europe/Cardif", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Wales_calendar() } } },
				{ "Europe/Edinburgh", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Scotland_calendar() } } },
				{ "Europe/Belfast", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Northern_Ireland_calendar() } } },
				{ "Europe/MPC", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_MPC_calendar() } } }, // or should it be Europe/UK/MPC? or should it be in etcetera?

				{ "Europe/T2", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_T2_calendar() } } }, // or should it be Europe/EU/TARGET2? or should it be in etcetera?

				{ "America/USA", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_USA_Federal_calendar() } } },
				{ "America/Washington", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Washington_DC_Federal_calendar() } } }, // not a city, but federal holidays

				{ "America/Canada", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Canada_Federal_calendar() } } },
				{ "America/Ontario", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Ontario_calendar() } } },
				{ "America/Quebec", _calendar_versions{ { 2026y / FirstDayOfJanuary, make_Quebec_calendar() } } },

				{ "America/ANBIMA", make_ANBIMA_calendar_versions() }, // or should it be America/Brazil/ANBIMA? or should it be in etcetera?
			};
		}

		auto _get_calendar_registry() -> const _calendar_registry&
		{
			static const auto r = _make_calendar_registry(); // ideally all this will be generated at compile time
			return r;
		}


		static auto _locate_calendar_versions(string_view tz_name) -> const _calendar_versions& // this should probably return _calendar_versions instead
		{
			const auto& reg = _get_calendar_registry();

			const auto it = reg.find(tz_name);
			if (it != reg.cend())
				return it->second;
			else
				throw runtime_error{ "calendar "s + string{ tz_name } + " could not be located"s };
		}

		auto locate_calendar(string_view tz_name, year_month_day as_of_day) -> const calendar&
		{
			// at the moment we ignore as_of_day
			const auto& cal_versions = _locate_calendar_versions(tz_name);
			assert(!cal_versions.empty());
			return cal_versions.crbegin()->second; // return the latest version
		}

		// not 100% sure about following tz-data, but it seems to be ok for now
		// (not sure if continent is important to calendars)

		// we'll probably end up with a separate data file like tz-data (maybe in a similar format)
		// or an sqlite database

		// #embed could also be considered, at least for the known dates

	}

}
