# algorithms-workshop-material

Material for an algorithms & data structures workshop at the University of Houston (UH).

## Structure

```
problems/
  <problem-slug>/
    README.md    # link to the problem, hints, summary, solution explanation, metadata
    solution.*   # the solution file

weekly_material/
  week1_day1.md  # one file per workshop day
  week1_day2.md
  ...
```

Each problem lives in its own directory under `problems/`, named with a slug (e.g. `two-sum/`).
Each workshop day gets a file under `weekly_material/`, named `week<N>_day<N>.md`.
