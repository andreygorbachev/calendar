#include <calendar.h>
#include <ics_parser.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace
{

	auto test_parse_ics_holidays() -> const calendar::holidays_storage&
	{
		static auto fs = std::ifstream{ "../../test/data/england-and-wales.ics" };
		static auto holidays = _parse_ics(fs);

		return holidays;
	}


	TEST(ics_parser, _start)
	{
		EXPECT_EQ(2018y/January/1d, _start(test_parse_ics_holidays()));
	}

	TEST(ics_parser, _end)
	{
		EXPECT_EQ(2025y/December/31d, _end(test_parse_ics_holidays()));
	}

}
