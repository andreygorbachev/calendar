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

#include <chrono>

using namespace std::chrono;


namespace gregorian
{

	namespace static_data
	{

		TEST(static, ANBIMA)
		{
			// mostly a duplicate of a locate calendar test
			const auto& cal0 = locate_calendar("America/ANBIMA", Epoch.get_from());
			EXPECT_FALSE(cal0.is_non_business_day(2024y / November / 20d)); // Dia Nacional de Zumbi e da Consciência Negra

			const auto& cal1a = locate_calendar("America/ANBIMA", 2023y / December / 20d);
			EXPECT_FALSE(cal1a.is_non_business_day(2024y / November / 20d)); // Dia Nacional de Zumbi e da Consciência Negra

			const auto& cal1b = locate_calendar("America/ANBIMA", 2023y / December / 21d);
			EXPECT_TRUE(cal1b.is_non_business_day(2024y / November / 20d)); // Dia Nacional de Zumbi e da Consciência Negra
		}

	}

}
