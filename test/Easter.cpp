#include <holiday.h>

using namespace std::chrono;


constexpr auto Easter_tests() -> bool
{
	constexpr auto e_calculated1 = get_Easter(1961y);
	constexpr auto e_expected1 = 1961y/April/2d;

	static_assert(e_calculated1 == e_expected1);

	constexpr auto e_calculated2 = get_Easter(2023y);
	constexpr auto e_expected2 = 2023y/April/9d;

	static_assert(e_calculated2 == e_expected2);
}


int main()
{
	Easter_tests();
}
