cmake_minimum_required(VERSION 3.10...3.30)

project(ASTU VERSION 0.10.2)

configure_file(src/AstUtilsConfig.h.in AstUtilsConfig.h)
set(CMAKE_CXX_STANDARD 17)

set(astulib_SOURCES src/Util/StringUtils.cpp include/Util/StringUtils.h)
list(APPEND astulib_SOURCES
                    src/AstUtils0.cpp
                    src/Util/VersionInfo.cpp
                    src/Util/Controllable.cpp
                    src/Util/Controller.cpp
                    src/Util/Memento.cpp
                    src/Math/Random.cpp
                    src/Math/MathUtils.cpp
                    src/Util/StringUtils.cpp include/Util/StringUtils.h


                    src/Graphics/AstuGraphics.cpp

                    src/Graphics/Palette.cpp
                    src/Graphics/Image.cpp 
                    src/Graphics/BmpCodec.cpp
                    src/Graphics/Pattern.cpp
                    src/Graphics/BoundingBox.cpp
                    src/Graphics/Quadtree.cpp
                    src/Graphics/PatternRenderer.cpp
                    src/Graphics/ImageRenderer.cpp

                    src/Audio/AudioBuffer.cpp
                    src/Audio/WaveCodec.cpp
                    src/Audio/AstuAudio.cpp

                    src/ECS/EntityService.cpp
                    src/ECS/EntityFactoryService.cpp
                    src/ECS/AutoDestructSystem.cpp
                    src/Input/InputMappingService.cpp

                    src/Input/AstuIO.cpp
                    src/Input/Keys.cpp
                    src/Input/Mouse.cpp
                    src/Input/Keyboard.cpp

                    src/Service/ServiceManager.cpp
                    src/Service/Service.cpp
                    src/Service/UpdateService.cpp
                    src/Service/ActionSignalService.cpp
                    src/Service/StateService.cpp
                    src/Service/TaskService.cpp
                    src/Service/Tasks.cpp
                    src/Service/InteractiveApplication.cpp

                    src/Suite2D/Scene.cpp
                    src/Suite2D/CameraService.cpp
                    src/Suite2D/CameraControlService.cpp
                    src/Suite2D/SceneSystem.cpp
                    src/Suite2D/AutoRotateSystem.cpp
                    src/Suite2D/AutoRotateSystem.cpp
                    src/Suite2D/ShapeGenerator.cpp
                    src/Suite2D/CBody.cpp
                    src/Suite2D/CColliders.cpp

                    src/Ai/Quantizer.cpp
                    src/Ai/StateUtil.cpp
                    src/Ai/QTable.cpp

                    src/AstUtils1.cpp)

OPTION(USE_JACK "Build the project with support for JACK Audio Connection Kit" OFF)
#set(USE_JACK false CACHE BOOL "Use JACK2")
if (USE_JACK)
    list(APPEND astulib_SOURCES 
        src/SuiteJack/JackErrorUtil.cpp
        src/SuiteJack/JackClient.cpp
        )
endif(USE_JACK) 


OPTION(USE_SDL "Build the project with support for SDL2" OFF)
#set(WITH_SDL false CACHE BOOL "Use SDL")

if(USE_SDL)

    list(APPEND astulib_SOURCES 
        src/SuiteSDL/SdlApplication0.cpp
        src/SuiteSDL/Application.cpp
        src/SuiteSDL/ApplicationImpl.cpp
        
        src/SuiteSDL/SdlService.cpp
        src/SuiteSDL/SdlEventService.cpp
        src/SuiteSDL/SdlKeyTable.cpp
        src/SuiteSDL/SdlVideoService.cpp
        src/SuiteSDL/SdlRenderService.cpp
        src/SuiteSDL/SdlJoystickService.cpp
        src/SuiteSDL/SdlAudioService.cpp
        src/SuiteSDL/SdlTimeService.cpp
        src/SuiteSDL/SdlLineRenderer.cpp
        src/SuiteSDL/SdlSceneGraph2D.cpp
        src/SuiteSDL/SdlSceneRenderer2D.cpp
        src/SuiteSDL/SdlRecordingSceneRenderer2D.cpp
        src/SuiteSDL/SdlApplication.cpp
        src/SuiteSDL/SdlMessageBox.cpp
        )
else(USE_SDL)
    list(APPEND astulib_SOURCES src/SuiteSDL/SdlApplicationDummy.cpp src/Util/DefaultMessageBox.cpp)
endif(USE_SDL)                 

add_library(astu ${astulib_SOURCES})

set(astulib_INCLUDES )
list(APPEND astulib_INCLUDES
        astu PRIVATE "${PROJECT_BINARY_DIR}" 
        astu PRIVATE "${PROJECT_SOURCE_DIR}/src"
        astu PUBLIC ${PROJECT_SOURCE_DIR}/include)
      
if(USE_SDL)
    # Portable SDL2 detection: try CMake config-package first (vcpkg, some
    # distros, Homebrew), then pkg-config (Homebrew, most Linux distros),
    # finally fall back to the macOS framework / Windows SDL2_HOME layouts.
    #
    # The HINTS below cover the standard Homebrew install layouts on macOS
    # (Apple Silicon and Intel) so `find_package` works out of the box
    # without requiring the user to set CMAKE_PREFIX_PATH.
    find_package(SDL2 CONFIG QUIET
        HINTS
            /opt/homebrew/opt/sdl2
            /usr/local/opt/sdl2)
    if(NOT SDL2_FOUND)
        find_package(PkgConfig QUIET)
        if(PkgConfig_FOUND)
            pkg_check_modules(SDL2 IMPORTED_TARGET sdl2)
        endif()
    endif()

    if(TARGET SDL2::SDL2)
        message(STATUS "SDL2: linking via SDL2::SDL2 (CMake config package)")
        target_link_libraries(astu SDL2::SDL2)
        # Homebrew's SDL2Config sets the imported target's include dir to
        # `<prefix>/include/SDL2` so that `#include <SDL.h>` works. Our
        # sources use `#include <SDL2/SDL.h>`, so also add the parent dir.
        if(SDL2_INCLUDE_DIRS)
            target_include_directories(astu PRIVATE ${SDL2_INCLUDE_DIRS})
        elseif(SDL2_PREFIX)
            target_include_directories(astu PRIVATE "${SDL2_PREFIX}/include")
        endif()
    elseif(TARGET PkgConfig::SDL2)
        message(STATUS "SDL2: linking via PkgConfig::SDL2 (pkg-config)")
        target_link_libraries(astu PkgConfig::SDL2)
    elseif(APPLE AND EXISTS "/Library/Frameworks/SDL2.framework")
        target_link_libraries(astu "-F/Library/Frameworks" "-framework SDL2")
        target_include_directories(astu PRIVATE
            /Library/Frameworks/SDL2.framework/Headers)
    elseif(WIN32 AND DEFINED ENV{SDL2_HOME})
        target_link_libraries(astu $ENV{SDL2_HOME}/lib/x64/SDL2.lib)
        target_include_directories(astu PRIVATE $ENV{SDL2_HOME}/include)
    else()
        message(FATAL_ERROR
            "USE_SDL=ON but SDL2 was not found. Install SDL2 (e.g. "
            "'brew install sdl2' on macOS, 'apt install libsdl2-dev' on "
            "Debian/Ubuntu) or set CMAKE_PREFIX_PATH / SDL2_HOME to your "
            "SDL2 install prefix.")
    endif()
endif(USE_SDL)


if(USE_JACK)
    IF (WIN32)
        target_include_directories(astu PRIVATE $ENV{JACK2_HOME}/include)
        target_link_libraries(astu $ENV{JACK2_HOME}/lib/libjack64.lib)
    ELSE()
        target_link_libraries(astu jack)    
    ENDIF()
endif(USE_JACK)                 

target_include_directories(${astulib_INCLUDES})