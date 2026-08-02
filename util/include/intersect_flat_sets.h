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

#include <flat_set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <utility>


namespace gregorian
{

	namespace util
	{

		template <typename Key>
		[[nodiscard]] auto intersect_flat_sets(const std::flat_set<Key>& a, const std::flat_set<Key>& b) -> std::flat_set<Key> // make it more generic?
		{
			auto result = std::vector<Key>{};
			// The intersection size will never exceed the size of the smaller set
			result.reserve(std::min(a.size(), b.size()));

			// Find overlapping elements in O(N + M) time
			std::ranges::set_intersection(a, b, std::back_inserter(result));

			// Construct flat_set without re-sorting or re-checking duplicates
			return std::flat_set<Key>(std::sorted_unique, std::move(result));
		}

	}

}
