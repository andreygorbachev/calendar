// The MIT License (MIT)
//
// Copyright (c) 2024 Andrey Gorbachev
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

#include "London.h"

#include <chrono>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
using namespace std::chrono;

using namespace gregorian;


constexpr auto number_of_runs = 10;

// SONIA Compound Index started on 23 April 2018
constexpr auto SONIA_compound_index_from = year{ 2018 } / April / day{ 23u };
constexpr auto until = year{ 2024 } / December / day{ 31u };



static void experiment_is_business_day_year_month_day()
{
	const auto& calendar = make_London_calendar();

	auto min_duration = microseconds::max();
	auto max_duration = microseconds::min();

	for (auto r = 0; r < number_of_runs; ++r)
	{
		const auto start = high_resolution_clock::now();

		volatile auto number_of_business_days = 0;
		for (
			auto d = SONIA_compound_index_from;
			d <= until;
			d = sys_days{ d } + days{ 1 }
		)
			if (calendar.is_business_day(d))
				number_of_business_days++;

		const auto stop = high_resolution_clock::now();

		const auto duration = duration_cast<microseconds>(stop - start);
		cout
			<< "Run:"s
			<< r
			<< " Duration: "s
			<< duration.count()
			<< " microseconds."s
			<< endl;

		min_duration = min(duration, min_duration);
		max_duration = max(duration, max_duration);
	}

	cout
		<< "Duration range: ["s
		<< min_duration.count()
		<< ", "s
		<< max_duration.count()
		<< "] microseconds."s
		<< endl;
}


static void experiment_is_business_day_sys_days()
{
	const auto& calendar = make_London_calendar();

	auto min_duration = microseconds::max();
	auto max_duration = microseconds::min();

	for (auto r = 0; r < number_of_runs; ++r)
	{
		const auto start = high_resolution_clock::now();

		volatile auto number_of_business_days = 0;
		for (
			auto d = sys_days{ SONIA_compound_index_from };
			d <= sys_days{ until };
			d += days{ 1 }
		)
			if (calendar.is_business_day(d))
				number_of_business_days++;

		const auto stop = high_resolution_clock::now();

		const auto duration = duration_cast<microseconds>(stop - start);
		cout
			<< "Run:"s
			<< r
			<< " Duration: "s
			<< duration.count()
			<< " microseconds."s
			<< endl;

		min_duration = min(duration, min_duration);
		max_duration = max(duration, max_duration);
	}

	cout
		<< "Duration range: ["s
		<< min_duration.count()
		<< ", "s
		<< max_duration.count()
		<< "] microseconds."s
		<< endl;
}


static void experiment_count_business_days_year_month_day()
{
	const auto& calendar = make_London_calendar();

	auto min_duration = microseconds::max();
	auto max_duration = microseconds::min();

	for (auto r = 0; r < number_of_runs; ++r)
	{
		const auto start = high_resolution_clock::now();

		const auto p = days_period{ SONIA_compound_index_from, until };

		volatile auto number_of_business_days =
			calendar.count_business_days(p);

		const auto stop = high_resolution_clock::now();

		const auto duration = duration_cast<microseconds>(stop - start);
		cout
			<< "Run:"s
			<< r
			<< " Duration: "s
			<< duration.count()
			<< " microseconds."s
			<< endl;

		min_duration = min(duration, min_duration);
		max_duration = max(duration, max_duration);
	}

	cout
		<< "Duration range: ["s
		<< min_duration.count()
		<< ", "s
		<< max_duration.count()
		<< "] microseconds."s
		<< endl;
}


static void experiment_count_business_sys_days()
{
	const auto& calendar = make_London_calendar();

	auto min_duration = microseconds::max();
	auto max_duration = microseconds::min();

	for (auto r = 0; r < number_of_runs; ++r)
	{
		const auto start = high_resolution_clock::now();

		const auto p = period<sys_days>{ SONIA_compound_index_from, until };

		volatile auto number_of_business_days =
			calendar.count_business_days(p);

		const auto stop = high_resolution_clock::now();

		const auto duration = duration_cast<microseconds>(stop - start);
		cout
			<< "Run:"s
			<< r
			<< " Duration: "s
			<< duration.count()
			<< " microseconds."s
			<< endl;

		min_duration = min(duration, min_duration);
		max_duration = max(duration, max_duration);
	}

	cout
		<< "Duration range: ["s
		<< min_duration.count()
		<< ", "s
		<< max_duration.count()
		<< "] microseconds."s
		<< endl;
}


int main()
{
	cout << "Experiment is_business_day with year/month/day:"s << endl;
	experiment_is_business_day_year_month_day();
	cout << endl;

	cout << "Experiment is_business_day with sys_days:"s << endl;
	experiment_is_business_day_sys_days();
	cout << endl;

	cout << "Experiment count_business_days with year/month/day:"s << endl;
	experiment_count_business_days_year_month_day();
	cout << endl;

	cout << "Experiment count_business_days with sys_days:"s << endl;
	experiment_count_business_sys_days();
	cout << endl;

	return 0;
}
