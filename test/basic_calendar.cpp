#include <calendar.h>

using namespace std::chrono;



constexpr auto make_FSS() -> basic_calendar::weekend_storage
{
	auto we = basic_calendar{}.get_weekend(); // start with Saturday/Sunday
	we[std::chrono::Friday.c_encoding()] = true; // add Friday

	return we;
}



constexpr void basic_calendar_tests()
{
	constexpr auto c1 = basic_calendar{}; // weekend on Saturday/Sunday
	constexpr auto c2 = basic_calendar{ basic_calendar::weekend_storage{} }; // no weekend

	static_assert(c1 != c2);

	// Friday
	static_assert(c1.is_business_day({ 2023y/March/24d }));
	static_assert(c2.is_business_day({ 2023y/March/24d }));

	// Saturday
	static_assert(!c1.is_business_day({ 2023y/March/25d }));
	static_assert(c2.is_business_day({ 2023y/March/25d }));

	// Sunday
	static_assert(!c1.is_business_day({ 2023y/March/26d }));
	static_assert(c2.is_business_day({ 2023y/March/26d }));

	// Monday
	static_assert(c1.is_business_day({ 2023y/March/27d }));
	static_assert(c2.is_business_day({ 2023y/March/27d }));

	constexpr auto c3 = basic_calendar{ make_FSS() }; // weekend on Friday/Saturday/Sunday

	static_assert(c1 != c3);
}


int main()
{
	basic_calendar_tests();
}
