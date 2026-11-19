"""
Pytest suite that executes every solution in problem_solutions/ and algorithm_implementation/.
"""
from pathlib import Path
import pytest
from problem_cases import REPO_ROOT, get_all_solution_files, run_solution_file

ALL_FILES = get_all_solution_files()


def pytest_generate_tests(metafunc):
    if "solution_file" in metafunc.fixturenames:
        target_path = metafunc.config.getoption("--path", default=None)
        if target_path:
            abs_target = Path(target_path).resolve()
            if abs_target.is_file():
                files = [abs_target]
            elif abs_target.is_dir():
                files = [f for f in ALL_FILES if abs_target in f.parents or f == abs_target]
            else:
                files = [f for f in ALL_FILES if target_path in str(f)]
        else:
            files = ALL_FILES

        ids = [str(f.relative_to(REPO_ROOT)) for f in files]
        metafunc.parametrize("solution_file", files, ids=ids)


def test_solution(solution_file: Path):
    success, message = run_solution_file(solution_file)
    assert success, f"Failed {solution_file.relative_to(REPO_ROOT)}: {message}"
