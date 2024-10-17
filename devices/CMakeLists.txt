cmake_minimum_required(VERSION 3.12)
set(PROJECT devices)

find_package(Qt6 COMPONENTS SerialBus REQUIRED)

file(GLOB CPP_FILE "*.cpp")
message("Adding ${PROJECT} CPP files: " )
foreach(source ${CPP_FILE})
    message("  - " ${source})
endforeach(source)
 
file(GLOB H_FILE "*.h")
message("Adding ${PROJECT} H files: " )
foreach(source ${H_FILE})
    message("  - " ${source})
endforeach(source)

file(GLOB UI_FILE "*.ui")
message("Adding ${PROJECT} UI files: " )
foreach(source ${UI_FILE})
    message("  - " ${source})
endforeach(source)

find_library(../stateManager stateManager)

add_library( 
    ${PROJECT} SHARED
    ${CPP_FILE}
    ${H_FILE}
    ${UI_FILE}
    )

target_link_libraries(${PROJECT} ${catkin_LIBRARIES} Qt6::Widgets Qt6::SerialBus stateManager)
target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
