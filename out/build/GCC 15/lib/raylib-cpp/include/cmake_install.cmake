# Install script for directory: /home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/lilian/Documents/projects/c/balalo/out/install/GCC 15")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "0")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/AudioDevice.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/AudioStream.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/AutomationEventList.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/BoundingBox.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Camera2D.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Camera3D.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Color.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/FileData.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/FileText.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Font.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Functions.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Gamepad.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Image.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Keyboard.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Material.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Matrix.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Mesh.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/MeshUnmanaged.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Model.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/ModelAnimation.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Mouse.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Music.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Ray.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/RayCollision.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/RaylibException.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/raylib-cpp-utils.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/raylib-cpp.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/raylib.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/raymath.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Rectangle.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/RenderTexture.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/ShaderUnmanaged.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Shader.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Sound.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Text.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Texture.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/TextureUnmanaged.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Touch.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Vector2.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Vector3.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Vector4.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/VrStereoConfig.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Wave.hpp"
    "/home/lilian/Documents/projects/c/balalo/lib/raylib-cpp/include/Window.hpp"
    )
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
if(CMAKE_INSTALL_LOCAL_ONLY)
  file(WRITE "/home/lilian/Documents/projects/c/balalo/out/build/GCC 15/lib/raylib-cpp/include/install_local_manifest.txt"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
