// Find the kth largest number in an unsorted array.
// int findKthLargest(int[] nums, int k){}

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static int _findKthLargest(const int nums[], int count, int k)
{
    int pivotIdx = rand() % count;
    int pivot = nums[pivotIdx];

    // Three-way partition: left (<pivot), right (>pivot); equal elements are counted but not stored
    int *left = malloc((size_t)count * sizeof(int));
    int *right = malloc((size_t)count * sizeof(int));
    if (left == NULL || right == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        free(left);
        free(right);
        exit(EXIT_FAILURE);
    }
    int leftLength = 0;
    int rightLength = 0;
    int equalCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (nums[i] < pivot)
        {
            left[leftLength++] = nums[i];
        }
        else if (nums[i] > pivot)
        {
            right[rightLength++] = nums[i];
        }
        else
        {
            equalCount++;
        }
    }

    int result;
    if (rightLength >= k)
    {
        free(left);
        result = _findKthLargest(right, rightLength, k);
        free(right);
    }
    else if (rightLength + equalCount >= k)
    {
        // k falls within the equal-to-pivot band
        free(left);
        free(right);
        result = pivot;
    }
    else
    {
        free(right);
        result = _findKthLargest(left, leftLength, k - rightLength - equalCount);
        free(left);
    }
    return result;
}

int findKthLargest(const int nums[], int count, int k)
{
    srand(time(NULL)); // Initialization, should only be called once.
    return _findKthLargest(nums, count, k);
}

#ifndef TEST_BUILD
int main(void)
{
    int test[] = {2, 4, 6, 7, 8, 34, 7, 2, 4, 543, 3, 1, -56, 3242, -9, 45, 2, 3, 4, 65, 7, 43, 76, 14, 4, 14, 76};
    int k = 3;
    printf("Term %d is %d\n", k, findKthLargest(test, sizeof(test) / sizeof(test[0]), k));
    return 0;
}
#endif
