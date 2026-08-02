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

#include "parser.h"

#include <schedule.h>
#include <annual_holidays.h>
#include <period.h>

#include <chrono>
#include <iostream>
#include <ios>
#include <utility>
#include <vector>

using namespace gregorian;
using namespace gregorian::util;

using namespace std;
using namespace std::chrono;



int main()
{

    const auto y_from = 1600y;
    const auto y_until = 2099y;

    // from https://www.census.gov/data/software/x13as/genhol/easter-dates-frequency.html

    const auto from_file = parse_txt_schedule("easter500.txt", y_from, y_until);

    // generate Easter dates for the same year range so we can compare schedules
    auto s = schedule::dates{};
    for (auto y = y_from; y <= y_until; ++y)
        s.insert(_Easter.make_holiday(y));

    const auto from = y_from / FirstDayOfJanuary;
    const auto until = y_until / LastDayOfDecember;

    const auto generated = schedule{ days_period{ from, until }, std::move(s) };

    cout << boolalpha;

    cout << "Are Easters from the file the same as generated Easters? " << (from_file == generated) << endl;

    return 0;

}
