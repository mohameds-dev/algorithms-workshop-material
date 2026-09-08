import contextlib
import importlib.util
import io
import re
from pathlib import Path
from typing import Callable

import pytest
from hanoi.cases import HANOI_CASES, HanoiCase

hanoi_cases = pytest.mark.parametrize("case", HANOI_CASES, ids=lambda c: c.name)

MOVE_LINE = re.compile(r"^move disk (\d+) from (\S+) to (\S+)$")


def load_hanoi_function(solution_path: Path) -> Callable[[int, str, str, str], None]:
    if not solution_path.is_file():
        raise FileNotFoundError(f"no solution file at {solution_path}")

    # importlib, not a normal import: because "algorithm_implementation/towers-of-hanoi/" isn't a valid package name
    spec = importlib.util.spec_from_file_location(solution_path.stem, solution_path)
    if spec is None or spec.loader is None:
        raise ImportError(f"could not load a module spec for {solution_path}")

    solution_module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(solution_module)

    if not hasattr(solution_module, "hanoi"):
        raise AttributeError(f"{solution_path} does not define a top-level `hanoi(n, from_pole, to_pole, aux_pole)` function")

    return solution_module.hanoi


def collect_printed_moves(hanoi_fn: Callable[[int, str, str, str], None], case: HanoiCase) -> list[tuple[int, str, str]]:
    # the solution reports its moves by printing them, so the only way to inspect them is to capture stdout
    printed = io.StringIO()
    with contextlib.redirect_stdout(printed):
        hanoi_fn(case.disks, case.from_pole, case.to_pole, case.aux_pole)

    moves = []
    for line_number, line in enumerate(printed.getvalue().splitlines(), start=1):
        match = MOVE_LINE.match(line.strip())
        assert match, f"line {line_number} is not a move: {line!r}, expected 'move disk <disk> from <pole> to <pole>'"
        disk, from_pole, to_pole = match.groups()
        moves.append((int(disk), from_pole, to_pole))

    return moves


def assert_solves_puzzle(hanoi_fn: Callable[[int, str, str, str], None], case: HanoiCase) -> None:
    moves = collect_printed_moves(hanoi_fn, case)

    # each pole is a stack, bottom of the pile first, so the last element is the only movable disk
    poles = {case.from_pole: list(range(case.disks, 0, -1)), case.to_pole: [], case.aux_pole: []}

    for move_number, (disk, from_pole, to_pole) in enumerate(moves, start=1):
        where = f"move {move_number} of {len(moves)} ({disk}: {from_pole} to {to_pole})"

        assert from_pole in poles, f"{where}: no such pole {from_pole!r}"
        assert to_pole in poles, f"{where}: no such pole {to_pole!r}"
        assert poles[from_pole], f"{where}: pole {from_pole!r} is empty"
        assert poles[from_pole][-1] == disk, f"{where}: disk {disk} is not on top of {from_pole!r}, {poles[from_pole][-1]} is"
        assert not poles[to_pole] or poles[to_pole][-1] > disk, f"{where}: would land on smaller disk {poles[to_pole][-1]}"

        poles[to_pole].append(poles[from_pole].pop())

    expected_final_stack = list(range(case.disks, 0, -1))
    assert poles[case.to_pole] == expected_final_stack, f"pole {case.to_pole!r} ended as {poles[case.to_pole]!r}, expected {expected_final_stack!r}"
    assert not poles[case.from_pole], f"pole {case.from_pole!r} still holds {poles[case.from_pole]!r}"
    assert not poles[case.aux_pole], f"pole {case.aux_pole!r} still holds {poles[case.aux_pole]!r}"
    assert len(moves) == 2 ** case.disks - 1, f"took {len(moves)} moves, the minimum for {case.disks} disks is {2 ** case.disks - 1}"
