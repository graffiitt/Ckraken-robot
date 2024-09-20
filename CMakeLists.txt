cmake_minimum_required(VERSION 3.12)
project(craken_ui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Network REQUIRED)

file(GLOB CPP_FILE "*.cpp")
message("Adding ${PROJECT_NAME} CPP files: " )
foreach(source ${CPP_FILE})
    message("  - " ${source})
endforeach(source)
 
file(GLOB H_FILE "*.h")
message("Adding ${PROJECT_NAME} H files: " )
foreach(source ${H_FILE})
    message("  - " ${source})
endforeach(source)

file(GLOB UI_FILE "*.ui")
message("Adding ${PROJECT_NAME} UI files: " )
foreach(source ${UI_FILE})
    message("  - " ${source})
endforeach(source)

set(QRCFILE resource/resource.qrc)

add_executable(
    ${PROJECT_NAME} 
    ${CPP_FILE}
    ${H_FILE}
    ${UI_FILE}
    ${QRCFILE}
    )

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} Qt5::Widgets Qt5::Network)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})
