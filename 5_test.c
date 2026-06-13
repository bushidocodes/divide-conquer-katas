// Regression tests for assignPages (kata 5, book allocation).
// Expected values are derived by hand from the problem definition: minimize the
// maximum pages assigned to any student over contiguous allocations.
#include <stdio.h>

// Must match the layout declared in 5.c (separate translation unit, same ABI).
typedef struct testcase
{
    int numberOfBooks;
    int *pageCountOfBooks;
    int numberOfStudents;
} testcase;

long long assignPages(const testcase *tc);

static int run_case(const char *label, int pages[], int numberOfBooks,
                    int numberOfStudents, long long want)
{
    testcase tc = {
        .numberOfBooks = numberOfBooks,
        .pageCountOfBooks = pages,
        .numberOfStudents = numberOfStudents,
    };
    long long got = assignPages(&tc);
    if (got != want)
    {
        printf("FAIL %s: got %lld, want %lld\n", label, got, want);
        return 1;
    }
    printf("PASS %s: -> %lld\n", label, got);
    return 0;
}

int main(void)
{
    int failures = 0;

    // Canonical example from the problem statement: {12,34,67,90}, 2 students -> 113
    { int p[] = {12, 34, 67, 90}; failures += run_case("example", p, 4, 2, 113); }

    // Single student gets every book -> total page count
    { int p[] = {10, 20, 30}; failures += run_case("single-student", p, 3, 1, 60); }

    // Single book, single student
    { int p[] = {42}; failures += run_case("single-book", p, 1, 1, 42); }

    // More students than books -> impossible
    { int p[] = {5, 10}; failures += run_case("too-many-students", p, 2, 3, -1); }

    // Students == books -> each gets one, answer is the heaviest single book
    { int p[] = {5, 10, 15}; failures += run_case("one-each", p, 3, 3, 15); }

    // Two students, optimal split {10,20,30}|{40} -> 60
    { int p[] = {10, 20, 30, 40}; failures += run_case("split", p, 4, 2, 60); }

    printf("\n%s\n", failures ? "SOME TESTS FAILED" : "All tests passed");
    return failures ? 1 : 0;
}
