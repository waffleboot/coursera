#!bin/sh

g++ -pipe -O2 -std=c++14 bwt/bwt.cpp -o bwt/bwt -lm

bwt/bwt < bwt/sample_tests/sample1 | diff bwt/sample_tests/sample1.a -
bwt/bwt < bwt/sample_tests/sample2 | diff bwt/sample_tests/sample2.a -
bwt/bwt < bwt/sample_tests/sample3 | diff bwt/sample_tests/sample3.a -
