// Find the contiguous sub array which has the largest sum and return its sum. This array may contain negative numbers.
// I understand a subarray to be a continuous sequence of elements from the source array

#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

// Must be used in the block where declared so array doesn't degrade to a pointer
#define length(n) (sizeof(n) / sizeof(n[0]))

static inline int max2(int a, int b) { return a > b ? a : b; }

static int _maxSubArray(const int nums[], int startIdx, int endIdxInclusive, bool isCheckingFromMidpoint)
{
    if (startIdx == endIdxInclusive) // One element
    {
        return nums[startIdx];
    }
    else if (startIdx + 1 == endIdxInclusive) // Two elements
    {
        return max2(nums[startIdx] + nums[endIdxInclusive],
                    max2(nums[startIdx], nums[endIdxInclusive]));
    }
    else if (isCheckingFromMidpoint) // Checking the middle of three or more
    {
        int midpoint = startIdx + (endIdxInclusive + 1 - startIdx) / 2;
        int maxLeft = INT_MIN;
        int maxRight = INT_MIN;
        int buffer = 0;

        // Find the best left
        for (int i = midpoint; i >= startIdx; i--)
        {
            buffer += nums[i];
            maxLeft = buffer > maxLeft ? buffer : maxLeft;
        }

        // Find the best right
        buffer = 0;
        for (int i = midpoint + 1; i <= endIdxInclusive; i++)
        {
            buffer += nums[i];
            maxRight = buffer > maxRight ? buffer : maxRight;
        }

        return maxLeft + (maxRight > 0 ? maxRight : 0);
    }
    else // Divide and Conquer of three or more
    {
        int midpoint = startIdx + (endIdxInclusive + 1 - startIdx) / 2;
        return max2(_maxSubArray(nums, startIdx, midpoint - 1, false),
                    max2(_maxSubArray(nums, startIdx, endIdxInclusive, true),
                         _maxSubArray(nums, midpoint, endIdxInclusive, false)));
    }
}

// I need to pass indices because the function loses state about the length of the array when passed as an arg
// I abstract my kludgey flag on the external API to be close to the original spirit of the problem
int maxSubArray(const int nums[], int startIdx, int endIdxInclusive)
{
    return _maxSubArray(nums, startIdx, endIdxInclusive, false);
}

int main(void)
{
    int test[] = {4, 1, 8, -12, 4, 32, -99, 12};
    // int test[] = {2, 3, 4, 5, 7};
    printf("The sum of the max sub array is %d\n", maxSubArray(test, 0, length(test) - 1));
    return 0;
}
