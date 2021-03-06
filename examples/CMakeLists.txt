if(BUILD_SHARED_LIBS)
  set(LINDBLAD_LIBRARY lindblad_shared)
else()
  set(LINDBLAD_LIBRARY lindblad_static)
endif()

set(EXAMPLES
    RabiOscillations
    EIT)
foreach(e ${EXAMPLES})
  add_executable(${e} ${e}.cpp)
  target_link_libraries(${e} ${LINDBLAD_LIBRARY})
  set_target_properties(${e} PROPERTIES COMPILE_FLAGS -DLINDBLAD_STATIC_DEFINE)
  add_test(${e} ${e})
endforeach()

set(PETSC_EXAMPLES
    SteadyStateEIT
    SteadyStateEIA
    SteadyState)
find_package(DL)
find_path(PETSC_INCLUDE_DIR petsc.h ${PETSC_DIR}/include)
message(STATUS "PETSC_INCLUDE_DIR==${PETSC_INCLUDE_DIR}")
find_library(PETSC_LIBS petsc ${PETSC_DIR}/lib)
message(STATUS "PETSC_LIBS==${PETSC_LIBS}")
if(PETSC_INCLUDE_DIR AND PETSC_LIBS)
  set (PETSC_FOUND TRUE)
  include_directories(${PETSC_INCLUDE_DIR}/mpiuni ${PETSC_INCLUDE_DIR})
endif()
if(PETSC_FOUND)
  foreach(e ${PETSC_EXAMPLES})
    add_executable(${e} ${e}.cpp)
    target_link_libraries(${e} ${LINDBLAD_LIBRARY} ${PETSC_LIBS} lapack blas pthread ${DL_LIBRARIES})
    add_test(${e} ${e})
  endforeach()
endif()

set(SCRIPTS 
    plotRabiOscillationsData.py
    scanEIT.py
    dynamicsEIT.py
    SteadyStateFromDynEIT.py
    )
file(COPY ${SCRIPTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

set(PYTHON_SCRIPT_TESTS
    dynamicsEIT
    SteadyStateFromDynEIT
   )
if(PETSC_FOUND)
  list(APPEND PYTHON_SCRIPT_TESTS scanEIT)
endif()
if(NOT WIN32)
  foreach(s ${PYTHON_SCRIPT_TESTS})
    add_test(NAME test_${s} COMMAND python ${s}.py)
  endforeach()
endif()
