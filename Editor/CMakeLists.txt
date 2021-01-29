find_package(Threads REQUIRED)
add_executable(WickedEngineEditor 
    main_${PLATFORM}.cpp
    $<$<STREQUAL:${PLATFORM},Windows>:App_${PLATFORM}.cpp>
    AnimationWindow.cpp
    CameraWindow.cpp
    DecalWindow.cpp
    Editor.cpp
    EmitterWindow.cpp
    EnvProbeWindow.cpp
    ForceFieldWindow.cpp
    HairParticleWindow.cpp
    IKWindow.cpp
    LayerWindow.cpp
    LightWindow.cpp
    MaterialWindow.cpp
    MeshWindow.cpp
    ModelImporter_GLTF.cpp
    ModelImporter_OBJ.cpp
    NameWindow.cpp
    ObjectWindow.cpp
    PaintToolWindow.cpp
    PostprocessWindow.cpp
    RendererWindow.cpp
    SoundWindow.cpp
    SpringWindow.cpp
    stdafx.cpp
    TransformWindow.cpp
    Translator.cpp
    WeatherWindow.cpp
    xatlas.cpp
)

FIND_PACKAGE(OpenCV REQUIRED)
LIST(APPEND PLATFORM_LIBRARIES dl pthread asound)
# SET(APP_SOURCES alsatut1.cpp ${APP_HEADERS})
# ADD_EXECUTABLE(RubyAI ${APP_SOURCES} ${PLATFORM_SOURCES})
TARGET_INCLUDE_DIRECTORIES(WickedEngineEditor PRIVATE ${OpenCV_INCLUDE_DIRS})
ADD_DEFINITIONS(-DOPENCV_DIR=${OpenCV_DIR}) # Used at runtime to load the cascade classifier XML file
# TARGET_LINK_LIBRARIES(WickedEngineEditor   ${OpenCV_LIBS} ${PLATFORM_LIBRARIES})
find_path(PULSEAUDIO_INCLUDE_DIR
NAMES pulse/pulseaudio.h
DOC "The PulseAudio include directory"
)
find_library(PULSEAUDIO_LIBRARY
NAMES pulse
DOC "The PulseAudio library"
)
include_directories(${PULSEAUDIO_INCLUDE_DIRS})

target_link_libraries(WickedEngineEditor PUBLIC
    ${OpenCV_LIBS} ${PLATFORM_LIBRARIES}
    pulse-simple pulse
	WickedEngine 
	Threads::Threads
)


# target_link_libraries(Audio pulse-simple pulse)


# cmake_minimum_required(VERSION 3.8)
# project(Audio)
# set(CMAKE_CXX_STANDARD 11)
# find_path(PULSEAUDIO_INCLUDE_DIR
#         NAMES pulse/pulseaudio.h
#         DOC "The PulseAudio include directory"
#         )
# find_library(PULSEAUDIO_LIBRARY
#         NAMES pulse
#         DOC "The PulseAudio library"
#         )
# include_directories(${PULSEAUDIO_INCLUDE_DIRS})
# set(SOURCE_FILES main.cpp)
# add_executable(Audio ${SOURCE_FILES})
# target_link_libraries(Audio pulse-simple pulse)
