import sys

# solution files are loaded straight from source, and two edits made in the same second with the
# same file size look identical to Python's .pyc cache check, which then serves the stale build
sys.dont_write_bytecode = True
