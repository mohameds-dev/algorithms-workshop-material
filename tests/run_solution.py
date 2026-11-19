#!/usr/bin/env python3
"""
CLI test runner for solutions in problem_solutions/ and algorithm_implementation/.

Usage:
    # Run all solutions:
    python tests/run_solution.py

    # Run solutions for a specific problem or file:
    python tests/run_solution.py problem_solutions/shortest-routes-i/solution.py
    python tests/run_solution.py problem_solutions/shortest-routes-i/solution.cpp
    python tests/run_solution.py shortest-routes-i
"""
from pathlib import Path
import sys
import time

REPO_ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO_ROOT / "tests"))

from problem_cases import get_all_solution_files, run_solution_file  # noqa: E402


def main():
    args = sys.argv[1:]
    all_files = get_all_solution_files()

    if args:
        target = args[0]
        abs_target = Path(target).resolve()
        if abs_target.is_file():
            targets = [abs_target]
        elif abs_target.is_dir():
            targets = [f for f in all_files if abs_target in f.parents or f == abs_target]
        else:
            targets = [f for f in all_files if target in str(f)]
    else:
        targets = all_files

    if not targets:
        print(f"Error: No solution files matched '{args[0]}'")
        sys.exit(1)

    print(f"Testing {len(targets)} solution file(s)...\n")

    passed = 0
    failed = 0
    start_all = time.time()

    for idx, f in enumerate(targets, 1):
        rel_path = str(f.relative_to(REPO_ROOT))
        start_t = time.time()
        success, message = run_solution_file(f)
        elapsed = time.time() - start_t

        if success:
            passed += 1
            print(f"[{idx}/{len(targets)}] PASS ({elapsed:.2f}s) {rel_path}")
        else:
            failed += 1
            print(f"[{idx}/{len(targets)}] FAIL ({elapsed:.2f}s) {rel_path}")
            print(f"    --> {message}\n")

    total_time = time.time() - start_all
    print(f"\nSummary: {passed} passed, {failed} failed in {total_time:.2f}s")
    if failed > 0:
        sys.exit(1)


if __name__ == "__main__":
    main()
