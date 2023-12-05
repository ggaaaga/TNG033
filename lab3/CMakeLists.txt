cmake_minimum_required(VERSION 3.13.0...3.25.1)
project(TNG033-Lab-3 VERSION 1.0.0 DESCRIPTION "TNG033 Lab 3" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_warnings target)
target_compile_options(${target} PUBLIC 
$<$<CXX_COMPILER_ID:MSVC>:/W4 /permissive->
$<$<CXX_COMPILER_ID:AppleClang,Clang,GNU>:-Wall -Wextra>
)
endfunction()

add_executable(Exercise1 exerc1.cpp uppgift1_kort.txt out_uppgift1_kort.txt uppgift1.txt out_uppgift1.txt)
add_executable(Exercise2 exerc2.cpp uppgift2_kort.txt anagrams_uppgift2_kort.txt uppgift2.txt anagrams_uppgift2.txt)
add_executable(Exercise3 exerc3.cpp)
add_executable(Exercise3-given exerc3_given.cpp)

enable_warnings(Exercise1)
enable_warnings(Exercise2)
enable_warnings(Exercise3)
enable_warnings(Exercise3-given)