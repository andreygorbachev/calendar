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

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(static, make_calendar1)
		{
			const auto& cal = make_T2_calendar();
		}

		TEST(static, make_calendar2)
		{
			const auto& cal = make_USA_Federal_calendar();
		}

		TEST(static, make_calendar3)
		{
			const auto& cal1 = make_England_calendar();
			const auto& cal2 = make_Scotland_calendar();
			const auto& cal3 = make_Wales_calendar();
			const auto& cal4 = make_Northern_Ireland_calendar();
		}

		TEST(static, make_calendar4)
		{
			const auto& cal = make_ANBIMA_calendar();
		}

	}

}
