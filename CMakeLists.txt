cmake_minimum_required(VERSION 3.28)
project(FlappyBird LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main src/main.cpp
        src/Render.hpp
        src/Render.cpp
        src/Column.hpp
        src/Column.cpp
        src/Game.hpp
        src/Game.cpp
        src/Bird.hpp
        src/Bird.cpp)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    # Add path to DLLs needed for compilation
    set(MINGW_DLLS
        ${CMAKE_SOURCE_DIR}/dlls/libgcc_s_dw2-1.dll
        ${CMAKE_SOURCE_DIR}/dlls/libstdc++-6.dll
        ${CMAKE_SOURCE_DIR}/dlls/libwinpthread-1.dll
    )

    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${MINGW_DLLS} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
endif()
