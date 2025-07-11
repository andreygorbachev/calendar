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

#include <time_series.h>
#include <period.h>

#include <gtest/gtest.h>

#include <chrono>
#include <stdexcept>


using namespace std;
using namespace std::chrono;
using namespace gregorian::util;


namespace gregorian
{

	namespace util
	{

		TEST(time_series, constructor1)
		{
			const auto ts = time_series<double>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto expected = days_period{ 2023y / January / 1d, 2023y / June / 5d };
			EXPECT_EQ(expected, ts.get_period());
		}
		/*
		TEST(time_series, constructor2)
		{
			const auto ts = time_series<double>{ period{ sys_days{ 2023y / January / 1d }, sys_days{ 2023y / June / 5d } } };

			const auto expected = days_period{ 2023y / January / 1d, 2023y / June / 5d };
			EXPECT_EQ(expected, ts.get_period());
		}
		*/
		TEST(time_series, operator_subscript_1)
		{
			const auto ts = time_series<double>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto expected = double{};
			EXPECT_EQ(expected, ts[2023y / January / 1d]);
			EXPECT_EQ(expected, ts[2023y / June / 5d]);

			EXPECT_THROW(ts[2023y / June / 6d], out_of_range);
		}

		TEST(time_series, operator_subscript_2)
		{
			auto ts = time_series<double>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };
			ts[2023y / January / 3d] = 3.4269;

			EXPECT_EQ(3.4269, ts[2023y / January / 3d]);
		}

		TEST(time_series, operator_subscript_3)
		{
			const auto ts = time_series<double>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto expected = double{};
			EXPECT_EQ(expected, ts[sys_days{ 2023y / January / 1d }]);
			EXPECT_EQ(expected, ts[sys_days{ 2023y / June / 5d }]);

			EXPECT_THROW(ts[sys_days{ 2023y / June / 6d }], out_of_range);
		}

		TEST(time_series, operator_subscript_4)
		{
			auto ts = time_series<double>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto sd = sys_days{ 2023y / January / 3d };

			ts[sd] = 3.4269;

			EXPECT_EQ(3.4269, ts[sd]);
		}

		TEST(time_series_bool, constructor1)
		{
			const auto f = 2023y / January / 1d;
			const auto u = f;
			const auto ts = time_series<bool>{ days_period{ f, u } };

			const auto expected = days_period{ f, u };
			EXPECT_EQ(expected, ts.get_period());

			EXPECT_EQ(bool{}, ts[f]);
			EXPECT_EQ(bool{}, ts[u]);
		}

		TEST(time_series_bool, constructor2)
		{
			const auto cs = time_series<bool>::get_chunk_size();

			const auto f = 2023y / January / 1d;
			const auto u = sys_days{ f } + days{ cs } - days{ 1 };
			const auto ts = time_series<bool>{ days_period{ f, u } };

			const auto expected = days_period{ f, u };
			EXPECT_EQ(expected, ts.get_period());

			EXPECT_EQ(bool{}, ts[f]);
			EXPECT_EQ(bool{}, ts[u]);
		}

		TEST(time_series_bool, constructor3)
		{
			const auto cs = time_series<bool>::get_chunk_size();

			const auto f = 2023y / January / 1d;
			const auto u = sys_days{ f } + days{ cs } - days{ 1 } + days{ 1 };
			const auto ts = time_series<bool>{ days_period{ f, u } };

			const auto expected = days_period{ f, u };
			EXPECT_EQ(expected, ts.get_period());

			EXPECT_EQ(bool{}, ts[f]);
			EXPECT_EQ(bool{}, ts[u]);
		}
		/*
		TEST(time_series_bool, constructor4)
		{
			const auto ts = time_series<bool>{ period{ sys_days{ 2023y / January / 1d }, sys_days{ 2023y / June / 5d } } };

			const auto expected = days_period{ 2023y / January / 1d, 2023y / June / 5d };
			EXPECT_EQ(expected, ts.get_period());
		}
		*/
		TEST(time_series_bool, operator_subscript_1)
		{
			const auto ts = time_series<bool>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto expected = bool{};
			EXPECT_EQ(expected, ts[2023y / January / 1d]);
			EXPECT_EQ(expected, ts[2023y / June / 5d]);

			EXPECT_THROW(ts[2023y / June / 6d], out_of_range);
		}

		TEST(time_series_bool, operator_subscript_2)
		{
			auto ts = time_series<bool>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			ts[2023y / January / 3d] = false;
			EXPECT_EQ(false, ts[2023y / January / 3d]);

			ts[2023y / January / 3d] = true;
			EXPECT_EQ(true, ts[2023y / January / 3d]);
		}

		TEST(time_series_bool, operator_subscript_3)
		{
			const auto ts = time_series<bool>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto expected = bool{};
			EXPECT_EQ(expected, ts[sys_days{ 2023y / January / 1d }]);
			EXPECT_EQ(expected, ts[sys_days{ 2023y / June / 5d }]);

			EXPECT_THROW(ts[sys_days{ 2023y / June / 6d }], out_of_range);
		}

		TEST(time_series_bool, operator_subscript_4)
		{
			auto ts = time_series<bool>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			const auto sd = sys_days{ 2023y / January / 3d };

			ts[sd] = false;
			EXPECT_EQ(false, ts[sd]);

			ts[sd] = true;
			EXPECT_EQ(true, ts[sd]);
		}

		TEST(time_series_bool, count_1)
		{
			auto ts = time_series<bool>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			ts[2023y / January / 1d] = false;
			ts[2023y / January / 2d] = false;
			ts[2023y / January / 3d] = true;
			ts[2023y / January / 4d] = true;
			ts[2023y / January / 5d] = false;

			const auto p = days_period{ 2023y / January / 1d, 2023y / January / 5d };

			EXPECT_EQ(2, ts.count(p));
		}

		TEST(time_series_bool, count_2)
		{
			auto ts = time_series<bool>{ days_period{ 2023y / January / 1d, 2023y / June / 5d } };

			ts[2023y / January / 1d] = false;
			ts[2023y / January / 2d] = false;
			ts[2023y / January / 3d] = true;
			ts[2023y / January / 4d] = true;
			ts[2023y / January / 5d] = false;

			const auto p = period{ sys_days{ 2023y / January / 1d }, sys_days{ 2023y / January / 5d } };

			EXPECT_EQ(2, ts.count(p));
		}

		TEST(time_series_bool, get_chunk_size_1)
		{
			EXPECT_EQ(64, time_series<bool>::get_chunk_size());
		}

	}

}
