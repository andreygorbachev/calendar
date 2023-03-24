#include "..\include\calendar.h"


int main()
{
	const auto c1 = basic_calendar{}; // Saturday/Sunday
	const auto c2 = basic_calendar{ basic_calendar::weekend_storage{} }; // no weekend

	static_assert(c1 != c2);
}
