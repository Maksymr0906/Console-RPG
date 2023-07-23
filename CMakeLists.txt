cmake_minimum_required(VERSION 3.12)
project(ConsoleRPG)

# Add the "header" directory to include directories
include_directories(header)

# Collect all the .cpp files from the "source" directory
file(GLOB SOURCES "source/*.cpp")

# Set the path to the txt files in a variable
set(TXT_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# List of text files to copy
set(TXT_FILES Armor.txt EmptyEventMessages.txt Enemies.txt FoundItemMessages.txt Products.txt Puzzle.txt Weapons.txt)

# Loop through the list and copy each txt file
foreach(TXT_FILE ${TXT_FILES})
    # Copy the file to the Debug folder in the build directory
    file(COPY ${TXT_FILES_DIR}/${TXT_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/Debug)
endforeach()

# Add an executable and link the sources
add_executable(ConsoleRPG ${SOURCES})