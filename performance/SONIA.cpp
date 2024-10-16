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

using namespace std;
using namespace std::chrono;

using namespace gregorian;



int main()
{
	const auto& calendar = make_London_calendar();

	const auto number_of_runs = 100;
	for (auto i = 0; i < number_of_runs; ++i)
	{
		const auto start = high_resolution_clock::now();

		// SONIA Compound Index started on 23 April 2018
		auto result = 0;
		for (
			auto d = year{ 2018 } / April / day{ 23u };
			d <= year{ 2024 } / December / day{ 31u };
			d = sys_days{ d } + days{ 1 }
		)
			if (calendar.is_business_day(d))
				result++;

		const auto stop = high_resolution_clock::now();

		const auto duration = duration_cast<microseconds>(stop - start);
		cout << "Duration: "s << duration.count() << " microseconds." << endl;
	}

	return 0;
}
