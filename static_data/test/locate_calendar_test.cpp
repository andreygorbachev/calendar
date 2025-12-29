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

#include <schedule.h>

#include <chrono>
#include <stdexcept>

using namespace std;
using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(static, locate_calendar1)
		{
			// none existing name
			EXPECT_THROW(locate_calendar("foo", 2025y / LastDayOfDecember), runtime_error);

			// none existing version
			EXPECT_THROW(locate_calendar("America/ANBIMA", 2000y / LastDayOfDecember), runtime_error);
		}

		TEST(static, locate_calendar2)
		{
			// test 2 different versions of the same calendar (ANBIMA)
			// Black Consciousness Day

			const auto& cal_ver1 = locate_calendar("America/ANBIMA", 2023y / December / 20d); // prior to announcement of the new holiday
			const auto& cal_ver2 = locate_calendar("America/ANBIMA", 2023y / December / 21d); // on the announcement date of the new holiday
			EXPECT_TRUE(cal_ver1 != cal_ver2);

			// holiday did not exist at all before it was announced
			EXPECT_TRUE(cal_ver1.is_business_day(2023y / November / 20d));
			EXPECT_TRUE(cal_ver1.is_business_day(2024y / November / 20d));
			// holiday exists after it was announced (but starting from 2024)
			EXPECT_TRUE(cal_ver2.is_business_day(2023y / November / 20d));
			EXPECT_FALSE(cal_ver2.is_business_day(2024y / November / 20d));
		}

	}

}
