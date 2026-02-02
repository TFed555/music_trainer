# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "src/CMakeFiles/trainer_1_autogen.dir/AutogenUsed.txt"
  "src/CMakeFiles/trainer_1_autogen.dir/ParseCache.txt"
  "src/audio/CMakeFiles/audio_module_autogen.dir/AutogenUsed.txt"
  "src/audio/CMakeFiles/audio_module_autogen.dir/ParseCache.txt"
  "src/audio/audio_module_autogen"
  "src/gui/CMakeFiles/gui_autogen.dir/AutogenUsed.txt"
  "src/gui/CMakeFiles/gui_autogen.dir/ParseCache.txt"
  "src/gui/gui_autogen"
  "src/log/CMakeFiles/log_module_autogen.dir/AutogenUsed.txt"
  "src/log/CMakeFiles/log_module_autogen.dir/ParseCache.txt"
  "src/log/log_module_autogen"
  "src/music/CMakeFiles/music_module_autogen.dir/AutogenUsed.txt"
  "src/music/CMakeFiles/music_module_autogen.dir/ParseCache.txt"
  "src/music/music_module_autogen"
  "src/trainer_1_autogen"
  )
endif()
