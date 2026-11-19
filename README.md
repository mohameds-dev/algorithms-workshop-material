# algorithms-workshop-material

Material for the algorithms & data structures workshop at the University of Houston (UH).

## Navigating this repo

- **New here?** Start with [`weekly_material/`](weekly_material/): one file per workshop day,
  in order, covering what we discussed that day.
- **Looking for a practice problem?** Check [`problem_solutions/`](problem_solutions/): each
  problem has its own folder with a README (link to the problem, hints, and a solution write-up)
  and a solution file.
- **Looking for a reference implementation of an algorithm itself** (not tied to one specific
  practice problem)? Check [`algorithm_implementation/`](algorithm_implementation/): laid out the
  same way, one folder per algorithm.

Full syllabus: https://uofh-my.sharepoint.com/:w:/g/personal/msabdelr_cougarnet_uh_edu/IQCVl-8XtdHvTro25geICGy7AVDzrhaCsOwLIWHBAvCUTB0?e=cENbUf

## Usage notes for instructors / repo users

[`tests/`](tests/) is a standalone, uv-managed Python project that checks the solutions in both
[`algorithm_implementation/`](algorithm_implementation/) and [`problem_solutions/`](problem_solutions/)
for correctness across Python and C++20. It requires [uv](https://docs.astral.sh/uv/); if you don't have it, install it using this guide:
https://docs.astral.sh/uv/getting-started/installation/.

To run all tests:

```bash
cd tests
uv sync            # first time only, sets up the environment
uv run pytest      # run every test across all problems and algorithms
```

To test a specific solution by file path:

```bash
# Using the CLI runner from repo root:
python tests/run_solution.py problem_solutions/shortest-routes-i/solution.py
python tests/run_solution.py problem_solutions/shortest-routes-i/solution.cpp

# Or using pytest from tests/:
uv run pytest -k shortest-routes-i
```

See [`tests/README.md`](tests/README.md) for full testing options and details.
