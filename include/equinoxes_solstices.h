// The MIT License (MIT)
//
// Copyright (c) 2023 Andrey Gorbachev
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "annual_holiday_interface.h"

#include <chrono>
#include <numbers>
#include <cmath>
#include <cassert>
#include <ranges>


namespace gregorian
{

	// from "Astronomical Algorithms" second edition 1998
	// by J.Meeus


	class vernal_equinox final : public annual_holiday
	{

	public:

//		explicit vernal_equinox() noexcept;

	private:

		auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_day _md;

	};


	const auto MarchEquinox = vernal_equinox{};



	class summer_solstice final : public annual_holiday
	{

	public:

//		explicit summer_solstice() noexcept;

	private:

		auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_day _md;

	};


	const auto JuneSolstice = summer_solstice{};



	class autumnal_equinox final : public annual_holiday
	{

	public:

//		explicit autumnal_equinox() noexcept;

	private:

		auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_day _md;

	};


	const auto SeptemberEquinox = autumnal_equinox{};



	class winter_solstice final : public annual_holiday
	{

	public:

//		explicit winter_solstice() noexcept;

	private:

		auto _make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day final;

	private:

		std::chrono::month_day _md;

	};


	const auto DecemberSolstice = winter_solstice{};



	auto _Y(const int year) noexcept -> double // constexpr?
	{
		return (static_cast<double>(year) - 2'000.0) / 1'000.0;
	}


	auto _T(const double JDE0) noexcept -> double
	{
		return (JDE0 - 2'451'545.0) / 36'525.0;
	}


	auto _W(const double T) noexcept -> double
	{
		return (35'999.373 * T - 2.47) * std::numbers::pi / 180.0;
	}


	auto _delta_lambda(const double W) noexcept -> double
	{
		return 1.0 + 0.0334 * std::cos(W) + 0.0007 * std::cos(2.0 * W); // are these noexcept? should we handle (assert) errors from there
	}


	auto _S(const double T) noexcept -> double
	{
		const auto _A = {
			485.0,
			203.0,
			199.0,
			182.0,
			156.0,
			136.0,
			77.0,
			74.0,
			70.0,
			58.0,
			52.0,
			50.0,
			45.0,
			44.0,
			29.0,
			18.0,
			17.0,
			16.0,
			14.0,
			12.0,
			12.0,
			12.0,
			9.0,
			8.0
		};

		const auto _B = {
			324.96,
			337.23,
			342.08,
			27.85,
			73.14,
			171.52,
			222.54,
			296.72,
			243.58,
			119.81,
			297.17,
			21.02,
			247.54,
			325.15,
			60.93,
			155.12,
			288.79,
			198.04,
			199.76,
			95.39,
			287.11,
			320.81,
			227.73,
			15.45
		};

		const auto _C = {
			1'934.136,
			32'964.467,
			20.186,
			445'267.112,
			45'036.886,
			22'518.443,
			65'928.934,
			3'034.906,
			9'037.513,
			33'718.147,
			150.678,
			2'281.226,
			29'929.562,
			31'555.956,
			4'443.417,
			67'555.328,
			4'562.452,
			62'894.029,
			31'436.921,
			14'577.848,
			31'931.756,
			34'777.259,
			1'222.114,
			16'859.074
		};

		auto S = 0.0;
		for (const auto [A, B, C] : std::views::zip(_A, _B, _C))
		{
			const auto b = B * std::numbers::pi / 180.0; // factor out?
			const auto c = C * std::numbers::pi / 180.0;

			S += A * std::cos(b + c * T); // are these noexcept? should we handle (assert) errors from there
		}

		return S; // do we need to convert this to int?
	}


	auto _JDE(const double JDE0, const double delta_lambda, const double S) noexcept -> double
	{
		return JDE0 + 0.00001 * S / delta_lambda;
	}



	auto _alfa(const int Z) noexcept -> int
	{
		return static_cast<int>((static_cast<double>(Z) - 1'867'216.25) / 36'524.25);
	}

	auto _A(const int Z) noexcept -> int
	{
		const auto alfa = _alfa(Z);

		return Z + 1 + alfa - static_cast<int>(static_cast<double>(alfa) / 4.0);
	}

	auto _B(const int A) noexcept -> int
	{
		return A + 1524;
	}

	auto _C(const int B) noexcept -> int
	{
		return static_cast<int>((static_cast<double>(B) - 122.1) / 365.25);
	}

	auto _D(const int C) noexcept -> int
	{
		return static_cast<int>(365.25 * static_cast<double>(C));
	}

	auto _E(const int B, const int D) noexcept -> int
	{
		return static_cast<int>((static_cast<double>(B - D)) / 30.6001);
	}

	struct _day_month_year
	{
		double day;
		int month;
		int year;
	};

	auto _calculate_date(double JD) noexcept -> _day_month_year
	{
		assert(JD > 0.0);

		JD += 0.5;

		auto _Z = double{};
		const auto F = std::modf(JD, &_Z);
		const auto Z = static_cast<int>(_Z);

		const auto A = Z < 2'299'161 ? Z : _A(Z);

		const auto B = _B(A);

		const auto C = _C(B);

		const auto D = _D(C);

		const auto E = _E(B, D);

		const auto day = static_cast<double>(B - D - static_cast<int>(30.6001 * static_cast<double>(E))) + F;

		const auto month = E < 14 ? E - 1 : E - 13;

		const auto year = month > 2 ? C - 4716 : C - 4715;

		return { day, month, year };
	}



	template<double C0, double C1, double C2, double C3, double C4>
	auto _equinox_solstice(const int y) noexcept -> _day_month_year
	{
		const auto Y = _Y(y);

		const auto JDE0 = C0 + C1 * Y + C2 * Y * Y + C3 * Y * Y * Y + C4 * Y * Y * Y * Y; // use std::pow?

		const auto T = _T(JDE0);

		const auto W = _W(T);

		const auto delta_lambda = _delta_lambda(W);

		const auto S = _S(T);

		const auto JDE = _JDE(JDE0, delta_lambda, S);

		return _calculate_date(JDE);
	}



	auto _from_std_chrono(const std::chrono::year y) noexcept -> int
	{
		return static_cast<int>(y);
	}
		
	auto _to_std_chrono(const _day_month_year& dmy) noexcept -> std::chrono::year_month_day
	{
		const auto [d, m, y] = dmy;
		assert(y >= 1 && y <= 9999);
		assert(m >= 1 && m <= 12);
		assert(d >= 1.0 && d <= 31.0);

		return std::chrono::year_month_day{
			std::chrono::year{ y },
			std::chrono::month{ static_cast<unsigned int>(m) },
			std::chrono::day{ static_cast<unsigned int>(d) }
		};
	}

	template<double C0, double C1, double C2, double C3, double C4>
	auto _equinox_solstice(const std::chrono::year& y) noexcept -> std::chrono::year_month_day
	{
		const auto yd = _from_std_chrono(y);

		const auto ymd = _equinox_solstice<C0, C1, C2, C3, C4>(yd);

		return _to_std_chrono(ymd);
	}



	inline auto vernal_equinox::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return _equinox_solstice<2'451'623.80984, 365'242.37404, 0.05169, -0.00411, -0.00057>(y);
	}



	inline auto summer_solstice::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return _equinox_solstice<2'451'716.56767, 365241.62603, 0.00325, 0.00888, -0.00030>(y);
	}



	inline auto autumnal_equinox::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return _equinox_solstice<2'451'810.21715, 365'242.01767, -0.11575, 0.00337, 0.00078>(y);
	}



	inline auto winter_solstice::_make_holiday(const std::chrono::year& y) const noexcept -> std::chrono::year_month_day
	{
		return _equinox_solstice<2'451'900.05952, 365'242.74049, -0.06223, -0.00823, 0.00032>(y);
	}

}
