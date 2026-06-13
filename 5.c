/*

Note: I've rephrased the problem statement because I found the existing description to be super confusing.

You are given N number of books, each with a specific number of pages.
Your goal is to allocate these books to M students in a manner that minimizes the maximum number of pages assigned to any single student

For mysterious reasons, the book assignments need to be contiguous subarrays of the array formed by the provided list of page counts.

Each book will be assigned to exactly one student.
Each student has to be allocated at least one book.

Return the minimized number of pages assigned to the student

Note: Return -1 if a valid assignment is not possible, and allotment should be in contiguous order (see explanation for better understanding).

Input:
The first line contains 'T' denoting the number of testcases. Then follows description of T

testcases:
Each case begins with a single positive integer N denoting the number of books.
The second line contains N space separated positive integers denoting the pages of each book.
And the third line contains another integer M, denoting the number of students.

Output:
For each test case, output a single line containing the highest number of pages assigned to a student in the optimal assignment.

Constraints:
1<= T <= 100
1 <= N <= 106
1 <= A [ i ] <= 106
1 <= M <= 106

Example:
Input:
1 (number of test cases)
4 (number of books in test case)
12 34 67 90 (pages of each book in test case)
2 (number of students)

Output:
113

Explanation: Allocation can be done in following ways:
{12} and {34, 67, 90} Maximum Pages = 191
{12, 34} and {67, 90} Maximum Pages = 157
{12, 34, 67} and {90} Maximum Pages = 113
Therefore, the minimum of these cases is 113, which is selected as output.



NOTE TO GRADER:
To run this program:
gcc 5.c && cat 5.txt | ./a.out

I'm a bit confused if binary search constitutes divide and conquer. Since we are tossing half the results, we are dividing, but we don't need to merge. I could refactor to make the binary search portion to use leftBounds and rightBounds as arguments to a recursive function, but that doesn't seem to provide any additional value in my opinion.

*/
#include <stdio.h>
#include <stdlib.h>

typedef struct testcase
{
    int numberOfBooks;
    int *pageCountOfBooks;
    int numberOfStudents;
} testcase;

[[nodiscard]] static bool canBeAssigned(const testcase *tc, long long candidate_min)
{
    int studentsNeeded = 1;
    long long buffer = 0;
    for (int i = 0; i < tc->numberOfBooks; i++)
    {
        if (tc->pageCountOfBooks[i] > candidate_min)
            return false;
        if (buffer + tc->pageCountOfBooks[i] <= candidate_min)
        {
            buffer += tc->pageCountOfBooks[i];
        }
        else
        {
            studentsNeeded++;
            buffer = tc->pageCountOfBooks[i];
            if (studentsNeeded > tc->numberOfStudents)
                return false;
        }
    }
    return true;
}

long long assignPages(const testcase *tc)
{
    // Each student must be assigned at least one book, so error condition if students > books
    if (tc->numberOfStudents > tc->numberOfBooks)
        return -1;

    // Accumulate sum of page count of all books; track max for the binary search lower bound
    long long totalPageCount = 0;
    long long maxPageCount = 0;
    for (int i = 0; i < tc->numberOfBooks; i++)
    {
        totalPageCount += tc->pageCountOfBooks[i];
        if (tc->pageCountOfBooks[i] > maxPageCount)
            maxPageCount = tc->pageCountOfBooks[i];
    }

    // Binary search over the range of possible minimums, testing feasibility with canBeAssigned.
    // Lower bound is max(pages): any valid allocation must accommodate the heaviest single book.
    long long leftBounds = maxPageCount;
    long long rightBounds = totalPageCount;

    // We know we have the optimal solution when the bounds cross each other
    while (leftBounds <= rightBounds)
    {
        long long midpoint = leftBounds + (rightBounds - leftBounds) / 2;
        if (canBeAssigned(tc, midpoint))
            rightBounds = midpoint - 1;
        else
            leftBounds = midpoint + 1;
    }
    return leftBounds;
}

#ifndef TEST_BUILD
int main(void)
{
    int numberOfTestCases;
    if (scanf("%d", &numberOfTestCases) != 1 || numberOfTestCases <= 0 || numberOfTestCases > 100)
    {
        fprintf(stderr, "Error: invalid number of test cases\n");
        return EXIT_FAILURE;
    }
    testcase **testcases = malloc((size_t)numberOfTestCases * sizeof(testcase *));
    if (testcases == NULL)
    {
        fprintf(stderr, "Error: malloc failed\n");
        return EXIT_FAILURE;
    }
    for (int i = 0; i < numberOfTestCases; i++)
    {
        testcases[i] = malloc(sizeof(testcase));
        if (testcases[i] == NULL)
        {
            fprintf(stderr, "Error: malloc failed\n");
            exit(EXIT_FAILURE);
        }
        testcases[i]->pageCountOfBooks = NULL;
        if (scanf("%d", &testcases[i]->numberOfBooks) != 1)
        {
            fprintf(stderr, "Error: failed to read numberOfBooks\n");
            exit(EXIT_FAILURE);
        }
        if (testcases[i]->numberOfBooks <= 0 || testcases[i]->numberOfBooks > 1000000)
        {
            fprintf(stderr, "Error: numberOfBooks (%d) out of range [1, 1000000]\n",
                    testcases[i]->numberOfBooks);
            exit(EXIT_FAILURE);
        }
        testcases[i]->pageCountOfBooks = malloc((size_t)testcases[i]->numberOfBooks * sizeof(int));
        if (testcases[i]->pageCountOfBooks == NULL)
        {
            fprintf(stderr, "Error: malloc failed\n");
            exit(EXIT_FAILURE);
        }
        for (int j = 0; j < testcases[i]->numberOfBooks; j++)
        {
            if (scanf("%d", &testcases[i]->pageCountOfBooks[j]) != 1)
            {
                fprintf(stderr, "Error: failed to read page count\n");
                exit(EXIT_FAILURE);
            }
        }
        if (scanf("%d", &testcases[i]->numberOfStudents) != 1 || testcases[i]->numberOfStudents <= 0)
        {
            fprintf(stderr, "Error: invalid numberOfStudents\n");
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < numberOfTestCases; i++)
        printf("%lld\n", assignPages(testcases[i]));
    for (int i = 0; i < numberOfTestCases; i++)
    {
        free(testcases[i]->pageCountOfBooks);
        free(testcases[i]);
    }
    free(testcases);
    return 0;
}
#endif
