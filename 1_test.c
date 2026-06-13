// Regression tests for maxSubArray (kata 1).
// Verifies the divide-and-conquer result against a brute-force O(n^2) oracle.
#include <limits.h>
#include <stdio.h>

int maxSubArray(const int nums[], int startIdx, int endIdxInclusive);

// Brute-force maximum subarray sum over all contiguous subarrays.
static int ref(const int nums[], int count)
{
    int best = INT_MIN;
    for (int i = 0; i < count; i++)
    {
        int sum = 0;
        for (int j = i; j < count; j++)
        {
            sum += nums[j];
            if (sum > best)
                best = sum;
        }
    }
    return best;
}

static int run_case(const char *label, const int nums[], int count)
{
    int got = maxSubArray(nums, 0, count - 1);
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

    // Single element (positive and negative)
    { int a[] = {5}; failures += run_case("{5}", a, 1); }
    { int a[] = {-3}; failures += run_case("{-3}", a, 1); }

    // Two elements
    { int a[] = {-1, 4}; failures += run_case("{-1,4}", a, 2); }

    // All equal
    { int a[] = {2, 2, 2, 2}; failures += run_case("{2,2,2,2}", a, 4); }

    // All negative -> least-negative single element
    { int a[] = {-1, -2, -3}; failures += run_case("{-1,-2,-3}", a, 3); }
    { int a[] = {-5, -1, -8, -2}; failures += run_case("{-5,-1,-8,-2}", a, 4); }

    // All positive -> whole array
    { int a[] = {1, 2, 3, 4}; failures += run_case("{1,2,3,4}", a, 4); }

    // Classic mixed case (Kadane example) -> 6
    { int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4}; failures += run_case("kadane", a, 9); }

    // Original main() input
    { int a[] = {4, 1, 8, -12, 4, 32, -99, 12}; failures += run_case("original", a, 8); }

    printf("\n%s\n", failures ? "SOME TESTS FAILED" : "All tests passed");
    return failures ? 1 : 0;
}
