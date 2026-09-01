"""Generic correctness tests, run against every registered sorting algorithm.

Run everything:
    uv run pytest

Run just one algorithm (matches on its registry name below):
    uv run pytest -k merge_sort

Run just one case, across every algorithm:
    uv run pytest -k reverse_sorted

Add a new algorithm to test: add one entry to SORT_IMPLEMENTATIONS below,
pointing at its solution file. That file must define a top-level
`sort(a)` function returning `a` sorted in nondecreasing order (see
algorithm_implementation/merge-sort/solution.py). Every case in cases.py
then runs against it automatically; nothing else to wire up.

Add a new test case: add one SortCase to cases.py's SORT_CASES list. It
runs against every registered algorithm automatically.
"""

from __future__ import annotations

import importlib.util
from pathlib import Path
from typing import Callable

import pytest
from sorting.cases import SORT_CASES

REPO_ROOT = Path(__file__).resolve().parents[2]

# Registry of every sorting algorithm under test: name -> path to its
# solution file. The name is what shows up in test IDs and `-k` filters.
SORT_IMPLEMENTATIONS: dict[str, Path] = {
    "merge_sort": REPO_ROOT / "algorithm_implementation" / "merge-sort" / "solution.py",
}


def _load_sort_function(path: Path) -> Callable[[list], list]:
    if not path.is_file():
        raise FileNotFoundError(f"no solution file at {path}")

    spec = importlib.util.spec_from_file_location(path.stem, path)
    if spec is None or spec.loader is None:
        raise ImportError(f"could not load a module spec for {path}")

    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)

    if not hasattr(module, "sort"):
        raise AttributeError(f"{path} does not define a top-level `sort(a)` function")

    return module.sort


SORT_FUNCTIONS: dict[str, Callable[[list], list]] = {
    name: _load_sort_function(path) for name, path in SORT_IMPLEMENTATIONS.items()
}


@pytest.mark.parametrize("case", SORT_CASES, ids=lambda c: c.name)
@pytest.mark.parametrize("algorithm", sorted(SORT_FUNCTIONS))
def test_sort_correctness(algorithm: str, case) -> None:
    sort_fn = SORT_FUNCTIONS[algorithm]

    # Pass a fresh copy in: a case's input list is shared across every
    # algorithm this runs against, so an in-place sort must never be able
    # to mutate the shared original.
    result = sort_fn(list(case.input))
    expected = sorted(case.input)

    assert result == expected, (
        f"{algorithm} on case '{case.name}': "
        f"input={case.input!r} expected={expected!r} got={result!r}"
    )
