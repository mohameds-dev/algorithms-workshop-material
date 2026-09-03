import importlib.util
from pathlib import Path
from typing import Callable

import pytest
from sorting.cases import SORT_CASES, SortCase

sort_cases = pytest.mark.parametrize("case", SORT_CASES, ids=lambda c: c.name)


def load_sort_function(solution_path: Path) -> Callable[[list], list]:
    if not solution_path.is_file():
        raise FileNotFoundError(f"no solution file at {solution_path}")

    # importlib, not a normal import: because "algorithm_implementation/merge-sort/" isn't a valid package name
    spec = importlib.util.spec_from_file_location(solution_path.stem, solution_path)
    if spec is None or spec.loader is None:
        raise ImportError(f"could not load a module spec for {solution_path}")

    solution_module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(solution_module)

    if not hasattr(solution_module, "sort"):
        raise AttributeError(f"{solution_path} does not define a top-level `sort(a)` function")

    return solution_module.sort


def assert_sorts_correctly(sort_fn: Callable[[list], list], case: SortCase) -> None:
    actual = sort_fn(list(case.input))
    expected = sorted(case.input)
    assert actual == expected, f"input={case.input!r} expected={expected!r} got={actual!r}"
