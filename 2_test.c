// Regression tests for findKthLargest duplicate-element crash (issue #4)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int findKthLargest(const int nums[], int count, int k);

static int cmp_desc(const void *a, const void *b)
{
    return *(const int *)b - *(const int *)a;
}

static int ref(const int nums[], int count, int k)
{
    int tmp[count];
    memcpy(tmp, nums, count * sizeof(int));
    qsort(tmp, count, sizeof(int), cmp_desc);
    return tmp[k - 1];
}

static int run_case(const char *label, const int nums[], int count, int k)
{
    int got = findKthLargest(nums, count, k);
    int want = ref(nums, count, k);
    if (got != want)
    {
        printf("FAIL %s: got %d, want %d\n", label, got, want);
        return 1;
    }
    printf("PASS %s: k=%d -> %d\n", label, k, got);
    return 0;
}

int main(void)
{
    int failures = 0;

    // Issue #4 crash case: {1,1} k=2
    { int a[] = {1, 1}; failures += run_case("{1,1} k=2", a, 2, 2); }

    // All identical elements
    { int a[] = {5, 5, 5, 5}; failures += run_case("{5,5,5,5} k=1", a, 4, 1); }
    { int a[] = {5, 5, 5, 5}; failures += run_case("{5,5,5,5} k=4", a, 4, 4); }

    // Many duplicates around pivot
    { int a[] = {3, 1, 3, 2, 3}; failures += run_case("{3,1,3,2,3} k=2", a, 5, 2); }
    { int a[] = {3, 1, 3, 2, 3}; failures += run_case("{3,1,3,2,3} k=3", a, 5, 3); }
    { int a[] = {3, 1, 3, 2, 3}; failures += run_case("{3,1,3,2,3} k=4", a, 5, 4); }

    // Single element
    { int a[] = {7}; failures += run_case("{7} k=1", a, 1, 1); }

    // Original test array k=3 (expect 76)
    { int a[] = {2,4,6,7,8,34,7,2,4,543,3,1,-56,3242,-9,45,2,3,4,65,7,43,76,14,4,14,76};
      failures += run_case("original k=3", a, 27, 3); }

    printf("\n%s\n", failures ? "SOME TESTS FAILED" : "All tests passed");
    return failures ? 1 : 0;
}
