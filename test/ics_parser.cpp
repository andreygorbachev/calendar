#include <calendar.h>
#include <ics_parser.h>

#include <gtest/gtest.h>

#include <chrono>

#include "setup.h"

using namespace std;
using namespace std::chrono;


namespace
{

	TEST(ics_parser, _start)
	{
		EXPECT_EQ(2018y/January/1d, _start(test_parse_ics()));
	}

	TEST(ics_parser, _end)
	{
		EXPECT_EQ(2025y/December/31d, _end(test_parse_ics()));
	}

}
