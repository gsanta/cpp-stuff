cmake_minimum_required(VERSION 3.16)
project(Algorithms VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2
        GIT_TAG v3.3.0
        GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

set(ALGORITHMS
    segmentation_tree
    red_black_tree
    quick_sort
)

set(CPP_LANG_FEATURES
    storage
)

function(create_project_from_sources topic folder)

    file(GLOB SOURCE
        "src/${topic}/${folder}/*.h"
        "src/${topic}/${folder}/*.cpp"
        "src/${topic}/${folder}/*.vs"
        "src/${topic}/${folder}/*.fs"
    )

    file(GLOB EXCLUDE_SOURCE
        "src/${topic}/${folder}/*test.cpp"
    )

    list(REMOVE_ITEM SOURCE ${EXCLUDE_SOURCE})

    if (topic STREQUAL "algorithms")
		set(NAME "algorithm_${folder}")
	elseif(topic STREQUAL "problems")
		set(NAME "problem_${folder}")
    elseif(topic STREQUAL "cpp_lang_features")
		set(NAME "cpp_lang_feature_${folder}")
	endif()

    add_executable(${NAME} ${SOURCE})

    set_target_properties(${NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${topic}")
endfunction()

foreach(ALGORITHM ${ALGORITHMS})
	create_project_from_sources("algorithms" ${ALGORITHM})
endforeach(ALGORITHM)

foreach(CPP_LANG_FEATURES ${CPP_LANG_FEATURES})
	create_project_from_sources("cpp_lang_features" ${CPP_LANG_FEATURES})
endforeach(CPP_LANG_FEATURES)

set(TEST "unit_test")
file(GLOB_RECURSE TEST_SOURCES 
    "src/algorithms/segmentation_tree/test.cpp"
    "src/algorithms/red_black_tree/test.cpp"
    "src/algorithms/quick_sort/test.cpp"
)

if(CODE_COVERAGE)
    set(CMAKE_BUILD_TYPE Debug)
    include(CodeCoverage)
    append_coverage_compiler_flags()

    set(COVERAGE_TARGET_NAME "coverage")
    set(EXECUTABLE_NAME ${TEST})
    set(EXCLUDE_PATH "/src/CMakeCCompilerId.c;tests/*;/usr/*;*/catch2/*;")
    set(BASE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

    message("BASE_DIRECTORY: ${BASE_DIRECTORY}")

    if (COVERAGE_REPORTER STREQUAL "XML")
        setup_target_for_coverage_gcovr_xml(NAME ${COVERAGE_TARGET_NAME} EXECUTABLE ${EXECUTABLE_NAME} EXCLUDE ${EXCLUDE_PATH} BASE_DIRECTORY ${BASE_DIRECTORY})
    elseif(COVERAGE_REPORTER STREQUAL "HTML")
        setup_target_for_coverage_lcov(NAME ${COVERAGE_TARGET_NAME} EXECUTABLE ${EXECUTABLE_NAME} EXCLUDE ${EXCLUDE_PATH} BASE_DIRECTORY ${BASE_DIRECTORY})
    else()
        message(FATAL_ERROR "Invalid COVERAGE_REPORTER option: ${COVERAGE_REPORTER}")
    endif()
endif()

enable_testing()

set(TEST_INCLUDES "./")

set(CMAKE_VERBOSE_MAKEFILE on)

add_executable(${TEST} ${TEST_SOURCES})
target_include_directories(${TEST} PUBLIC ${TEST_INCLUDES})
target_link_libraries(${TEST} PUBLIC Catch2::Catch2WithMain)
set_target_properties(${TEST} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")



