#include <holiday_schedule.h>
#include <ics_parser.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace calendar
{

	auto test_parse_ics_holidays() -> const holiday_schedule::storage&
	{
		static auto fs = std::ifstream{ "../../test/data/england-and-wales.ics" };
		static auto hols = _parse_ics(fs);

		return hols;
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
