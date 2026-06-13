/* Find the missing number from a given array. Your array will be in form [n, n+c, n+2c, …]. */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    bool found;
    int value;
} MaybeInt;

static MaybeInt found_value(int v) { return (MaybeInt){.found = true, .value = v}; }
static MaybeInt not_found(void) { return (MaybeInt){.found = false, .value = 0}; }

/* Return the first found result among up to three MaybeInt values. */
static MaybeInt first_found(MaybeInt a, MaybeInt b, MaybeInt c)
{
    if (a.found) return a;
    if (b.found) return b;
    return c;
}

static MaybeInt _findMissNo(const int nums[], int startIdx, int endIdxExclusive)
{
    if (endIdxExclusive - startIdx < 3) /* Error Condition - Can't find missing value with a sequence of only two */
    {
        fprintf(stderr, "Error: Cannot solve with less than three numbers!\n");
        exit(EXIT_FAILURE);
    }
    else if (endIdxExclusive - startIdx < 6) /* Base Case */
    {
        // The common difference is assumed to be the smallest difference because we are checking for missing terms
        // not extra terms

        int commonDifference = INT_MAX;
        for (int i = startIdx; i + 1 < endIdxExclusive; i++)
        {
            int diff = nums[i + 1] - nums[i];
            commonDifference = diff < commonDifference ? diff : commonDifference;
        }
        for (int i = startIdx + 1; i < endIdxExclusive; i++)
        {
            if (nums[i] > nums[startIdx] + (i - startIdx) * commonDifference)
            {
                return found_value(nums[startIdx] + (i - startIdx) * commonDifference);
            }
        }
        return not_found();
    }
    else /* Divide and Conquer */
    {
        int midpoint = startIdx + (endIdxExclusive - startIdx) / 2;
        // Partition, but be sure to check the middle band of three
        return first_found(
            _findMissNo(nums, startIdx, midpoint),
            _findMissNo(nums, midpoint - 1, midpoint + 2),
            _findMissNo(nums, midpoint, endIdxExclusive));
    }
}

MaybeInt findMissNo(const int nums[], int startIdx, int endIdxExclusive)
{
    return _findMissNo(nums, startIdx, endIdxExclusive);
}

#ifndef TEST_BUILD
int main(void)
{
    // int test[] = {1, 5, 7, 9, 11, 13, 15, 17, 19, 21}; // Test Missing in front
    int test[] = {1, 3, 5, 7, 9, 13, 15, 17, 19, 21}; // Test Missing in middle
    // int test[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 21}; // Test Missing in back
    // int test[] = {19, 21}; // Test error handling of too small unsorted array
    MaybeInt result = findMissNo(test, 0, sizeof(test) / sizeof(test[0]));
    if (!result.found)
    {
        printf("No terms are missing\n");
    }
    else
    {
        printf("Sequence is missing %d\n", result.value);
    }
    return 0;
}
#endif
