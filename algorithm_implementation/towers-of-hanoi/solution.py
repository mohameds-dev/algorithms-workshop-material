def move_disk(disk: int, from_pole: str, to_pole: str) -> None:
    print(f"move disk {disk} from {from_pole} to {to_pole}")


def hanoi(n: int, from_pole: str, to_pole: str, aux_pole: str) -> None:
    if n == 0:
        return

    hanoi(n - 1, from_pole, aux_pole, to_pole)
    move_disk(n, from_pole, to_pole)
    hanoi(n - 1, aux_pole, to_pole, from_pole)


if __name__ == "__main__":
    hanoi(3, "A", "C", "B")
