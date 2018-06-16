#!bin/sh

g++ -pipe -O2 -std=c++14 kmp/kmp.cpp -o kmp/kmp -lm

#cat << EOF | kmp/kmp
#ATA
#ATATA
#EOF

kmp/kmp < kmp/sample_tests/sample1 | diff -w -a kmp/sample_tests/sample1.a -
kmp/kmp < kmp/sample_tests/sample2 | diff -w -a kmp/sample_tests/sample2.a -
kmp/kmp < kmp/sample_tests/sample3 | diff -w -a kmp/sample_tests/sample3.a -

