project(${LAPACK_LIBRARY} C)

if(UNIX)
  if(CMAKE_COMPILER_IS_GNUCXX OR CV_ICC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  endif()
endif()

set(LAPACK_MAJOR_VERSION 3 PARENT_SCOPE)
set(LAPACK_MINOR_VERSION 2 PARENT_SCOPE)
set(LAPACK_PATCH_VERSION 1 PARENT_SCOPE)

if(WIN32 AND MSVC)
  add_definitions(-DMSDOS -DNO_ISATTY)
endif()

file(GLOB lib_srcs src/*.c blas/*.c install/*.c f2c/*.c)
file(GLOB lib_incs include/*.h)

add_library(${LAPACK_LIBRARY} STATIC ${lib_srcs} ${lib_incs})
vp_target_include_directories(${LAPACK_LIBRARY} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(ENABLE_SOLUTION_FOLDERS)
  set_target_properties(${LAPACK_LIBRARY} PROPERTIES FOLDER "3rdparty")
endif()

set_target_properties(${LAPACK_LIBRARY}
  PROPERTIES OUTPUT_NAME ${LAPACK_LIBRARY}
  DEBUG_POSTFIX "${VISP_DEBUG_POSTFIX}"
  COMPILE_PDB_NAME ${LAPACK_LIBRARY}
  COMPILE_PDB_NAME_DEBUG "${LAPACK_LIBRARY}${VISP_DEBUG_POSTFIX}"
  ARCHIVE_OUTPUT_DIRECTORY ${VISP_3P_LIBRARY_OUTPUT_PATH}
  )

if(NOT BUILD_SHARED_LIBS)
  vp_install_target(${LAPACK_LIBRARY} EXPORT VISPModules ARCHIVE DESTINATION ${VISP_3P_LIB_INSTALL_PATH} COMPONENT dev)
endif()

if(MSVC)
  # Disable Visual C++ warnings
  foreach(f ${lib_srcs})
    vp_set_source_file_compile_flag(${f} /wd"4244" /wd"4267" /wd"4273" /wd"4554" /wd"4996")
  endforeach()
  vp_set_source_file_compile_flag(f2c/pow_ii.c /wd"4723")
else()
  foreach(f ${lib_srcs})
    vp_set_source_file_compile_flag(${f} -Wno-logical-op-parentheses -Wno-shift-op-parentheses -Wno-parentheses -Wno-format-extra-args -Wno-format)
  endforeach()
endif()