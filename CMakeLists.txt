cmake_minimum_required(VERSION 3.7)
project(Project)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES source/main.cpp source/RandomGenerator/RandomGenerator.cpp include/RandomGenerator/RandomGenerator.h source/RandomGenerator/NormalRandomGenerator.cpp include/RandomGenerator/NormalRandomGenerator.h source/RandomGenerator/UniformRandomGenerator.cpp include/RandomGenerator/UniformRandomGenerator.h source/DataHandler/DataReader.cpp include/DataHandler/DataReader.h source/DataHandler/DataWriter.cpp include/DataHandler/DataWriter.h source/DataHandler/TextDataReader.cpp include/DataHandler/TextDataReader.h source/DataHandler/TextDataWriter.cpp include/DataHandler/TextDataWriter.h source/Serial/MatrixMultiplier.cpp include/Serial/MatrixMultiplier.h source/Pvm/SingleRowMultiplier.cpp include/Pvm/SingleRowMultiplier.h source/Serial/SerialMatrixMultiplier.cpp source/Pvm/single_row.cpp source/Pvm/SingleColumnMultiplier.cpp include/Pvm/SingleColumnMultiplier.h source/Pvm/single_column.cpp source/Pvm/MultipleRowMultiplier.cpp include/Pvm/MultipleRowMultiplier.h source/Pvm/multiple_rows.cpp)
add_executable(Project ${SOURCE_FILES})
target_link_libraries(Project libpvm3.a)
target_link_libraries(Project libgpvm3.a)