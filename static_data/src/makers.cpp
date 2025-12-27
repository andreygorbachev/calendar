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

#include <map>
#include <string>
#include <string_view>
#include <stdexcept>

using namespace std;


namespace gregorian
{

	namespace static_data
	{

		using _calendar_registry = map<string_view, calendar>;
		// should it be string rather than string_view?
		// is map a correct data structure for this?

		static auto _make_calendar_registry() -> _calendar_registry
		{
			// at the moment we create all calendars (needed or not), which might or might not be what we want
			// this could be changed to lazy creation if needed, but we'll have to deal with synchronization then
			return _calendar_registry{
				{ "Europe/London", make_England_calendar() }, // from UK, only London is in tzdata
				{ "Europe/Cardif", make_Wales_calendar() },
				{ "Europe/Edinburgh", make_Scotland_calendar() },
				{ "Europe/Belfast", make_Northern_Ireland_calendar() },
				{ "Europe/MPC", make_MPC_calendar() }, // or should it be Europe/UK/MPC? or should it be in etcetera?

				{ "Europe/T2", make_T2_calendar() }, // or should it be Europe/EU/TARGET2? or should it be in etcetera?

				{ "America/USA", make_USA_Federal_calendar() },
				{ "America/Washington", make_Washington_DC_Federal_calendar() }, // not a city, but federal holidays

				{ "America/Canada", make_Canada_Federal_calendar() },
				{ "America/Quebec", make_Quebec_calendar() },

				{ "America/ANBIMA", make_ANBIMA_calendar() }, // or should it be America/Brazil/ANBIMA? or should it be in etcetera?
			};
		}

		static auto _get_calendar_registry() -> const _calendar_registry&
		{
			static const auto r = _make_calendar_registry();
			return r;
		}


		auto locate_calendar(string_view tz_name) -> const calendar&
		{
			const auto& reg = _get_calendar_registry();

			const auto it = reg.find(tz_name);
			if (it != reg.cend())
				return it->second;
			else
				throw runtime_error{ "calendar "s + string{ tz_name } + " could not be located"s };
		}

		// not 100% sure about following tz-data, but it seems to be ok for now
		// (not sure if continent is important to calendars)

		// we'll probably end up with a separate data file like tz-data (maybe in a similar format)
		// or an sqlite database

		// #embed could also be considered, at least for the known dates

	}

}
