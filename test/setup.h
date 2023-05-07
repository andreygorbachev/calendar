#include <calendar.h>
#include <ics_parser.h>

#include <fstream>


namespace
{

	auto test_parse_ics_holidays() -> const calendar::holidays_storage&
	{
		static auto fs = std::ifstream{ "../../test/data/england-and-wales.ics" };
		static auto holidays = _parse_ics(fs);

		return holidays;
	}

	auto test_parse_ics_calendar() -> const calendar&
	{
		static auto calendar = parse_ics("../../test/data/england-and-wales.ics");

		return calendar;
	}

}
