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
#include <string_view>

using namespace std;


namespace gregorian
{

	namespace static_data
	{

		using _calendar_registry2 = map<string_view, calendar>;
		// should it be string rather than string_view?
		// is map a correct data structure for this?

		static auto _make_calendar_registry2() -> _calendar_registry2
		{
			// at the moment we create all calendars (needed or not), which might or might not be what we want
			// this could be changed to lazy creation if needed, but we'll have to deal with synchronization then
			return _calendar_registry2{
				{ "Europe/London", make_England_calendar() },
				{ "Europe/Cardif", make_Wales_calendar() },
				{ "Europe/Edinburgh", make_Scotland_calendar() },
				{ "Europe/Belfast", make_Northern_Ireland_calendar() },
				{ "Europe/MPC", make_MPC_calendar() },

				{ "Europe/T2", make_T2_calendar() },

				{ "America/USA", make_USA_Federal_calendar() },
				{ "America/Washington", make_Washington_DC_Federal_calendar() },

				{ "America/Canada", make_Canada_Federal_calendar() },
				{ "America/Quebec", make_Quebec_calendar() },

				{ "America/ANBIMA", make_ANBIMA_calendar() },
			};
		}

		static auto _get_calendar_registry2() -> const _calendar_registry2&
		{
			static const auto r = _make_calendar_registry2();
			return r;
		}

	}

}
