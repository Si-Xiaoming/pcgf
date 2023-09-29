file(GLOB SOURCES "*.h" "*.cpp" "*.hpp" "*.ui" "*.qrc")

add_executable(app ${SOURCES})  #${SOURCES}

include_directories(${CMAKE_CURRENT_LIST_DIR})
