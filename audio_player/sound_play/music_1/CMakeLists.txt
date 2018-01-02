add_executable(music_1_play Music_1.cpp)
target_link_libraries(music_1_play ${catkin_LIBRARIES})
add_dependencies(music_1_play sound_play_gencpp)
set_target_properties(music_1_play PROPERTIES OUTPUT_NAME test)
