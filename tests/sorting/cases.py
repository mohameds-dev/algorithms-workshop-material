"""Reusable test cases for any sorting-algorithm implementation.

Every case here only assumes the function under test takes a list of
orderable elements and returns them sorted in nondecreasing order. Add a
case once, here, and every algorithm registered in test_sorting.py picks it
up automatically; no per-algorithm test code needed.

To add a case: append a SortCase to SORT_CASES, with a descriptive
snake_case name (it becomes part of the test ID, e.g.
`test_sort_correctness[merge_sort-your_case_name]`).
"""

from __future__ import annotations

import random
from dataclasses import dataclass


@dataclass(frozen=True)
class SortCase:
    name: str
    input: list[int]


def _random_list(seed: int, size: int, low: int = -1000, high: int = 1000) -> list[int]:
    """A reproducible pseudo-random list; same seed always gives the same list."""
    rng = random.Random(seed)
    return [rng.randint(low, high) for _ in range(size)]


SORT_CASES: list[SortCase] = [
    SortCase("empty_list", []),
    SortCase("single_element", [42]),
    SortCase("two_elements_already_sorted", [1, 2]),
    SortCase("two_elements_reversed", [2, 1]),
    SortCase("two_equal_elements", [7, 7]),
    SortCase("already_sorted", [1, 2, 3, 4, 5]),
    SortCase("reverse_sorted", [9, 7, 5, 3, 1]),
    SortCase("all_duplicates", [4, 4, 4, 4, 4]),
    SortCase("all_zeros", [0, 0, 0]),
    SortCase("negative_numbers", [-3, -1, -7, 0, 5, -2]),
    SortCase("mixed_with_duplicates", [5, 2, 3, 1, 4, 4, -1]),
    SortCase("odd_length", [8, 1, 6, 3, 5]),
    SortCase("descending_then_ascending", [5, 4, 3, 1, 2, 3, 4]),
    SortCase("random_small", _random_list(seed=1, size=20)),
    SortCase("random_medium", _random_list(seed=2, size=200)),
    SortCase("random_large", _random_list(seed=3, size=1000)),
    SortCase("random_many_duplicates", _random_list(seed=4, size=200, low=0, high=5)),
]
