file(GLOB SOURCES "*.h" "*.cpp" "*.hpp" "*.ui" "*.qrc")

add_executable(app ${SOURCES})  #${SOURCES}

include_directories(${CMAKE_CURRENT_LIST_DIR})


#把当前的目录添加到搜索目录
#include_directories(${CMAKE_CURRENT_LIST_DIR})   

target_link_libraries(app PUBLIC pcgfLib ${PDAL_LIBRARIES} Qt5::Core OpenMP::OpenMP_CXX)