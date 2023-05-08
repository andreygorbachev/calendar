#include <calendar.h>
#include <ics_parser.h>

#include <fstream>


namespace
{

	auto test_parse_ics_england() -> const calendar&
	{
		// from https://www.gov.uk/bank-holidays
		static auto calendar = parse_ics("../../test/data/england-and-wales.ics");

		return calendar;
	}

	auto test_parse_ics_united_states() -> const calendar&
	{
		// from https://www.newyorkfed.org/aboutthefed/holiday_schedule
		static auto calendar = parse_ics("../../test/data/united-states.ics");

		return calendar;
	}

}
