cmake_minimum_required(VERSION 3.7)
project(Project)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp util/RandomGenerator.cpp util/RandomGenerator.h util/NormalRandomGenerator.cpp util/NormalRandomGenerator.h util/UniformRandomGenerator.cpp util/UniformRandomGenerator.h util/DataReader.cpp util/DataReader.h util/DataWriter.cpp util/DataWriter.h util/TextDataReader.cpp util/TextDataReader.h util/TextDataWriter.cpp util/TextDataWriter.h MatrixMultiplier.cpp MatrixMultiplier.h pvm/SingleRowMultiplier.cpp pvm/SingleRowMultiplier.h serial/SerialMatrixMultiplier.cpp serial/SerialMatrixMultiplier.h pvm/single_row.cpp pvm/SingleColumnMultiplier.cpp pvm/SingleColumnMultiplier.h pvm/single_column.cpp pvm/MultipleRowMultiplier.cpp pvm/MultipleRowMultiplier.h pvm/multiple_rows.cpp)
add_executable(Project ${SOURCE_FILES})
target_link_libraries(Project libpvm3.a)
target_link_libraries(Project libgpvm3.a)