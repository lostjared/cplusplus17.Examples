cmake_minimum_required(VERSION 3.16)

project(cplusplus17_examples LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -pedantic
    )
elseif(MSVC)
    add_compile_options(/W4 /permissive-)
endif()

include(CheckIncludeFileCXX)
include(CheckCXXSourceCompiles)

set(CPP17_REQUIRED_HEADERS
    any
    charconv
    filesystem
    optional
    shared_mutex
    string_view
    variant
)

foreach(header IN LISTS CPP17_REQUIRED_HEADERS)
    string(TOUPPER "${header}" header_upper)
    string(REPLACE "/" "_" header_upper "${header_upper}")
    set(var_name "HAS_CXX17_${header_upper}")
    check_include_file_cxx("${header}" ${var_name})
    if(NOT ${var_name})
        message(FATAL_ERROR
            "C++17 header <${header}> not found.\n"
            "Your compiler or standard library is too old to build these examples.")
    endif()
endforeach()

check_cxx_source_compiles([=[
#include <any>
#include <optional>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>

template <typename... T>
constexpr auto fold_sum(T... values) {
    return (values + ...);
}

int main() {
    if constexpr (std::is_same_v<int, int>) {
        auto [a, b] = std::make_pair(1, 2);
        (void)a;
        (void)b;
    }

    std::optional<int> o = 7;
    std::variant<int, double> v = 2.5;
    std::any x = 42;
    std::string_view s = "c++17";

    (void)o;
    (void)std::get<double>(v);
    (void)std::any_cast<int>(x);
    (void)s;
    static_assert(fold_sum(1, 2, 3) == 6, "fold expressions must work");
    return 0;
}
]=] CXX17_FEATURES_WORK)

if(NOT CXX17_FEATURES_WORK)
    message(FATAL_ERROR
        "C++17 feature smoke-test failed.\n"
        "Your compiler claims C++17 support but key features do not compile.")
endif()

message(STATUS "C++17 standard library and language feature checks passed")

find_package(Threads REQUIRED)
find_package(SDL2 QUIET)
find_package(SDL2_ttf QUIET)
find_package(OpenCV QUIET)
find_package(TBB QUIET)
find_path(ACIDCAM_INCLUDE_DIR
    NAMES acidcam/ac.h ac.h
    PATH_SUFFIXES include
)
option(BUILD_ACIDCAM_EXAMPLES "Build examples that depend on AcidCam libraries" OFF)
find_package(Qt6 COMPONENTS Core Gui Widgets QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Gui Widgets QUIET)
endif()

if(Qt5_FOUND OR Qt6_FOUND)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    set(CMAKE_AUTORCC ON)
endif()

if(SDL2_FOUND)
    if(TARGET SDL2::SDL2)
        get_target_property(SDL2_TARGET_INCLUDES SDL2::SDL2 INTERFACE_INCLUDE_DIRECTORIES)
        if(SDL2_TARGET_INCLUDES)
            include_directories(${SDL2_TARGET_INCLUDES})
        endif()
    elseif(SDL2_INCLUDE_DIRS)
        include_directories(${SDL2_INCLUDE_DIRS})
    endif()
endif()

if(OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

function(file_has_main source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "(^|[ \t\r\n])main[ \t\r\n]*\\(" has_main "${source_content}")
    if(has_main)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(make_target_name input_path output_var)
    string(REPLACE "/" "_" target_name "${input_path}")
    string(REPLACE "." "_" target_name "${target_name}")
    string(REPLACE "-" "_" target_name "${target_name}")
    string(REPLACE "+" "x" target_name "${target_name}")
    set(${output_var} "${target_name}" PARENT_SCOPE)
endfunction()

function(source_uses_sdl source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*SDL[^>\"]*[>\"]" has_sdl_include "${source_content}")
    if(has_sdl_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(source_uses_sdl_ttf source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*SDL_ttf[^>\"]*[>\"]" has_sdl_ttf_include "${source_content}")
    if(has_sdl_ttf_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(source_uses_opencv source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*opencv2/[^>\"]*[>\"]" has_cv_include "${source_content}")
    if(has_cv_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(source_uses_qt source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*Q[A-Za-z0-9_]*[^>\"]*[>\"]" has_qt_include "${source_content}")
    if(has_qt_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(source_uses_acidcam source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"][^>\"]*(acidcam/ac\\.h|ac\\.h)[^>\"]*[>\"]" has_ac_include "${source_content}")
    if(has_ac_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(source_uses_execution source_path out_var)
    file(READ "${CMAKE_CURRENT_SOURCE_DIR}/${source_path}" source_content)
    string(REGEX MATCH "#[ \t]*include[ \t]*[<\"]execution[>\"]" has_execution_include "${source_content}")
    if(has_execution_include)
        set(${out_var} TRUE PARENT_SCOPE)
    else()
        set(${out_var} FALSE PARENT_SCOPE)
    endif()
endfunction()

function(link_optional_deps target_name)
    set(needs_sdl FALSE)
    set(needs_sdl_ttf FALSE)
    set(needs_cv FALSE)
    set(needs_qt FALSE)
    set(needs_tbb FALSE)

    foreach(source_file IN LISTS ARGN)
        source_uses_sdl("${source_file}" has_sdl)
        source_uses_sdl_ttf("${source_file}" has_sdl_ttf)
        source_uses_opencv("${source_file}" has_cv)
        source_uses_qt("${source_file}" has_qt)
        source_uses_execution("${source_file}" has_execution)

        if(has_sdl)
            set(needs_sdl TRUE)
        endif()
        if(has_sdl_ttf)
            set(needs_sdl_ttf TRUE)
        endif()
        if(has_cv)
            set(needs_cv TRUE)
        endif()
        if(has_qt)
            set(needs_qt TRUE)
        endif()
        if(has_execution)
            set(needs_tbb TRUE)
        endif()
    endforeach()

    if(needs_sdl)
        if(TARGET SDL2::SDL2)
            target_link_libraries(${target_name} PRIVATE SDL2::SDL2)
        elseif(SDL2_LIBRARIES)
            target_link_libraries(${target_name} PRIVATE ${SDL2_LIBRARIES})
        endif()
    endif()

    if(needs_sdl_ttf)
        if(TARGET SDL2_ttf::SDL2_ttf)
            target_link_libraries(${target_name} PRIVATE SDL2_ttf::SDL2_ttf)
        elseif(SDL2_TTF_LIBRARIES)
            target_link_libraries(${target_name} PRIVATE ${SDL2_TTF_LIBRARIES})
        elseif(SDL2_ttf_LIBRARIES)
            target_link_libraries(${target_name} PRIVATE ${SDL2_ttf_LIBRARIES})
        endif()
    endif()

    if(needs_cv AND OpenCV_FOUND)
        target_link_libraries(${target_name} PRIVATE ${OpenCV_LIBS})
    endif()

    if(needs_qt)
        if(Qt6_FOUND)
            target_link_libraries(${target_name} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
        elseif(Qt5_FOUND)
            target_link_libraries(${target_name} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)
        endif()
    endif()

    if(needs_tbb)
        if(TARGET TBB::tbb)
            target_link_libraries(${target_name} PRIVATE TBB::tbb)
        elseif(TBB_LIBRARIES)
            target_link_libraries(${target_name} PRIVATE ${TBB_LIBRARIES})
        endif()
    endif()
endfunction()

file(GLOB CHILDREN RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "*")
set(EXAMPLE_ROOTS)
foreach(child IN LISTS CHILDREN)
    if(IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/${child}" AND
       NOT child STREQUAL "build" AND
       NOT child STREQUAL "docs" AND
       NOT child STREQUAL ".git")
        list(APPEND EXAMPLE_ROOTS "${child}")
    endif()
endforeach()

set(EXAMPLE_SOURCES)
foreach(root IN LISTS EXAMPLE_ROOTS)
    file(GLOB_RECURSE root_sources CONFIGURE_DEPENDS
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${root}/*.cpp"
        "${root}/*.cc"
    )
    list(APPEND EXAMPLE_SOURCES ${root_sources})
endforeach()

set(SKIP_SOURCES)

if(NOT SDL2_FOUND)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_sdl("${source_file}" has_sdl_include)
        if(has_sdl_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "SDL2 package not found: skipping SDL-dependent example sources")
endif()

if(NOT SDL2_ttf_FOUND)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_sdl_ttf("${source_file}" has_sdl_ttf_include)
        if(has_sdl_ttf_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "SDL2_ttf package not found: skipping SDL_ttf-dependent example sources")
endif()

if(NOT OpenCV_FOUND)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_opencv("${source_file}" has_cv_include)
        if(has_cv_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "OpenCV package not found: skipping OpenCV-dependent example sources")
endif()

if(NOT TBB_FOUND)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_execution("${source_file}" has_execution_include)
        if(has_execution_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "TBB package not found: skipping <execution>-dependent example sources")
endif()

if(NOT (Qt5_FOUND OR Qt6_FOUND))
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_qt("${source_file}" has_qt_include)
        if(has_qt_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "Qt package not found: skipping Qt-dependent example sources")
endif()

if(NOT BUILD_ACIDCAM_EXAMPLES)
    list(APPEND SKIP_SOURCES
        examples/ac-tool/ac-tool.cpp
        examples/libacidcam/main.cpp
        examples/filter_design_02/main.cpp
    )
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_acidcam("${source_file}" has_ac_include)
        if(has_ac_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "BUILD_ACIDCAM_EXAMPLES=OFF: skipping AcidCam-dependent example sources")
elseif(NOT ACIDCAM_INCLUDE_DIR)
    foreach(source_file IN LISTS EXAMPLE_SOURCES)
        source_uses_acidcam("${source_file}" has_ac_include)
        if(has_ac_include)
            list(APPEND SKIP_SOURCES "${source_file}")
        endif()
    endforeach()
    message(STATUS "AcidCam headers not found: skipping AcidCam-dependent example sources")
else()
    include_directories(${ACIDCAM_INCLUDE_DIR})
endif()

foreach(source_file IN LISTS EXAMPLE_SOURCES)
    if(source_file MATCHES "(^|/)build(/|$)" OR source_file MATCHES "(^|/)CMakeFiles(/|$)")
        list(APPEND SKIP_SOURCES "${source_file}")
    endif()
endforeach()

list(REMOVE_DUPLICATES SKIP_SOURCES)
list(REMOVE_ITEM EXAMPLE_SOURCES ${SKIP_SOURCES})

set(EXAMPLE_DIRS)
foreach(source_file IN LISTS EXAMPLE_SOURCES)
    get_filename_component(source_dir "${source_file}" DIRECTORY)
    list(APPEND EXAMPLE_DIRS "${source_dir}")
endforeach()
list(REMOVE_DUPLICATES EXAMPLE_DIRS)

foreach(source_dir IN LISTS EXAMPLE_DIRS)
    file(GLOB dir_sources CONFIGURE_DEPENDS
        RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
        "${source_dir}/*.cpp"
        "${source_dir}/*.cc"
    )
    list(REMOVE_ITEM dir_sources ${SKIP_SOURCES})

    set(main_sources)
    set(non_main_sources)
    foreach(source_file IN LISTS dir_sources)
        file_has_main("${source_file}" is_main)
        if(is_main)
            list(APPEND main_sources "${source_file}")
        else()
            list(APPEND non_main_sources "${source_file}")
        endif()
    endforeach()

    list(LENGTH main_sources main_count)

    if(main_count EQUAL 1)
        list(GET main_sources 0 main_source)
        make_target_name("${main_source}" target_name)
        add_executable(${target_name} ${dir_sources})
        target_link_libraries(${target_name} PRIVATE Threads::Threads)
        if(OpenCV_FOUND)
            target_link_libraries(${target_name} PRIVATE ${OpenCV_LIBS})
        endif()
        link_optional_deps(${target_name} ${dir_sources})
    elseif(main_count GREATER 1)
        foreach(main_source IN LISTS main_sources)
            make_target_name("${main_source}" target_name)
            add_executable(${target_name} "${main_source}" ${non_main_sources})
            target_link_libraries(${target_name} PRIVATE Threads::Threads)
            if(OpenCV_FOUND)
                target_link_libraries(${target_name} PRIVATE ${OpenCV_LIBS})
            endif()
            link_optional_deps(${target_name} "${main_source}" ${non_main_sources})
        endforeach()
    endif()
endforeach()