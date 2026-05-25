/* Find the missing number from a given array. Your array will be in form [n, n+c, n+2c, …]. */
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static inline int max2(int a, int b) { return a > b ? a : b; }

static int _findMissNo(const int nums[], int startIdx, int endIdxExclusive)
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
                return nums[startIdx] + (i - startIdx) * commonDifference;
            }
        }
        return INT_MIN;
    }
    else /* Divide and Conquer */
    {
        int midpoint = startIdx + (endIdxExclusive - startIdx) / 2;
        // Partition, but be sure to check the middle band of three
        return max2(_findMissNo(nums, startIdx, midpoint),
                    max2(_findMissNo(nums, midpoint - 1, midpoint + 2),
                         _findMissNo(nums, midpoint, endIdxExclusive)));
    }
}

int findMissNo(const int nums[], int startIdx, int endIdxExclusive)
{
    return _findMissNo(nums, startIdx, endIdxExclusive);
}

int main(void)
{
    // int test[] = {1, 5, 7, 9, 11, 13, 15, 17, 19, 21}; // Test Missing in front
    int test[] = {1, 3, 5, 7, 9, 13, 15, 17, 19, 21}; // Test Missing in middle
    // int test[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 21}; // Test Missing in back
    // int test[] = {19, 21}; // Test error handling of too small unsorted array
    int missingTerm = findMissNo(test, 0, sizeof(test) / sizeof(test[0]));
    if (missingTerm == INT_MIN)
    {
        printf("No terms are missing\n");
    }
    else
    {
        printf("Sequence is missing %d\n", missingTerm);
    }
    return 0;
}
