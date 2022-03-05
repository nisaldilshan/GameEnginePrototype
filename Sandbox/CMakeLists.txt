################################
########## SANDBOX APP #########
################################
add_executable (sandbox 
                    src/ParticleSystem.cpp
                    src/SandboxApp.cpp
                    src/Sandbox2D.cpp           
                )
target_include_directories(sandbox PRIVATE ../Hazel)

#set_property(TARGET sandbox PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
#message("-- MSVC_RUNTIME_LIBRARY - sandbox = MultiThreaded$<$<CONFIG:Debug>:Debug>")

target_link_libraries(sandbox PRIVATE engine)

set_target_properties(sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/bin/Sandbox/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/bin/Sandbox/Release"
    RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO "${CMAKE_BINARY_DIR}/bin/Sandbox/RelWithDebInfo"
    RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL "${CMAKE_BINARY_DIR}/bin/Sandbox/MinSizeRel"
)

get_target_property(SANDBOX_SOURCE_DIR sandbox SOURCE_DIR)
add_custom_command(TARGET sandbox POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${SANDBOX_SOURCE_DIR}/assets $<TARGET_FILE_DIR:sandbox>/assets)



