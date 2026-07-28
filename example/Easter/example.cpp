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

#include <chrono>
#include <iostream>
#include <ios>

using namespace gregorian;

using namespace std;
using namespace std::chrono;



int main()
{

    const auto from = 1600y;
    const auto until = 2099y;

    // from https://www.census.gov/data/software/x13as/genhol/easter-dates-frequency.html

    const auto from_file = parse_txt_schedule("easter500.txt", from, until);

    // generate Easter dates for the same year range so we can compare schedules
    auto s = schedule::dates{};
    for (auto y = from; y <= until; ++y)
        s.insert(_Easter.make_holiday(y));

    const auto generated = schedule{ from_file.get_period(), std::move(s) };

    return 0;

}