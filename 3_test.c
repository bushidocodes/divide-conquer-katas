// Regression tests for findMissNo (kata 3).
// Exercises the missing term at the front, middle, and back of the sequence,
// plus the "nothing missing" path. The <3-element error path calls exit() and
// is therefore left to the program's own main() rather than tested here.
#include <stdio.h>

// Must match the layout declared in 3.c (separate translation unit, same ABI).
typedef struct
{
    bool found;
    int value;
} MaybeInt;

MaybeInt findMissNo(const int nums[], int startIdx, int endIdxExclusive);

static int run_case(const char *label, const int nums[], int count, bool wantFound, int wantValue)
{
    MaybeInt got = findMissNo(nums, 0, count);
    if (got.found != wantFound || (wantFound && got.value != wantValue))
    {
        printf("FAIL %s: got {found=%d, value=%d}, want {found=%d, value=%d}\n",
               label, got.found, got.value, wantFound, wantValue);
        return 1;
    }
    if (wantFound)
        printf("PASS %s: missing %d\n", label, got.value);
    else
        printf("PASS %s: nothing missing\n", label);
    return 0;
}

int main(void)
{
    int failures = 0;

    // Missing in front: 3 absent from an arithmetic sequence with c=2
    { int a[] = {1, 5, 7, 9, 11, 13, 15, 17, 19, 21}; failures += run_case("front", a, 10, true, 3); }

    // Missing in middle: 11 absent
    { int a[] = {1, 3, 5, 7, 9, 13, 15, 17, 19, 21}; failures += run_case("middle", a, 10, true, 11); }

    // Missing in back: 19 absent
    { int a[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 21}; failures += run_case("back", a, 10, true, 19); }

    // Nothing missing
    { int a[] = {1, 3, 5, 7, 9}; failures += run_case("complete-5", a, 5, false, 0); }

    // Smallest solvable sequence (3 elements), missing middle term
    { int a[] = {1, 3, 7}; failures += run_case("small-missing", a, 3, true, 5); }

    // Smallest solvable sequence, nothing missing
    { int a[] = {1, 3, 5}; failures += run_case("small-complete", a, 3, false, 0); }

    printf("\n%s\n", failures ? "SOME TESTS FAILED" : "All tests passed");
    return failures ? 1 : 0;
}
