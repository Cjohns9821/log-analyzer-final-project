Log Analyzer Final Project
Description
This project compares a baseline log analyzer with an optimized implementation.

The baseline version uses a linked list and linear searches to track IP address occurrences within a log file. The optimized version uses a hash table with separate chaining to improve lookup performance and reduce processing time.

The goal of the project is to demonstrate how a more efficient data structure can improve program performance while producing identical results.

Compile Instructions
Compile the baseline implementation:

gcc -Wall baseline.c -o baseline
Compile the optimized implementation:

gcc -Wall optimized.c -o optimized
Running the Programs
Run the baseline version:

./baseline large.log
Run the optimized version:

./optimized large.log
Running Benchmarks
Measure execution time for the baseline version:

time ./baseline large.log
Measure execution time for the optimized version:

time ./optimized large.log
Compare the reported execution times and calculate the speedup ratio:

Speedup = Baseline Time / Optimized Time
Expected Output Format
Execution Time: 0.005633 seconds

IP Address Counts:
192.168.1.0 -> 400
192.168.1.1 -> 400
192.168.1.2 -> 400
...
The optimized implementation should produce the same IP address counts as the baseline implementation while executing faster.

Optimization Summary
The baseline implementation uses a linked list, requiring a linear search to find existing IP addresses. The optimized implementation uses a hash table, reducing average lookup complexity from O(n) to O(1). Benchmark testing showed approximately a 1.83× performance improvement while preserving correctness.
