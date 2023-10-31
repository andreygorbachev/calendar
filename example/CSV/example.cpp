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

#include <weekend.h>
#include <schedule.h>
#include <calendar.h>

#include <chrono>
#include <iostream>

using namespace gregorian;

using namespace std;
using namespace std::chrono;



inline auto parse_csv_NYM_schedule() -> schedule
{
	// from https://www.cdsmodel.com/fee-computations.html
	return parse_csv_schedule("..\\..\\..\\example\\CSV\\data\\NYM.csv", 2009y, 2070y); // or set a working directory?
}

inline auto parse_csv_TYO_schedule() -> schedule
{
	// from https://www.cdsmodel.com/fee-computations.html
	return parse_csv_schedule("..\\..\\..\\example\\CSV\\data\\TYO.csv", 2009y, 2070y);
}

inline auto parse_csv_NNT_schedule() -> schedule
{
	// from https://www.cdsmodel.com/fee-computations.html
	return parse_csv_schedule("..\\..\\..\\example\\CSV\\data\\NNT.csv", 2009y, 2070y);
}



int main()
{
	const auto NYM = calendar{ SaturdaySundayWeekend, parse_csv_NYM_schedule() };
	const auto TYO = calendar{ SaturdaySundayWeekend, parse_csv_TYO_schedule() };
	const auto c = NYM | TYO;

	const auto NNT = calendar{ SaturdaySundayWeekend, parse_csv_NNT_schedule() };

	cout << "Is a joint calendar (NNT) the same as a joint of 2 calendars (NYC and TYO)? " << (NNT == c) << endl;

	return 0;
}
