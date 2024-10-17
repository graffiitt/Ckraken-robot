cmake_minimum_required(VERSION 3.12)
project(craken_ui)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_subdirectory(io_widget)
add_subdirectory(programm)
add_subdirectory(stateManager)
add_subdirectory(devices)

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
    ${PROJECT_NAME} MACOSX_BUNDLE
    ${CPP_FILE}
    ${H_FILE}
    ${UI_FILE}
    ${QRCFILE}
    )

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} Qt6::Widgets programm_part stateManager ioWidget)
target_include_directories(${PROJECT_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

install(TARGETS ${PROJECT_NAME}
LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
BUNDLE DESTINATION . COMPONENT Runtime
RUNTIME DESTINATION bin COMPONENT Runtime
)

set(MACOSX_BUNDLE_ICON_FILE spacex)
set_source_files_properties(${MACOSX_BUNDLE_ICON_FILE} PROPERTIES
       MACOSX_PACKAGE_LOCATION "Resources")
       
file(COPY "${CMAKE_SOURCE_DIR}/resource/icon/spacex.icns"
             DESTINATION "${CMAKE_BINARY_DIR}/${PROJECT_NAME}.app/Contents/Resources")

 # Note Mac specific extension .app
set(APPS "/${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}.app")
install(CODE "include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"\" \"${DIRS}\")")
set(CPACK_GENERATOR "DragNDrop")
include(CPack)