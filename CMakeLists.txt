cmake_minimum_required(VERSION 3.1.0)

project(TdTest)
find_package(Td 1.3.0 REQUIRED)
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Find the QtWidgets library
find_package(Qt5Core CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(TdTest_SRCS
	    cmdthread.cpp
	    loger.cpp
	    tdclient.cpp
	    telegramthread.cpp
	    utility.h
	    td_example.cpp
	          logout.cpp
		    )
 # Tell CMake to create the helloworld executable
add_executable(TdTest  ${TdTest_SRCS})
# Use the Widgets module from Qt 5
target_link_libraries(TdTest Qt5::Core Td::TdStatic)
set_property(TARGET TdTest PROPERTY CXX_STANDARD 14)
