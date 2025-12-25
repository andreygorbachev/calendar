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

#include <static_data.h>

#include <calendar.h>
#include <weekend.h>
#include <period.h>
#include <schedule.h>

#include <chrono>
#include <iostream>
#include <ios>
#include <algorithm>

using namespace gregorian;
using namespace gregorian::util;
using namespace gregorian::static_data;

using namespace std;
using namespace std::chrono;



static auto parse_csv_ANBIMA_schedule() -> schedule
{
	// from https://www.anbima.com.br/feriados/arqs/feriados_nacionais.xls
	// (download it and re-save it as CSV)
	return parse_csv_schedule("feriados_nacionais.csv", 2001y, 2099y);
}


int main()
{
	const auto parsed = calendar{ SaturdaySundayWeekend, parse_csv_ANBIMA_schedule() };
	const auto& made = locate_calendar("America/ANBIMA");

	const auto& from = max(
		parsed.get_schedule().get_period().get_from(),
		made.get_schedule().get_period().get_from()
	);
	const auto& until = min(
		parsed.get_schedule().get_period().get_until(),
		made.get_schedule().get_period().get_until()
	);

	const auto cal1 = calendar{
		parsed.get_weekend(),
		schedule{ days_period{ from, until }, parsed.get_schedule().get_dates() }
	};
	const auto cal2 = calendar{
		made.get_weekend(),
		schedule{ days_period{ from, until }, made.get_schedule().get_dates() }
	};

	cout << boolalpha;

	cout << "Is parsed calendar the same as made calendar (over common dates)? " << (cal1 == cal2) << endl;

	return 0;
}
