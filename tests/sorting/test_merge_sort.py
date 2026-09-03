from pathlib import Path

from sorting.harness import assert_sorts_correctly, load_sort_function, sort_cases

REPO_ROOT = Path(__file__).resolve().parents[2]
SOLUTION_PATH = REPO_ROOT / "algorithm_implementation" / "merge-sort" / "solution.py"

merge_sort = load_sort_function(SOLUTION_PATH)


@sort_cases
def test_merge_sort_correctness(case):
    assert_sorts_correctly(merge_sort, case)
