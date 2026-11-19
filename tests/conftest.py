import sys

# solution files are loaded straight from source, and two edits made in the same second with the
# same file size look identical to Python's .pyc cache check, which then serves the stale build
sys.dont_write_bytecode = True


def pytest_addoption(parser):
    parser.addoption(
        "--path",
        action="store",
        default=None,
        help="Path to a specific solution file or directory to test",
    )
