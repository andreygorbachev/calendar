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

#include <cyclical_holiday.h>

#include <annual_holidays.h>

#include <gtest/gtest.h>

#include <chrono>

using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(_cyclical_holiday, make_holiday1)
		{
			const auto _January_20 = named_holiday{ January / 20d };
			const auto _InaugurationDay = _cyclical_holiday{ &_January_20, 1965y, years{ 4 } };

			EXPECT_EQ(2025y / January / 20d, _InaugurationDay.make_holiday(2025y));
			EXPECT_FALSE(_InaugurationDay.make_holiday(2026y).ok());
			EXPECT_FALSE(_InaugurationDay.make_holiday(2027y).ok());
			EXPECT_FALSE(_InaugurationDay.make_holiday(2028y).ok());
			EXPECT_EQ(2029y / January / 20d, _InaugurationDay.make_holiday(2029y));
		}

		TEST(_cyclical_holiday, make_holiday2)
		{
			const auto _January_20 = named_holiday{ January / 20d };
			const auto _InaugurationDay = _cyclical_holiday{ &_January_20, 1965y, years{ -4 } }; // negative period does not make sense, but it works

			EXPECT_EQ(2025y / January / 20d, _InaugurationDay.make_holiday(2025y));
			EXPECT_FALSE(_InaugurationDay.make_holiday(2024y).ok());
			EXPECT_FALSE(_InaugurationDay.make_holiday(2023y).ok());
			EXPECT_FALSE(_InaugurationDay.make_holiday(2022y).ok());
			EXPECT_EQ(2021y / January / 20d, _InaugurationDay.make_holiday(2021y));
		}

		TEST(_cyclical_holiday, make_holiday3)
		{
			const auto _January_20 = named_holiday{ January / 20d };
			const auto _InaugurationDay = _cyclical_holiday{ &_January_20, 1965y, years{ 4 } };

			EXPECT_EQ(1961y / January / 20d, _InaugurationDay.make_holiday(1961y)); // year before start does not make sense, but it works
			EXPECT_FALSE(_InaugurationDay.make_holiday(1962y).ok());
			EXPECT_FALSE(_InaugurationDay.make_holiday(1963y).ok());
			EXPECT_FALSE(_InaugurationDay.make_holiday(1964y).ok());
			EXPECT_EQ(1965y / January / 20d, _InaugurationDay.make_holiday(1965y));
		}

	}

}
