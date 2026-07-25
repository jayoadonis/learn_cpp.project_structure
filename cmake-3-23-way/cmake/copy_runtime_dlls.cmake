message(STATUS "::: SRC_DLLS=[${SRC_DLLS}]")
message(STATUS "::: DEST_DIR='${DEST_DIR}'")

if(SRC_DLLS)
  file(MAKE_DIRECTORY "${DEST_DIR}")

  execute_process(
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${SRC_DLLS} "${DEST_DIR}"
    RESULT_VARIABLE out_result
  )

  if(NOT out_result EQUAL 0)
    message(FATAL_ERROR "Failed to copy runtime DLLs (exit code ${out_result})")
  endif()
endif()