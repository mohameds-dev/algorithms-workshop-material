from dataclasses import dataclass


@dataclass(frozen=True)
class HanoiCase:
    name: str
    disks: int
    from_pole: str
    to_pole: str
    aux_pole: str


HANOI_CASES: list[HanoiCase] = [
    HanoiCase("no_disks", 0, "A", "C", "B"),
    HanoiCase("one_disk", 1, "A", "C", "B"),
    HanoiCase("two_disks", 2, "A", "C", "B"),
    HanoiCase("three_disks", 3, "A", "C", "B"),
    HanoiCase("four_disks", 4, "A", "C", "B"),
    HanoiCase("five_disks", 5, "A", "C", "B"),
    HanoiCase("ten_disks", 10, "A", "C", "B"),
    HanoiCase("destination_is_the_middle_pole", 4, "A", "B", "C"),
    HanoiCase("source_is_the_last_pole", 4, "C", "A", "B"),
    HanoiCase("renamed_poles", 6, "left", "right", "spare"),
]
