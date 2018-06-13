#!bin/sh

g++ -pipe -O2 -std=c++14 bwt/bwt.cpp -o bwt/bwt -lm

cat << EOF | bwt/bwt
ATGC$
EOF

bwt/bwt < bwt/sample_tests/sample1 | diff -a bwt/sample_tests/sample1.a -
bwt/bwt < bwt/sample_tests/sample2 | diff -a bwt/sample_tests/sample2.a -
bwt/bwt < bwt/sample_tests/sample3 | diff -a bwt/sample_tests/sample3.a -
time bwt/bwt < bwt/sample_tests/sample4 > /dev/null

g++ -pipe -O2 -std=c++14 bwtinverse/bwtinverse.cpp -o bwtinverse/bwtinverse -lm 2>/dev/null

cat << EOF | bwtinverse/bwtinverse
C\$GTA
EOF

bwtinverse/bwtinverse < bwtinverse/sample_tests/sample1 | diff -a bwtinverse/sample_tests/sample1.a -
bwtinverse/bwtinverse < bwtinverse/sample_tests/sample2 | diff -a bwtinverse/sample_tests/sample2.a -
time bwtinverse/bwtinverse < bwtinverse/sample_tests/sample3 > /dev/null
