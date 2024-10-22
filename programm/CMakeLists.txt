cmake_minimum_required(VERSION 3.12)
set(PROJECT programm_part)
 
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

add_subdirectory(commands/comment)
add_subdirectory(commands/time)
add_subdirectory(commands/programmChanger)
find_library(stateManager ../../stateManager)

add_library( 
    ${PROJECT} SHARED
    ${CPP_FILE}
    commands/icommand.h
    ${H_FILE}
    ${UI_FILE}
    )

target_link_libraries(${PROJECT} ${catkin_LIBRARIES} Qt6::Widgets comment_cmd time_cmd prgChanger_cmd stateManager )
target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
