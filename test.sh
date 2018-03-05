mkdir -p build
cd build
cmake ..
make
echo ""
echo "Make Complete, running the code with testcase 1"
./programming-test-c < ../tests/input1.txt