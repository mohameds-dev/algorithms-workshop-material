import os
import subprocess
from pathlib import Path
import pytest

REPO_ROOT = Path(__file__).resolve().parent.parent
SCRIPT_PATH = REPO_ROOT / "run_cpp.sh"


def test_script_exists_and_executable():
    assert SCRIPT_PATH.is_file(), f"{SCRIPT_PATH} does not exist"
    assert os.access(SCRIPT_PATH, os.X_OK), f"{SCRIPT_PATH} is not executable"


def test_missing_argument():
    result = subprocess.run([str(SCRIPT_PATH)], capture_output=True, text=True)
    assert result.returncode != 0
    assert "Usage:" in result.stderr


def test_nonexistent_file():
    result = subprocess.run(
        [str(SCRIPT_PATH), "does_not_exist.cpp"],
        capture_output=True,
        text=True,
    )
    assert result.returncode != 0
    assert "not found" in result.stderr.lower() or "does not exist" in result.stderr.lower()


def test_successful_compilation_and_cleanup(tmp_path):
    cpp_file = tmp_path / "hello.cpp"
    cpp_file.write_text(
        '#include <iostream>\n'
        'int main() {\n'
        '    std::cout << "Hello from C++20!" << std::endl;\n'
        '    return 0;\n'
        '}\n'
    )
    expected_bin = tmp_path / "hello.out"

    result = subprocess.run(
        [str(SCRIPT_PATH), str(cpp_file)],
        capture_output=True,
        text=True,
    )
    assert result.returncode == 0
    assert "Hello from C++20!" in result.stdout
    assert not expected_bin.exists()


def test_passes_arguments_to_executable(tmp_path):
    cpp_file = tmp_path / "args.cpp"
    cpp_file.write_text(
        '#include <iostream>\n'
        'int main(int argc, char* argv[]) {\n'
        '    for (int i = 1; i < argc; ++i) std::cout << argv[i] << " ";\n'
        '    std::cout << std::endl;\n'
        '    return 0;\n'
        '}\n'
    )

    result = subprocess.run(
        [str(SCRIPT_PATH), str(cpp_file), "apple", "banana"],
        capture_output=True,
        text=True,
    )
    assert result.returncode == 0
    assert result.stdout.strip() == "apple banana"


def test_compilation_error_shows_and_cleans_up(tmp_path):
    cpp_file = tmp_path / "invalid.cpp"
    cpp_file.write_text(
        '#include <iostream>\n'
        'int main() {\n'
        '    syntax_error_here;\n'
        '    return 0;\n'
        '}\n'
    )
    expected_bin = tmp_path / "invalid.out"

    result = subprocess.run(
        [str(SCRIPT_PATH), str(cpp_file)],
        capture_output=True,
        text=True,
    )
    assert result.returncode != 0
    assert "syntax_error_here" in result.stderr
    assert not expected_bin.exists()


def test_cleanup_on_runtime_failure(tmp_path):
    cpp_file = tmp_path / "fail.cpp"
    cpp_file.write_text(
        '#include <iostream>\n'
        'int main() {\n'
        '    return 42;\n'
        '}\n'
    )
    expected_bin = tmp_path / "fail.out"

    result = subprocess.run(
        [str(SCRIPT_PATH), str(cpp_file)],
        capture_output=True,
        text=True,
    )
    assert result.returncode == 42
    assert not expected_bin.exists()
