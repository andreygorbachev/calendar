#pragma once

#include <chrono>
#include <cmath>



class annual_holiday
{

public:

	virtual ~annual_holiday() noexcept = default;

public:

	virtual auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day = 0;

};



class GoodFriday final : public annual_holiday
{

public:

	auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

};



class EasterMonday final : public annual_holiday
{

public:

	auto holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

};


// https://en.wikipedia.org/wiki/Date_of_Easter

inline auto make_Easter(const std::chrono::year& y) noexcept -> std::chrono::year_month_day
{
	const auto Y = static_cast<int>(y);

	const auto a = Y % 19;

	const auto b = static_cast<int>(std::floor(static_cast<double>(Y) / 100.0));

	const auto c = Y % 100;

	const auto d = static_cast<int>(std::floor(static_cast<double>(b) / 4.0));

	const auto e = b % 4;

	const auto g = static_cast<int>(std::floor((8.0 * static_cast<double>(b) + 13.0) / 25.0));

	const auto h = (19 * a + b - d - g + 15) % 30;

	const auto i = static_cast<int>(std::floor(static_cast<double>(c) / 4.0));

	const auto k = c % 4;

	const auto l = (32 + 2 * e + 2 * i - h - k) % 7;

	const auto m = static_cast<int>(std::floor((static_cast<double>(a) + 11.0 * static_cast<double>(h) + 19.0 * static_cast<double>(l)) / 433.0));

	const auto n = static_cast<int>(std::floor((static_cast<double>(h) + static_cast<double>(l) - 7.0 * static_cast<double>(m) + 90.0) / 25.0));

	const auto p = (h + l - 7 * m + 33 * n + 19) % 32;

	return { y, std::chrono::month{ static_cast<unsigned>(n) }, std::chrono::day{ static_cast<unsigned>(p) } };
}



auto GoodFriday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
{
	const auto easterSunday = make_Easter(y);

	return std::chrono::sys_days{ easterSunday } - std::chrono::days{ 2 };
}


auto EasterMonday::holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
{
	const auto easterSunday = make_Easter(y);

	return std::chrono::sys_days{ easterSunday } + std::chrono::days{ 1 };
}
