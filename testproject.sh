cmake --preset default;
cmake --build --preset default;
cd ./build/tests/ && ctest && cd -;