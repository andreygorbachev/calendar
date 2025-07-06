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

#include <stdexcept>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		auto locate_calendar(string_view tz_name) -> const calendar&
		{
			// linear serach for now, but we can use a map later if needed
			// (each calendar should be able to register itself during initialization)
			if (tz_name == "Europe/London"s) // from UK, only London is in tzdata
				return make_England_calendar();
			else if (tz_name == "Europe/Cardif"s)
				return make_Wales_calendar();
			else if (tz_name == "Europe/Edinburgh"s)
				return make_Scotland_calendar();
			else if (tz_name == "Europe/Belfast"s)
				return make_Northern_Ireland_calendar();
			else if (tz_name == "Europe/MPC"s) // or should it be Europe/UK/MPC? or should it be in etcetera?
				return make_MPC_calendar();
			else if (tz_name == "Europe/T2"s) // or should it be Europe/EU/MPC? or should it be in etcetera?
				return make_T2_calendar();
			else
				throw runtime_error{ "calendar "s + string{ tz_name } + " could not be located"s };
		}

		// not 100% sure about following tz-data, but it seems to be ok for now
		// (not sure if continent is important to calendars)

		// we'll probably end up with a separate data file like tz-data (maybe in a similar format)
		// (that we'll also make a long if ... eles chain not needed)

		// otherwise, make* functions should not be exposed anyway

	}

}
