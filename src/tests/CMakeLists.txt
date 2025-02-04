#                  ReactivePlusPlus library
#
#          Copyright Aleksey Loginov 2022 - present.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          https://www.boost.org/LICENSE_1_0.txt)
#
# Project home: https://github.com/victimsnino/ReactivePlusPlus
#

file(GLOB_RECURSE FILES "test_*.cpp")

foreach(SOURCE ${FILES}) 
  get_filename_component(BASE_NAME ${SOURCE} NAME_WE)

  set(TARGET ${BASE_NAME})

  add_executable(${TARGET} ${SOURCE} mock_observer.hpp copy_count_tracker.hpp test_scheduler.hpp)
  target_link_libraries(${TARGET} PRIVATE rpp Catch2::Catch2WithMain)
  set_target_properties(${TARGET} PROPERTIES FOLDER Tests/Suites)

  add_test(NAME ${TARGET} COMMAND $<TARGET_FILE:${TARGET}> -r junit -o ${RPP_TEST_RESULTS_DIR}/${TARGET}.xml)

  if(MSVC)
    target_compile_options(${TARGET} PRIVATE /W4 /WX)
  else()
    target_compile_options(${TARGET} PRIVATE -Wall -Wextra -Wpedantic -Werror -Wconversion)
  endif()

endforeach()


