cmake_minimum_required(VERSION 3.12)
set(PROJECT comment_cmd)
 
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

add_library( 
    ${PROJECT} STATIC
    ../icommand.h
    ../icommand.cpp
    ../icommandform.h
    ${CPP_FILE}
    ${H_FILE}
    ${UI_FILE}
    )

target_link_libraries(${PROJECT} ${catkin_LIBRARIES} Qt5::Widgets)
target_include_directories(${PROJECT} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
