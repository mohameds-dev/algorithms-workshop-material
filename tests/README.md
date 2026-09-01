# Test suite

A pytest suite that checks the solutions in `../algorithm_implementation/` for correctness,
using shared, reusable test cases per problem category (currently: sorting).

## Setup

From this directory:

```
uv sync
```

## Running

```
uv run pytest                    # everything
uv run pytest -k merge_sort      # just one algorithm
uv run pytest -k reverse_sorted  # just one case, across every algorithm
uv run pytest -v                 # list every test that ran, by name
```

## Adding a test case

Sorting cases live in `sorting/cases.py`. Add one `SortCase(name, input)` to `SORT_CASES`; it
runs against every registered sorting algorithm automatically.

## Adding a new algorithm

Sorting algorithms are registered in `sorting/test_sorting.py`'s `SORT_IMPLEMENTATIONS` dict:
add one `"algorithm_name": path/to/solution.py` entry. The solution file must define a
top-level `sort(a)` function that returns `a` sorted in nondecreasing order. Every existing
case then runs against it automatically.

## Adding a new category (not sorting)

Copy the shape of `sorting/`: a `cases.py` for reusable inputs/expectations, and a
`test_<category>.py` with its own implementation registry and one generic test function. Keep
the case data and the runner separate, the way `sorting/` does, so cases stay reusable if a
second test function (e.g. a performance check) is added later.
