# Register the standard build
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/BpSerializer.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/Outduct.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/DTN.fpp"
)
register_fprime_module()
