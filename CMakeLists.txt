
cmake_minimum_required(VERSION 3.20)
project(SyobonKZ)

# Set the name of the executable
if( ${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(EXECUTABLE_NAME main)
else()
    set(EXECUTABLE_NAME SyobonAction)
endif()

if( ${CMAKE_SYSTEM_NAME} MATCHES "Android")
    set(BUILD_SHARED_LIBS ON)
else()
    set(BUILD_SHARED_LIBS OFF)
endif()

# options
option(SYOBONKZ_USE_SDL3 "Use SDL3, SDL3_image, SDL3_mixer and SDL3_ttf instead of SDL 1.2 counterparts" ON)

# SDL3 error checking
if(SYOBONKZ_USE_SDL3)
    add_compile_definitions(SYOBONKZ_USE_SDL3=1)

    if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
        message( FATAL_ERROR "SYOBONKZ_USE_SDL3 is unsupported with Emscripten")
    endif()
endif()

# html
if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    set(SYOBONKZ_EMSCRIPTEN_C_FLAGS "-s USE_SDL=1 -s USE_SDL_IMAGE=1 -s USE_SDL_MIXER=1 -s ALLOW_MEMORY_GROWTH=1")
    set(SYOBONKZ_EMSCRIPTEN_LINK_FLAGS "--use-preload-plugins --preload-file text --preload-file res --preload-file BGM --preload-file SE -sSTACK_SIZE=8MB")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SYOBONKZ_EMSCRIPTEN_C_FLAGS} ${SYOBONKZ_EMSCRIPTEN_LINK_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SYOBONKZ_EMSCRIPTEN_C_FLAGS} ${SYOBONKZ_EMSCRIPTEN_LINK_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

# import ExternalProject module
include(ExternalProject)

# set the output directory for built objects.
# this makes sure that the dynamic libraries goes into the build directory automatically.
set(SYOBONKZ_LIB_INSTALL_DIR ${CMAKE_BINARY_DIR}/local_libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${SYOBONKZ_LIB_INSTALL_DIR}")

# prevent installing to system directories. 
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}" CACHE INTERNAL "")

if(SYOBONKZ_USE_SDL3)

    if( ${CMAKE_SYSTEM_NAME} MATCHES "Android")
        find_package(SDL3 REQUIRED)
        find_package(SDL3_image REQUIRED)
        find_package(SDL3_mixer REQUIRED)
        find_package(SDL3_ttf REQUIRED)

        # we will put SDL3::Headers in SDL3_INCLUDE_DIR to pass it into SDL3_gfx
        get_target_property(SDL3_INCLUDE_DIR SDL3::Headers INTERFACE_INCLUDE_DIRECTORIES)

        # add SDL3_gfx
        add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDL3_gfx EXCLUDE_FROM_ALL)

        # dont build static
        set_target_properties(SDL3_gfx_Static PROPERTIES EXCLUDE_FROM_ALL TRUE)
        set(SDL3_GFX_LIB SDL3_gfx_Shared)
    else()
        # dont build sdl3 tests
        set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)
        set(SDL_EXAMPLES OFF CACHE BOOL "" FORCE)

        # need ttf libs
        set(SDLTTF_VENDORED ON)

        # add SDL3 libs
        add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDL3 EXCLUDE_FROM_ALL)
        add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDL3_image EXCLUDE_FROM_ALL)
        add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDL3_mixer EXCLUDE_FROM_ALL)
        add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDL3_ttf EXCLUDE_FROM_ALL)

        # we will put SDL3::Headers in SDL3_INCLUDE_DIR to pass it into SDL3_gfx
        get_target_property(SDL3_INCLUDE_DIR SDL3::Headers INTERFACE_INCLUDE_DIRECTORIES)

        # add SDL3_gfx
        add_subdirectory(${PROJECT_SOURCE_DIR}/lib/SDL3_gfx EXCLUDE_FROM_ALL)

        # dont build static
        set_target_properties(SDL3_gfx_Shared PROPERTIES EXCLUDE_FROM_ALL TRUE)
        set(SDL3_GFX_LIB SDL3_gfx_Static)
    endif()

elseif(NOT(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten"))

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
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${SYOBONKZ_LIB_INSTALL_DIR}"
        BUILD_COMMAND make
        INSTALL_COMMAND make install
    )

    ExternalProject_Add(SDL_mixer
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_mixer
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${SYOBONKZ_LIB_INSTALL_DIR}"
        BUILD_COMMAND make
        INSTALL_COMMAND make install
    )

    ExternalProject_Add(SDL_gfx
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_gfx
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${SYOBONKZ_LIB_INSTALL_DIR}" "--enable-mmx=no" # need to disable mmx on non-x86 CPUs
        BUILD_COMMAND make
        INSTALL_COMMAND make install
    )

    ExternalProject_Add(SDL_ttf
        SOURCE_DIR ${PROJECT_SOURCE_DIR}/lib/SDL_ttf
        PREFIX ${CMAKE_INSTALL_PREFIX}
        CONFIGURE_COMMAND "<SOURCE_DIR>/configure" "--prefix=${SYOBONKZ_LIB_INSTALL_DIR}"
        BUILD_COMMAND make noinst_PROGRAMS= # noinst_PROGRAMS= avoids building showfont.c, building showfont.c on macOS may fail due to iconv
        INSTALL_COMMAND make install noinst_PROGRAMS= # read above
    )
endif()

if(MINGW)
    set(SYOBONKZ_WINDOWS_ICON_RC icon.rc)
    set(SYOBONKZ_WINDOWS_ICON_RC_FULL_PATH ${PROJECT_SOURCE_DIR}/${SYOBONKZ_WINDOWS_ICON})
    configure_file("icon.rc.in" "${SYOBONKZ_WINDOWS_ICON_RC}")
else()
    set(SYOBONKZ_WINDOWS_ICON_RC)
endif()

set(SOURCE_FILES_SYOBON
    main.h
    main.cpp
    loadg.cpp
    DxLib.h
    DxLib.cpp

    # files added by +KZ to split the code
    blocks.h
    blocks.cpp
    entities.h
    entities.cpp
    extra_graphics.h
    extra_graphics.cpp
    global_vars.h
    global_vars.cpp
    levels.h
    levels.cpp
    player.h
    player.cpp
    title.h
    title.cpp

    # a thing filled with macros and preprocessor checks
    crossplatform.h
    crossplatform.cpp

    # for different sdl versions
    sdl_includer.h
    sdl_includer.cpp

    # windows icon
    ${SYOBONKZ_WINDOWS_ICON_RC}
)

if( ${CMAKE_SYSTEM_NAME} MATCHES "Android")
    add_library(${EXECUTABLE_NAME} SHARED ${SOURCE_FILES_SYOBON})
else()
    add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES_SYOBON})
endif()

# we should not need to include standard libraries as .dll/.so
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    target_link_options(${EXECUTABLE_NAME} PRIVATE -static-libgcc)
    target_link_options(${EXECUTABLE_NAME} PRIVATE -static-libstdc++)
elseif(MINGW)
    target_link_options(${EXECUTABLE_NAME} PRIVATE --static)
endif()

#html
if( ${CMAKE_SYSTEM_NAME} MATCHES "Emscripten")
    target_link_options(${EXECUTABLE_NAME} PRIVATE
        ${SYOBONKZ_EMSCRIPTEN_LINK_FLAGS}
    )
endif()

if(SYOBONKZ_USE_SDL3)

    target_include_directories(${EXECUTABLE_NAME} PRIVATE
        SDL3::Headers
        SDL3_image::Headers
        SDL3_mixer::Headers
        SDL3_ttf::Headers
        SDL3_gfx::Headers
        ${CMAKE_BINARY_DIR}/include/
        ${PROJECT_SOURCE_DIR}/lib/
    )

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        SDL3::SDL3
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        SDL3_ttf::SDL3_ttf
        ${SDL3_GFX_LIB}
    )
elseif(NOT(${CMAKE_SYSTEM_NAME} MATCHES "Emscripten"))

    target_include_directories(${EXECUTABLE_NAME} PRIVATE
        ${SDL_INCLUDE_DIRS}
        ${SYOBONKZ_LIB_INSTALL_DIR}/include/SDL
    )

    target_link_libraries(${EXECUTABLE_NAME} PRIVATE
        ${SDL_LIBRARIES}
        ${SYOBONKZ_LIB_INSTALL_DIR}/lib/libSDL_image${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${SYOBONKZ_LIB_INSTALL_DIR}/lib/libSDL_mixer${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${SYOBONKZ_LIB_INSTALL_DIR}/lib/libSDL_gfx${CMAKE_SHARED_LIBRARY_SUFFIX}
        ${SYOBONKZ_LIB_INSTALL_DIR}/lib/libSDL_ttf${CMAKE_SHARED_LIBRARY_SUFFIX}
    )
endif()

# copy syobon action data
file(COPY ${PROJECT_SOURCE_DIR}/data/BGM DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/data/res DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/data/SE DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${PROJECT_SOURCE_DIR}/data/text DESTINATION ${CMAKE_BINARY_DIR})
