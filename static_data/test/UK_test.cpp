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

		// I guess as we treat all data as code, we should unit test it as well
		TEST(static, England)
		{
			const auto& cal0 = locate_calendar("Europe/London", 1998y / January / 1d);
			EXPECT_FALSE(cal0.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_TRUE(cal0.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_FALSE(cal0.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal0.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal0.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal0.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal0.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal0.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal0.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal0.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal0.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal0.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal1a = locate_calendar("Europe/London", 1998y / June / 2d);
			EXPECT_FALSE(cal1a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_TRUE(cal1a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_FALSE(cal1a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal1a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal1a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal1a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal1a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal1a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal1a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal1a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal1a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal1a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal1b = locate_calendar("Europe/London", 1998y / June / 3d);
			EXPECT_TRUE(cal1b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_TRUE(cal1b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_FALSE(cal1b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal1b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal1b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal1b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal1b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal1b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal1b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal1b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal1b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal1b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal2a = locate_calendar("Europe/London", 2000y / November / 22d);
			EXPECT_TRUE(cal2a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_TRUE(cal2a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_FALSE(cal2a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal2a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal2a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal2a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal2a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal2a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal2a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal2a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal2a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal2a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal2b = locate_calendar("Europe/London", 2000y / November / 23d);
			EXPECT_TRUE(cal2b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal2b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal2b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal2b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal2b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal2b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal2b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal2b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal2b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal2b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal2b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal2b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal3a = locate_calendar("Europe/London", 2010y / January / 4d);
			EXPECT_TRUE(cal3a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal3a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal3a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal3a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal3a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal3a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal3a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal3a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal3a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal3a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal3a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal3a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal3b = locate_calendar("Europe/London", 2010y / January / 5d);
			EXPECT_TRUE(cal3b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal3b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal3b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal3b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal3b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal3b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal3b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal3b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal3b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal3b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal3b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal3b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal4a = locate_calendar("Europe/London", 2010y / November / 22d);
			EXPECT_TRUE(cal4a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal4a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal4a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal4a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal4a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_FALSE(cal4a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal4a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal4a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal4a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal4a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal4a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal4a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal4b = locate_calendar("Europe/London", 2010y / November / 23d);
			EXPECT_TRUE(cal4b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal4b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal4b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal4b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal4b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal4b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal4b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal4b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal4b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal4b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal4b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal4b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal5a = locate_calendar("Europe/London", 2019y / June / 6d);
			EXPECT_TRUE(cal5a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal5a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal5a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal5a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal5a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal5a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_TRUE(cal5a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_FALSE(cal5a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal5a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal5a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal5a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal5a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal5b = locate_calendar("Europe/London", 2019y / June / 7d); // so the new calendar is available from the day of announcement, which might or might not be what we want
			EXPECT_TRUE(cal5b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal5b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal5b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal5b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal5b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal5b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal5b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal5b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal5b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal5b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal5b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal5b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal6a = locate_calendar("Europe/London", 2020y / November / 11d);
			EXPECT_TRUE(cal6a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal6a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal6a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal6a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal6a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal6a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal6a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal6a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_TRUE(cal6a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_FALSE(cal6a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal6a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal6a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal6b = locate_calendar("Europe/London", 2020y / November / 12d);
			EXPECT_TRUE(cal6b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal6b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal6b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal6b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal6b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal6b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal6b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal6b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_FALSE(cal6b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_TRUE(cal6b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal6b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal6b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal7a = locate_calendar("Europe/London", 2022y / September / 9d);
			EXPECT_TRUE(cal7a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal7a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal7a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal7a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal7a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal7a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal7a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal7a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_FALSE(cal7a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_TRUE(cal7a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_FALSE(cal7a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal7a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal7b = locate_calendar("Europe/London", 2022y / September / 10d);
			EXPECT_TRUE(cal7b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal7b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal7b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal7b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal7b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal7b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal7b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal7b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_FALSE(cal7b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_TRUE(cal7b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_TRUE(cal7b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal7b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal8a = locate_calendar("Europe/London", 2022y / November / 5d);
			EXPECT_TRUE(cal8a.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal8a.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal8a.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal8a.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal8a.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal8a.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal8a.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal8a.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_FALSE(cal8a.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_TRUE(cal8a.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_TRUE(cal8a.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_FALSE(cal8a.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III

			const auto& cal8b = locate_calendar("Europe/London", 2022y / November / 6d);
			EXPECT_TRUE(cal8b.is_non_business_day(1999y / December / 31d)); // Millennium Eve
			EXPECT_FALSE(cal8b.is_non_business_day(2002y / May / 27d)); // Spring bank holiday
			EXPECT_TRUE(cal8b.is_non_business_day(2002y / June / 3d)); // Queen's Golden Jubilee
			EXPECT_TRUE(cal8b.is_non_business_day(2002y / June / 4d)); // Queen's Golden Jubilee
			EXPECT_FALSE(cal8b.is_non_business_day(2012y / May / 28d)); // Spring bank holiday
			EXPECT_TRUE(cal8b.is_non_business_day(2012y / June / 5d)); // Queen's Diamond Jubilee
			EXPECT_FALSE(cal8b.is_non_business_day(2020y / May / 4d)); // Early May bank holiday
			EXPECT_TRUE(cal8b.is_non_business_day(2020y / May / 8d)); // 75th anniversary of VE Day
			EXPECT_FALSE(cal8b.is_non_business_day(2022y / May / 30d)); // Spring bank holiday
			EXPECT_TRUE(cal8b.is_non_business_day(2022y / June / 3d)); // Queen’s Platinum Jubilee
			EXPECT_TRUE(cal8b.is_non_business_day(2022y / September / 19d)); // State Funeral of Queen Elizabeth II
			EXPECT_TRUE(cal8b.is_non_business_day(2023y / May / 8d)); // coronation of King Charles III
		}

	}

}
