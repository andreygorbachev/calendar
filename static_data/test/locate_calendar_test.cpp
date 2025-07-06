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

#include <static_data.h>

#include <gtest/gtest.h>

#include <chrono>
#include <ranges>
#include <vector>
#include <stdexcept>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(static, locate_calendar1)
		{
			EXPECT_THROW(locate_calendar("foo"), runtime_error);
		}

		TEST(static, locate_calendar2)
		{
			const auto& cal1 = locate_calendar("Europe/London");
			const auto& cal2 = locate_calendar("Europe/Cardif");
			const auto& cal3 = locate_calendar("Europe/Edinburgh");
			const auto& cal4 = locate_calendar("Europe/Belfast");
			const auto& cal5 = locate_calendar("Europe/MPC");
			const auto& cal6 = locate_calendar("Europe/T2");
			const auto& cal7 = locate_calendar("America/USA");
			const auto& cal8 = locate_calendar("America/Washington");
			const auto& cal9 = locate_calendar("America/ANBIMA");
		}

	}

}
