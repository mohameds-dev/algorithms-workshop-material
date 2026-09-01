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

[`tests/`](tests/) is a standalone, uv-managed Python project that checks the solutions in
[`algorithm_implementation/`](algorithm_implementation/) for correctness. To run it:

```
cd tests
uv sync            # first time only, sets up the environment
uv run pytest      # run every test
```

Useful variations:

```
uv run pytest -k merge_sort      # just one algorithm
uv run pytest -k reverse_sorted  # just one test case, across every algorithm
uv run pytest -v                 # list every test that ran, by name
```

See [`tests/README.md`](tests/README.md) for how to add a test case or register a new
algorithm.
