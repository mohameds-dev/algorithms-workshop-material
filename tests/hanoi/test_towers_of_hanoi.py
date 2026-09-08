from pathlib import Path

from hanoi.harness import assert_solves_puzzle, hanoi_cases, load_hanoi_function

REPO_ROOT = Path(__file__).resolve().parents[2]
SOLUTION_PATH = REPO_ROOT / "algorithm_implementation" / "towers-of-hanoi" / "solution.py"

towers_of_hanoi = load_hanoi_function(SOLUTION_PATH)


@hanoi_cases
def test_towers_of_hanoi_correctness(case):
    assert_solves_puzzle(towers_of_hanoi, case)
