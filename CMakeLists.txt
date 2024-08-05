cmake_minimum_required (VERSION 3.5)
project (luatemplate)

# --- Lua ---

include(FindLua)
find_package(PkgConfig REQUIRED)
pkg_check_modules(LUA REQUIRED lua)

# --- Sources ---

file (GLOB LIB_SOURCES "src/*.c")

# --- Shared library ---

add_library (luatemplate_so SHARED ${LIB_SOURCES})

target_include_directories(luatemplate_so PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include ${LUA_INCLUDE_DIRS})
target_link_libraries(luatemplate_so PRIVATE ${LUA_LIBRARIES})

set_target_properties(luatemplate_so PROPERTIES OUTPUT_NAME "luatemplate_so" PREFIX "")

# --- Static library ---

add_library (luatemplate STATIC ${LIB_SOURCES})
target_include_directories(luatemplate PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/include ${LUA_INCLUDE_DIRS})
target_link_libraries(luatemplate PRIVATE ${LUA_LIBRARIES})

# --- Tests ---

file (GLOB TEST_SOURCES "test/*.c")
foreach (TEST_SOURCE ${TEST_SOURCES})
    get_filename_component (TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable (${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries (${TEST_NAME} luatemplate_so ${LUA_LIBRARIES})
    target_include_directories(${TEST_NAME} PRIVATE ${LUA_INCLUDE_DIRS})
endforeach ()

# --- Installation ---

set (install_directory "/usr/local/lib/lua/${LUA_VERSION_MAJOR}.${LUA_VERSION_MINOR}")

install (TARGETS luatemplate_so DESTINATION ${install_directory})
