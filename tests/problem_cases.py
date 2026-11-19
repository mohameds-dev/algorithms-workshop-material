"""
Test execution helpers for all solutions in problem_solutions/ and algorithm_implementation/.
Each solution file contains its own test_solution() function with assertions.
"""
from pathlib import Path
import subprocess
import tempfile
from typing import List, Tuple

REPO_ROOT = Path(__file__).resolve().parent.parent


def get_all_solution_files() -> List[Path]:
    """Find all solution files in problem_solutions/ and algorithm_implementation/."""
    files = []
    for base in ["problem_solutions", "algorithm_implementation"]:
        base_dir = REPO_ROOT / base
        if not base_dir.is_dir():
            continue
        for p in sorted(base_dir.rglob("*")):
            if p.is_file() and p.suffix in [".py", ".cpp"] and "__pycache__" not in str(p):
                files.append(p)
    return files


def run_solution_file(file_path: Path, timeout: float = 10.0) -> Tuple[bool, str]:
    """
    Run a solution file (either Python or C++).
    Since each solution defines test_solution() executed on main,
    we simply execute it and verify exit code 0.
    Returns (success, message).
    """
    file_path = file_path.resolve()
    if not file_path.exists():
        return False, f"File not found: {file_path}"

    if file_path.suffix == ".py":
        try:
            res = subprocess.run(
                ["python3", str(file_path)],
                capture_output=True,
                text=True,
                timeout=timeout,
                cwd=str(REPO_ROOT),
            )
        except subprocess.TimeoutExpired:
            return False, f"Execution timed out after {timeout}s"
        except Exception as e:
            return False, f"Error running python: {e}"

        if res.returncode != 0:
            return False, f"Process exited with code {res.returncode}:\n{res.stderr.strip()}"

        return True, "Passed"

    elif file_path.suffix == ".cpp":
        with tempfile.TemporaryDirectory() as tmpdir:
            bin_path = Path(tmpdir) / "solution.out"
            try:
                comp = subprocess.run(
                    ["g++", "-std=c++20", "-O2", str(file_path), "-o", str(bin_path)],
                    capture_output=True,
                    text=True,
                    timeout=timeout,
                )
            except subprocess.TimeoutExpired:
                return False, f"Compilation timed out after {timeout}s"
            except Exception as e:
                return False, f"Compilation error: {e}"

            if comp.returncode != 0:
                return False, f"Compilation failed:\n{comp.stderr.strip()}"

            try:
                run_res = subprocess.run(
                    [str(bin_path)],
                    capture_output=True,
                    text=True,
                    timeout=timeout,
                    cwd=str(REPO_ROOT),
                )
            except subprocess.TimeoutExpired:
                return False, f"Execution timed out after {timeout}s"
            except Exception as e:
                return False, f"Execution error: {e}"

            if run_res.returncode != 0:
                return False, f"Process exited with code {run_res.returncode}:\n{run_res.stderr.strip()}"

            return True, "Passed"

    return False, f"Unsupported file type: {file_path.suffix}"
