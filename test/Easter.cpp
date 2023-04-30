#include <holiday.h>

using namespace std::chrono;


constexpr auto Easter_tests() -> bool
{
	constexpr auto e_calculated = get_Easter(2023y);
	constexpr auto e_expected = 2023y/April/9d;

	static_assert(e_calculated == e_expected);
}


int main()
{
	Easter_tests();
}
