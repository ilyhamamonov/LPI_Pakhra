cmake_minimum_required(VERSION 3.6)
set(NAME Final)
project(${NAME})

option(WITH_GEANT4_UIVIS "Build project with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
    find_package(Geant4 REQUIRED ui_all vis_all)
else()
    find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

add_executable(${NAME} main.cc ${sources} ${headers})
target_link_libraries(${NAME} ${Geant4_LIBRARIES})

set(FSCRIPTS
        init_vis.mac
		vis.mac
        )

foreach(_script ${FSCRIPTS})
    configure_file(
            ${PROJECT_SOURCE_DIR}/${_script}
            ${PROJECT_BINARY_DIR}/${_script}
            COPYONLY
    )
endforeach()

file(COPY ${PROJECT_SOURCE_DIR}/geometry
	DESTINATION ${PROJECT_BUILD_DIR}/
	)