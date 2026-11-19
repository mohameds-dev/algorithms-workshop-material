import io
import sys


def move_disk(disk: int, from_pole: str, to_pole: str) -> None:
    print(f"move disk {disk} from {from_pole} to {to_pole}")


def hanoi(n: int, from_pole: str, to_pole: str, aux_pole: str) -> None:
    if n == 0:
        return

    hanoi(n - 1, from_pole, aux_pole, to_pole)
    move_disk(n, from_pole, to_pole)
    hanoi(n - 1, aux_pole, to_pole, from_pole)


def test_solution():
    old_stdout = sys.stdout
    sys.stdout = buffer = io.StringIO()
    try:
        hanoi(2, "A", "C", "B")
        lines = buffer.getvalue().strip().split("\n")
        assert lines == [
            "move disk 1 from A to B",
            "move disk 2 from A to C",
            "move disk 1 from B to C",
        ]
    finally:
        sys.stdout = old_stdout


if __name__ == "__main__":
    test_solution()  # Comment this out to run with custom inputs
