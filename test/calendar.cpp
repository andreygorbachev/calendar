#include <calendar.h>

using namespace std;
using namespace std::chrono;


constexpr auto make_May_calendar() -> calendar
{
	auto hols = calendar::holiday_storage{
		2023y/May/1d,
		2023y/May/8d,
		2023y/May/29d,
	};

	return calendar{ move(hols) };
}


constexpr void calendar_tests()
{
	const auto c = make_May_calendar();
}


int main()
{
	calendar_tests();
}
