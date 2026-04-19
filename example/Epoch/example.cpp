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

#include <calendar.h>

#include <chrono>
#include <iostream>
#include <ios>

using namespace gregorian;
using namespace gregorian::static_data;

using namespace std;
using namespace std::chrono;



int main()
{
	const auto as_of_date = floor<days>(system_clock::now());
	const auto& cal = locate_calendar("America/ANBIMA", as_of_date);

	cout << "   date   " << ", " << "is business day" << endl;
	cout << boolalpha;
	for (
		auto d = Epoch.get_from();
		d <= Epoch.get_until();
		d = ++sys_days{ d }
	)
		cout << d << ", " << cal.is_business_day(d) << endl;

	return 0;
}
