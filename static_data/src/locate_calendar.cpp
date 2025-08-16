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

#include "static_data.h"
#include "makers.h"

#include <stdexcept>
#include <map>
//#include <memory>
#include <functional>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		using _calendar_registry = map<string_view, function<const calendar&()>>; // should probably be unique_ptr // should it be string rather than string_view?
		// is map a correct data structure for this?

		static auto _make_calendar_registry()
		{
			auto r = _calendar_registry{};

			r["Europe/London"] = [] { return make_England_calendar(); }; // from UK, only London is in tzdata
			r["Europe/Cardif"] = [] { return make_Wales_calendar(); };
			r["Europe/Edinburgh"] = [] { return make_Scotland_calendar(); };
			r["Europe/Belfast"] = [] { return make_Northern_Ireland_calendar(); };
			r["Europe/MPC"] = [] { return make_MPC_calendar(); }; // or should it be Europe/UK/MPC? or should it be in etcetera?
			r["Europe/T2"] = [] { return make_T2_calendar(); }; // or should it be Europe/EU/TARGET2? or should it be in etcetera?

			r["America/USA"] = [] { return make_USA_Federal_calendar(); }; // not a city, but federal holidays
			r["America/Washington"] = [] { return make_Washington_DC_Federal_calendar(); }; // not a city, but federal holidays
			r["America/ANBIMA"] = [] { return make_ANBIMA_calendar(); }; // or should it be America/Brazil/ANBIMA? or should it be in etcetera?

			return r;
		}

		static auto _get_calendar_registry()
		{
			static const auto r = _make_calendar_registry();
			return r;
		}


		auto locate_calendar(string_view tz_name) -> const calendar&
		{
			const auto& reg = _get_calendar_registry();

			const auto it = reg.find(tz_name);
			if(it != reg.cend())
				return it->second();
			else
				throw runtime_error{ "calendar "s + string{ tz_name } + " could not be located"s };
		}

		// not 100% sure about following tz-data, but it seems to be ok for now
		// (not sure if continent is important to calendars)

		// we'll probably end up with a separate data file like tz-data (maybe in a similar format)
		// or sqlite database

		// #embed could also be considered, at least for the known dates

		// otherwise, make* functions should not be exposed anyway

	}

}
