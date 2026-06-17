
cmake_minimum_required(VERSION 4.2)
project(SyobonKZ)

# Set the name of the executable
set(EXECUTABLE_NAME SyobonAction)

# options
option(SYOBONKZ_BUILD_SDL1_EXTENSIONS "Build SDL_image, SDL_mixer, SDL_gfx and SDL_ttf (requires submodules being cloned)" ON)

# html
if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(SYOBONKZ_EMSCRIPTEN_C_FLAGS "-s USE_SDL=1 -s USE_SDL_IMAGE=1")
    set(SYOBONKZ_EMSCRIPTEN_LINK_FLAGS "--use-preload-plugins --preload-file res --preload-file BGM --preload-file SE -sSTACK_SIZE=8MB")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SYOBONKZ_EMSCRIPTEN_C_FLAGS} ${SYOBONKZ_EMSCRIPTEN_LINK_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYOBONKZ_EMSCRIPTEN_C_FLAGS} ${SYOBONKZ_EMSCRIPTEN_LINK_FLAGS}")
    set(SYOBONKZ_BUILD_SDL1_EXTENSIONS OFF)
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# import ExternalProject module
include(ExternalProject)

# set the output directory for built objects.
# this makes sure that the dynamic libraries goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

if(SYOBONKZ_BUILD_SDL1_EXTENSIONS)

    # search SDL 1.2 in the system
    # this allows choosing to use:
    #   SDL 1.2
    #   SDL2 with sdl12-compat
    #   SDL3 with sdl2-compat and sdl12-compat
    # could be better though...
    find_package(SDL REQUIRED)

    ExternalProject_Add(SDL_image
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_image
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${CMAKE_INSTALL_PREFIX}"
        BUILD_COMMAND make
        INSTALL_COMMAND make install
    )

    ExternalProject_Add(SDL_mixer
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_mixer
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${CMAKE_INSTALL_PREFIX}"
        BUILD_COMMAND make
        INSTALL_COMMAND make install
    )

    ExternalProject_Add(SDL_gfx
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_gfx
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${CMAKE_INSTALL_PREFIX}" "--enable-mmx=no" # need to disable mmx on non-x86 CPUs
        BUILD_COMMAND make
        INSTALL_COMMAND make install
    )

    ExternalProject_Add(SDL_ttf
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_ttf
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${CMAKE_INSTALL_PREFIX}"
        BUILD_COMMAND make noinst_PROGRAMS= # noinst_PROGRAMS= avoids building showfont.c, building showfont.c on macOS may fail due to iconv
        INSTALL_COMMAND make install noinst_PROGRAMS= # read above
    )

else()
    if(NOT(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten"))
        find_package(SDL REQUIRED)
        find_package(SDL_image REQUIRED)
        find_package(SDL_mixer REQUIRED)
        find_package(SDL_gfx REQUIRED)
        find_package(SDL_ttf REQUIRED)
    endif()
endif()

add_executable(${EXECUTABLE_NAME}
    main.cpp
    loadg.cpp
    DxLib.cpp
    global_vars.cpp
    levels.cpp
)

#html
if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(${EXECUTABLE_NAME} PRIVATE
        ${SYOBONKZ_EMSCRIPTEN_LINK_FLAGS}
    )
endif()

if(SYOBONKZ_BUILD_SDL1_EXTENSIONS)

    target_include_directories(${EXECUTABLE_NAME} PRIVATE
        ${SDL_INCLUDE_DIRS}
        ${CMAKE_BINARY_DIR}/include/SDL
    )

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        ${SDL_LIBRARIES}
        ${CMAKE_BINARY_DIR}/lib/libSDL_image${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${CMAKE_BINARY_DIR}/lib/libSDL_mixer${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${CMAKE_BINARY_DIR}/lib/libSDL_gfx${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${CMAKE_BINARY_DIR}/lib/libSDL_ttf${CMAKE_SHARED_LIBRARY_SUFFIX}
    )
else()
    target_include_directories(${EXECUTABLE_NAME} PRIVATE
        ${SDL_INCLUDE_DIRS}
        ${SDL_IMAGE_INCLUDE_DIRS}
        ${SDL_MIXER_INCLUDE_DIRS}
        ${SDL_GFX_INCLUDE_DIRS}
        ${SDL_TTF_INCLUDE_DIRS}
    )

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        ${SDL_LIBRARIES}
        ${SDL_IMAGE_LIBRARIES}
        ${SDL_MIXER_LIBRARIES}
        ${SDL_GFX_LIBRARIES}
        ${SDL_TTF_LIBRARIES}
    )
endif()

# copy syobon action data
file(COPY ${PROJECT_SOURCE_DIR}/BGM DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/res DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/SE DESTINATION ${CMAKE_BINARY_DIR})
