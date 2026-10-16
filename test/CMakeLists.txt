set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS}")

set(SOURCE_FILES TimeSquareTestMain.cpp)
add_executable(Test ${SOURCE_FILES})
target_link_libraries(Test libutilities libdelynoi)

set(SOURCE_FILES LShapeTestMain.cpp)
add_executable(LShape ${SOURCE_FILES})
target_link_libraries(LShape libutilities libdelynoi)

set(SOURCE_FILES SwissCheeseTestMain.cpp)
add_executable(Swiss ${SOURCE_FILES})
target_link_libraries(Swiss libutilities libdelynoi)

set(SOURCE_FILES SimpleSquareTestMain.cpp)
add_executable(SimpleSquare ${SOURCE_FILES})
target_link_libraries(SimpleSquare libutilities libdelynoi)