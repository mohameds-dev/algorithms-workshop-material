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

Copy `sorting/test_merge_sort.py` to `sorting/test_<algorithm>.py`, and change `SOLUTION_PATH`
to point at the new algorithm's solution file (and rename the test function, so failures are
reported under the right name). That's the whole file:

```python
from pathlib import Path

from sorting.harness import assert_sorts_correctly, load_sort_function, sort_cases

REPO_ROOT = Path(__file__).resolve().parents[2]
SOLUTION_PATH = REPO_ROOT / "algorithm_implementation" / "<algorithm-slug>" / "solution.py"

<algorithm> = load_sort_function(SOLUTION_PATH)


@sort_cases
def test_<algorithm>_correctness(case):
    assert_sorts_correctly(<algorithm>, case)
```

The solution file must define a top-level `sort(a)` function that returns `a` sorted in
nondecreasing order. Every case in `cases.py` runs against it automatically; nothing in
`cases.py` or `harness.py` needs to change.

## Adding a new category (not sorting)

Copy the shape of `sorting/`: a `cases.py` for reusable inputs/expectations, a `harness.py`
with the loading/assertion logic shared by every algorithm in the category, and one
`test_<algorithm>.py` per algorithm that imports the harness and points it at that algorithm's
solution file. Keep case data, harness, and per-algorithm files separate, the way `sorting/`
does, so adding an algorithm never means editing an existing file, and adding a case or a
second kind of check (e.g. a performance test) never means touching every algorithm's file.
