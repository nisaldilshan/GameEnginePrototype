################################
############ EDITOR ############
################################
add_executable (editor 
                    src/EditorApp.cpp
                    src/EditorLayer.cpp           
                )
target_include_directories(editor PRIVATE ../Hazel)

#set_property(TARGET sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#message("-- MSVC_RUNTIME_LIBRARY - sandbox = MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(editor PRIVATE engine)

set_target_properties(editor PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Editor/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Editor/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/Editor/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin/Editor/MinSizeRel"
)

get_target_property(EDITOR_SOURCE_DIR editor SOURCE_DIR)
add_custom_command(TARGET editor POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${EDITOR_SOURCE_DIR}/assets $<TARGET_FILE_DIR:editor>/assets)




################################
############ EDITOR-ECS ############
################################
add_compile_definitions(EDITOR_ECS)
add_executable (editor-ecs 
                    src/EditorApp.cpp
                    src/EditorLayerECS.cpp    
                    src/Panels/SceneHierarchyPanel.cpp
                    src/Panels/ContentBrowserPanel.cpp       
                )
target_include_directories(editor-ecs PRIVATE ../Hazel)

#set_property(TARGET sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#message("-- MSVC_RUNTIME_LIBRARY - sandbox = MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(editor-ecs PRIVATE engine)

set_target_properties(editor-ecs PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/EditorECS/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/EditorECS/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/EditorECS/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin/EditorECS/MinSizeRel"
)

get_target_property(EDITOR_ECS_SOURCE_DIR editor-ecs SOURCE_DIR)
add_custom_command(TARGET editor-ecs POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${EDITOR_ECS_SOURCE_DIR}/assets $<TARGET_FILE_DIR:editor-ecs>/assets)
add_custom_command(TARGET editor-ecs POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                        ${EDITOR_ECS_SOURCE_DIR}/Resources $<TARGET_FILE_DIR:editor-ecs>/Resources)
