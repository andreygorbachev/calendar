#include <calendar.h>
#include <ics_parser.h>
#include <holiday.h>

#include <fstream>
#include <unordered_set>


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


	auto test_rule_england() -> calendar
	{
		using namespace std;
		using namespace std::chrono;

		auto rules = unordered_set<const annual_holiday*>{};
		rules.insert(&NewYearsDay);
		rules.insert(&GoodFriday);
		rules.insert(&EasterMonday);
		// ...

		return make_calendar(
			2023y,
			2023y,
			rules
		);
	}

}
