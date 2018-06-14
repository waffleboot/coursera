#!bin/sh

g++ -pipe -O2 -std=c++14 bwt/bwt.cpp -o bwt/bwt -lm

cat << EOF | bwt/bwt
GAGAGAT\$
EOF

bwt/bwt < bwt/sample_tests/sample1 | diff -a bwt/sample_tests/sample1.a -
bwt/bwt < bwt/sample_tests/sample2 | diff -a bwt/sample_tests/sample2.a -
bwt/bwt < bwt/sample_tests/sample3 | diff -a bwt/sample_tests/sample3.a -
time bwt/bwt < bwt/sample_tests/sample4 > /dev/null

g++ -pipe -O2 -std=c++14 bwtinverse/bwtinverse.cpp -o bwtinverse/bwtinverse -lm

cat << EOF | bwtinverse/bwtinverse
TGGG\$AAA
EOF

bwtinverse/bwtinverse < bwtinverse/sample_tests/sample1 | diff -a bwtinverse/sample_tests/sample1.a -
bwtinverse/bwtinverse < bwtinverse/sample_tests/sample2 | diff -a bwtinverse/sample_tests/sample2.a -
time bwtinverse/bwtinverse < bwtinverse/sample_tests/sample3 > /dev/null

g++ -pipe -O2 -std=c++14 bwmatching/bwmatching.cpp -o bwmatching/bwmatching -lm

cat << EOF | bwmatching/bwmatching
TGGG\$AAA
1
AGA
EOF

bwmatching/bwmatching < bwmatching/sample_tests/sample1 | diff -a bwmatching/sample_tests/sample1.a -
bwmatching/bwmatching < bwmatching/sample_tests/sample2 | diff -a bwmatching/sample_tests/sample2.a -
bwmatching/bwmatching < bwmatching/sample_tests/sample3 | diff -a bwmatching/sample_tests/sample3.a -
time bwmatching/bwmatching < bwmatching/sample_tests/sample4 > /dev/null

