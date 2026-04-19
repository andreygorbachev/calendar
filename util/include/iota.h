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

#include <chrono>
#include <ranges>
#include <iterator>

#include <period.h>

namespace gregorian
{

	namespace util
	{

		template<typename Dur> requires std::weakly_incrementable<typename Dur::rep>
		constexpr auto
		_iota(std::chrono::sys_time<Dur> from, std::chrono::sys_time<Dur> until) // half open period [from, until)
		{
			return
				std::views::iota(
					from.time_since_epoch().count(),
					until.time_since_epoch().count()
				) |
				std::views::transform(
					[](const Dur::rep r) { return std::chrono::sys_time<Dur>{ Dur{ r } }; }
				);
		}


		// how can we make this more generic?
		constexpr auto iota(const days_period& p) // closed period [from, until]
		{
			const auto& f = std::chrono::sys_days{ p.get_from() };
			const auto u = std::chrono::sys_days{ p.get_until() } + std::chrono::days{ 1 };

			return _iota(f, u);
		}

		// add months_period and years_period

	}

}
