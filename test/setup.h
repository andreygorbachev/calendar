#include <calendar.h>
#include <ics_parser.h>

#include <fstream>


namespace
{

	auto test_parse_ics_england() -> const calendar&
	{
		static auto calendar = parse_ics("../../test/data/england-and-wales.ics");

		return calendar;
	}

	auto test_parse_ics_united_states() -> const calendar&
	{
		static auto calendar = parse_ics("../../test/data/united-states.ics");

		return calendar;
	}

}
