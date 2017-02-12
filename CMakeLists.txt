cmake_minimum_required(VERSION 3.1)
project(enum-utils CXX)

find_package(Boost REQUIRED)
add_library(boost INTERFACE IMPORTED)
set_property(TARGET boost PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR})
    
add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}>
    $<INSTALL_INTERFACE:${PROJECT_NAME}>
)
target_link_libraries(${PROJECT_NAME} INTERFACE boost)


add_executable(${PROJECT_NAME}-test tests/test.cpp)
target_link_libraries(${PROJECT_NAME}-test PUBLIC ${PROJECT_NAME})
set_property(TARGET ${PROJECT_NAME}-test PROPERTY CXX_STANDARD 11)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME} )
install(TARGETS ${PROJECT_NAME}-test RUNTIME DESTINATION bin)
install(FILES ${PROJECT_NAME}/enum.h DESTINATION ${PROJECT_NAME})
install(EXPORT ${PROJECT_NAME} DESTINATION cmake/${PROJECT_NAME})