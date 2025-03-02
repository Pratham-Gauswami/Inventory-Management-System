cmake_minimum_required(VERSION 3.1.0)
project(AutomatedInventoryMSystem)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17) # Enable Qt's automoc, autorcc, and autouic
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find required packages (Qt6 and SQLite3)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
find_package(SQLite3 REQUIRED)  # Add this line to find SQLite3

# Add the include/ directory to the include path
include_directories(${CMAKE_SOURCE_DIR}/include)

# Define a variable for the source files
set(SOURCES
    src/main.cpp
    src/inventory.cpp
    src/addProduct.cpp
    src/DatabaseManager.cpp
)

# Add executable using the SOURCES variable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Widgets
    SQLite::SQLite3  # Add this line to link SQLite3
)