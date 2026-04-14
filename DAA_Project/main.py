"""Menu-driven CLI for DAA mini-project algorithms."""

from heap_range import find_smallest_range
from line_intersection import count_intersections
from msis_dp import maximum_sum_increasing_subsequence
from utils import (
    input_k_sorted_arrays,
    input_line_segments,
    parse_int_list,
    sample_data_line_intersections,
    sample_data_msis,
    sample_data_smallest_range,
)


def run_smallest_range() -> None:
    print("\n--- Smallest Range from k Sorted Arrays (Heap) ---")
    use_sample = input("Use sample input? (y/n): ").strip().lower() == "y"

    if use_sample:
        arrays = sample_data_smallest_range()
        print("Sample arrays:", arrays)
    else:
        arrays = input_k_sorted_arrays()

    start, end = find_smallest_range(arrays, verbose=True)
    print(f"Smallest range including at least one element from each array: [{start}, {end}]")


def run_line_intersection() -> None:
    print("\n--- Line Segment Intersection Count (Sweep Line) ---")
    use_sample = input("Use sample input? (y/n): ").strip().lower() == "y"

    if use_sample:
        horizontal, vertical = sample_data_line_intersections()
        print("Sample horizontal segments:", horizontal)
        print("Sample vertical segments:", vertical)
    else:
        horizontal, vertical = input_line_segments()

    count = count_intersections(horizontal, vertical, verbose=True)
    print(f"Total intersections: {count}")


def run_msis() -> None:
    print("\n--- Maximum Sum Increasing Subsequence (Dynamic Programming) ---")
    use_sample = input("Use sample input? (y/n): ").strip().lower() == "y"

    if use_sample:
        arr = sample_data_msis()
        print("Sample array:", arr)
    else:
        arr = parse_int_list("Enter array elements (space-separated): ")

    max_sum, subsequence = maximum_sum_increasing_subsequence(arr)
    print("Maximum sum:", max_sum)
    print("MSIS subsequence:", subsequence)


def print_menu() -> None:
    print("\n================ DAA Mini Project ================")
    print("1. Smallest Range (Heap)")
    print("2. Line Intersection (Sweep Line)")
    print("3. Maximum Sum Increasing Subsequence (DP)")
    print("4. Exit")


def main() -> None:
    while True:
        print_menu()
        choice = input("Enter your choice (1-4): ").strip()

        if choice == "1":
            run_smallest_range()
        elif choice == "2":
            run_line_intersection()
        elif choice == "3":
            run_msis()
        elif choice == "4":
            print("Exiting. Thank you!")
            break
        else:
            print("Invalid choice. Please enter a number between 1 and 4.")


if __name__ == "__main__":
    main()
