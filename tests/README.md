# Test suite

A test suite that checks all solutions across `../problem_solutions/` and
`../algorithm_implementation/` for correctness in Python and C++20.

## Setup

From this directory:

```bash
uv sync
```

## Running Tests

### Option 1: Fast CLI Runner (Best for single files or problem folders)

Use `tests/run_solution.py` from the repository root:

```bash
# Test a specific Python or C++ solution file:
python tests/run_solution.py problem_solutions/shortest-routes-i/solution.py
python tests/run_solution.py problem_solutions/shortest-routes-i/solution.cpp

# Test all solutions for a specific problem folder:
python tests/run_solution.py problem_solutions/shortest-routes-i/
python tests/run_solution.py shortest-routes-i

# Run tests on every solution across the entire repo:
python tests/run_solution.py
```

### Option 2: Running with pytest

From the `tests/` directory:

```bash
# Run everything:
uv run pytest

# Run tests for a specific file path using --path:
uv run pytest test_solutions.py --path problem_solutions/shortest-routes-i/solution.py

# Run tests for a specific problem using -k keyword filter:
uv run pytest -k shortest-routes-i
uv run pytest -k network-delay-time

# Run only Python or only C++ tests:
uv run pytest -k solution.py
uv run pytest -k solution.cpp

# Run canonical algorithm tests:
uv run pytest -k merge_sort
uv run pytest sorting
uv run pytest hanoi
```

## How Solutions Are Tested

Every solution file in `problem_solutions/` and `algorithm_implementation/` is **self-testing**. Test inputs and assertions live directly inside the file within a `test_solution()` function called from the file's main execution block:

### Python Pattern
```python
def test_solution():
    sol = Solution()
    assert sol.method(...) == expected_value


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
```

### C++20 Pattern
```cpp
#include <cassert>

void test_solution() {
    Solution sol;
    assert(sol.method(...) == expected_value);
}

int main() {
    test_solution(); // Comment this out to run with custom inputs
    return 0;
}
```

This structure makes running tests straightforward:
1. Executing `python3 <file.py>` or compiling and running `<file.cpp>` runs the test assertions.
2. If all assertions pass, the program exits with code `0`. If any assertion fails, it exits with a non-zero code and pinpoints the failing assertion line.
3. To run the file with custom inputs or standard input, simply comment out the `test_solution()` call.

## Canonical Algorithms Suite (`tests/sorting/` and `tests/hanoi/`)

In addition to the self-tests in each solution file, standalone canonical algorithms in `algorithm_implementation/` are verified against reusable test suites:

- `sorting/`: validates that the function sorts arbitrary inputs nondecreasingly.
- `hanoi/`: simulates disk movements onto three stacks, verifying move legality, disk constraints, and the optimal $2^n - 1$ move count.
