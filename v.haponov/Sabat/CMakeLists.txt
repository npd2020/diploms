cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(Sabat)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

find_package(Qt5 REQUIRED
    COMPONENTS
        Core
)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/geometry
    ${PROJECT_SOURCE_DIR}/utils)

file(GLOB headers
    ${PROJECT_SOURCE_DIR}/include/*.h
    ${PROJECT_SOURCE_DIR}/geometry/*.h
    ${PROJECT_SOURCE_DIR}/utils/*.h
    )

file(GLOB sources
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/geometry/*.cpp
    ${PROJECT_SOURCE_DIR}/utils/*.cpp
    )


add_executable(sabat sabat.cpp ${sources} ${headers})
target_link_libraries(sabat ${Geant4_LIBRARIES})

set(SABAT_SCRIPTS
  scripts/sabat.in
  scripts/sabat.out
  scripts/RShow.c
  init_vis.mac
# scripts/run1.mac
# scripts/run2.mac
  vis.mac
  scripts/show.py
  #physic
#  physMacs/alpha.mac
#  physMacs/Cf238.mac
#  physMacs/Co60.mac
#  physMacs/Gd158.mac
#  physMacs/electronicCapture.mac
#  physMacs/fullChain.mac
#  physMacs/neutron.mac
#  physMacs/proton.mac
#  physMacs/No252.mac
#  physMacs/Po212.mac
#  physMacs/Ra228.mac
#  physMacs/singleDecay.mac
#  physMacs/timeWindow.mac
#  physMacs/timeWindowBiased.mac
#  physMacs/timeWindowBiased.data

  )

foreach(_script ${SABAT_SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()

add_custom_target(Sabat DEPENDS sabat)

install(TARGETS sabat DESTINATION bin)

