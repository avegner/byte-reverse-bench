# Byte Reverse Bench
This is a benchmark comparing different methods of bits reverse in byte in C.

# Methods
There are several implemented methods to reverse bits:
* simple loop over all bits
* bitfields and union
* swapping
* small (reduced) lookup table
* big (full) lookup table
* magic with constants
* clang's builtin method

# How to Run
Benchmark measures run times of implementations built by GCC and Clang for every optimization level (Os, O0-O3).

To run:
* install GCC and Clang
* run `run.sh` script
