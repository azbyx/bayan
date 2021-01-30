cmake_minimum_required(VERSION 3.2)

set(NAME_EXECUTABLE "bayan")
set(NAME_TEST "bayan_test")

set(PATHES "headrs/" "interfaces/")
set(SRC_PATH "src/")

if(NOT DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(ENV{TRAVIS_BUILD_NUMBER} 1)
endif()

project(${NAME_EXECUTABLE} VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER}  LANGUAGES CXX)

set(Boost_USE_DEBUG_RUNTIME OFF)
#set(Boost_DEBUG ON)

find_package(Boost COMPONENTS program_options unit_test_framework REQUIRED)

add_executable(${NAME_EXECUTABLE} ${SRC_PATH}main.cpp)

set(LIBRARIES parser finder handler options crc32hash md5hash)

add_library(parser    ${SRC_PATH}parser.cpp)
add_library(finder    ${SRC_PATH}finder.cpp)
add_library(handler   ${SRC_PATH}handler.cpp)
add_library(options   ${SRC_PATH}options.cpp)
add_library(crc32hash ${SRC_PATH}crc32hash.cpp)
add_library(md5hash   ${SRC_PATH}md5hash.cpp)

target_include_directories(parser    PUBLIC ${PATHES} ${Boost_INCLUDE_DIR})
target_include_directories(finder    PUBLIC ${PATHES} ${Boost_INCLUDE_DIR})
target_include_directories(handler   PUBLIC ${PATHES} ${Boost_INCLUDE_DIR})
target_include_directories(options   PRIVATE ${PATHES} ${Boost_INCLUDE_DIR})
target_include_directories(crc32hash PRIVATE ${PATHES} ${Boost_INCLUDE_DIR})
target_include_directories(md5hash   PRIVATE ${PATHES} ${Boost_INCLUDE_DIR})

target_link_libraries(parser PUBLIC ${Boost_LIBRARIES})
target_link_libraries(${NAME_EXECUTABLE} PRIVATE ${LIBRARIES} ${Boost_LIBRARIES})

target_compile_features(parser    PUBLIC cxx_std_17)
target_compile_features(finder    PUBLIC cxx_std_17)
target_compile_features(handler   PUBLIC cxx_std_17)
target_compile_features(options   PUBLIC cxx_std_17)
target_compile_features(crc32hash PUBLIC cxx_std_17)
target_compile_features(md5hash   PUBLIC cxx_std_17)

set_target_properties(${NAME_EXECUTABLE} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

add_executable(${NAME_TEST} ${SRC_PATH}test.cpp)

set_target_properties(${NAME_TEST} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    #COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR} ${PATHES}
)

target_link_libraries(${NAME_TEST} PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} ${LIBRARIES})

if (MSVC)
    target_compile_options(${NAME_EXECUTABLE} PRIVATE /W4)
    target_compile_options(${NAME_TEST} PRIVATE /W4)
else()
    target_compile_options(${NAME_EXECUTABLE} PRIVATE -Wall -Wextra -pedantic -Werror)
    target_compile_options(${NAME_TEST} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

install(TARGETS ${NAME_EXECUTABLE} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT azbyx@inbox.ru)

include(CPack)

enable_testing()

add_test(NAME ${NAME_TEST} COMMAND ${NAME_TEST})
