# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\SocialMediaApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\SocialMediaApp_autogen.dir\\ParseCache.txt"
  "SocialMediaApp_autogen"
  )
endif()
