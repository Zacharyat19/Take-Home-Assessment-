cmake_minimum_required(VERSION 3.16)
project(TakeHomeDashboard)

# Qt requires C++17 or later
set(CMAKE_CXX_STANDARD 17)

# Enable Qt's auto-compilers for handling signals/slots and UI
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find the Qt 6 libraries you installed
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# Create the executable from your source file
add_executable(dashboard main.cpp)

# Link the Qt 6 libraries to your executable
target_link_libraries(dashboard PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)