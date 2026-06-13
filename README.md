This repo includes several coding challenges solved using Divide and Conquer techniques in C.

For those unfamiliar, Divide and Conquer is an algorithm design technique / strategy that seeks to divide a large problem into subproblems, solve those subproblems, and then merge the results.

A key idea is that the subproblems and the overarching problems are the same. They have the same inputs and outputs, and are thus commonly implemented via recursive functions. The difference is only in the scale of the problem.

The nifty thing about divide and conquer is that messy algorithms with bad Big O performance characteristics can perform acceptably well with tiny arrays.

## Building and testing

```sh
make all     # build the five standalone kata programs (1..5)
make test    # build and run the regression tests for every kata
make clean   # remove build artifacts
```

Each kata `N.c` has a companion `N_test.c` that links against it (the kata's
`main()` is compiled out via `-DTEST_BUILD`) and checks results against an
independent oracle. `make test` runs all five suites, and the same target runs
in CI on every push and pull request (see `.github/workflows/ci.yml`).
