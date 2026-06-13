// Regression tests for findRotationNo (kata 4).
// The rotation count equals the index of the minimum element, so the result is
// checked against a linear-scan oracle. Inputs use distinct values to keep the
// minimum's index unambiguous.
#include <stdio.h>

int findRotationNo(const int nums[], int startIdx, int endIdxExclusive);

// Index of the minimum element (first occurrence).
static int ref(const int nums[], int count)
{
    int mi = 0;
    for (int i = 1; i < count; i++)
        if (nums[i] < nums[mi])
            mi = i;
    return mi;
}

static int run_case(const char *label, const int nums[], int count)
{
    int got = findRotationNo(nums, 0, count);
    int want = ref(nums, count);
    if (got != want)
    {
        printf("FAIL %s: got %d, want %d\n", label, got, want);
        return 1;
    }
    printf("PASS %s: -> %d\n", label, got);
    return 0;
}

int main(void)
{
    int failures = 0;

    // Single element -> 0 rotations
    { int a[] = {5}; failures += run_case("{5}", a, 1); }

    // Two elements, both orderings
    { int a[] = {1, 2}; failures += run_case("{1,2}", a, 2); }
    { int a[] = {2, 1}; failures += run_case("{2,1}", a, 2); }

    // Zero rotations (already sorted)
    { int a[] = {1, 2, 3, 4, 6, 8}; failures += run_case("sorted", a, 6); }

    // Rotation in the middle
    { int a[] = {4, 6, 8, 1, 2, 3}; failures += run_case("{4,6,8,1,2,3}", a, 6); }
    { int a[] = {6, 8, 1, 2, 3, 4}; failures += run_case("{6,8,1,2,3,4}", a, 6); }

    // Minimum at the final position
    { int a[] = {2, 3, 4, 6, 8, 1}; failures += run_case("min-at-end", a, 6); }

    // Odd length
    { int a[] = {8, 1, 2, 3, 4}; failures += run_case("odd-len", a, 5); }

    printf("\n%s\n", failures ? "SOME TESTS FAILED" : "All tests passed");
    return failures ? 1 : 0;
}
