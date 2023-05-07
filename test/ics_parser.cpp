#include <calendar.h>
#include <ics_parser.h>

#include <gtest/gtest.h>

#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;


namespace
{

	auto parse_ics() -> const calendar::holidays_storage&
	{
		static auto fs = ifstream{ "../../test/data/england-and-wales.ics" };
		static auto holidays = _parse_ics(fs);

		return holidays;
	}


	TEST(ics_parser, _start)
	{
		EXPECT_EQ(2018y/January/1d, _start(parse_ics()));
	}

	TEST(ics_parser, _end)
	{
		EXPECT_EQ(2025y/December/31d, _end(parse_ics()));
	}

}
