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


################################
############ EDITOR-ECS ############
################################
add_compile_definitions(EDITOR_ECS)
add_executable (editor-ecs 
                    src/EditorApp.cpp
                    src/EditorLayerECS.cpp           
                )
target_include_directories(editor-ecs PRIVATE ../Hazel)

#set_property(TARGET sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#message("-- MSVC_RUNTIME_LIBRARY - sandbox = MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(editor-ecs PRIVATE engine)
