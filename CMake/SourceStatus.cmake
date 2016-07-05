if(EXISTS "${PROJECT_SOURCE_DIR}/.hg")
find_package(Mercurial)
if(Mercurial_FOUND)
  message(STATUS "Repository status :")
  Mercurial_WC_IDENTIFY(${PROJECT_SOURCE_DIR} OTB)
  message(STATUS "  Mercurial version is ${Mercurial_VERSION_HG}")
  message(STATUS "  Repository revision is ${OTB_WC_REVISION}")
  set(OTB_WC_REVISION ${OTB_WC_REVISION} CACHE STRING "Repository version" FORCE)
  mark_as_advanced(OTB_WC_REVISION)
  if(OTB_WC_STATUS)
    message(STATUS "  Local file modifications:")
    string(REPLACE "\n" "\n--     " OTB_WC_STATUS_PRETTYPRINT "    ${OTB_WC_STATUS}")
    message(STATUS "${OTB_WC_STATUS_PRETTYPRINT}")
  else()
    message(STATUS "  No files modified locally")
  endif()
  string(REGEX REPLACE "\n" ";" OTB_WC_STATUS "${OTB_WC_STATUS}")
  set(OTB_WC_STATUS ${OTB_WC_STATUS} CACHE STRING "Repository status" FORCE)
  mark_as_advanced(OTB_WC_STATUS)
endif()
endif()

if(EXISTS "${PROJECT_SOURCE_DIR}/.git")
  find_package(Git)
  if(GIT_FOUND)
    execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H --oneline
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE OTB_GIT_LAST_COMMIT
      OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

    #git symbolic-ref --short -q HEAD does not work on older git version
    #rather than checking for git version. it is better to not use that
    #option and employ cmake stuff to do the work
    execute_process(COMMAND ${GIT_EXECUTABLE} symbolic-ref -q HEAD
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE OTB_GIT_SYMBOLIC_REF_OUTPUT
      OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

    get_filename_component(OTB_GIT_BRANCH ${OTB_GIT_SYMBOLIC_REF_OUTPUT} NAME)

    execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE OTB_WC_REVISION
      OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    execute_process(COMMAND ${GIT_EXECUTABLE} status -s
      WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
      OUTPUT_VARIABLE OTB_WC_STATUS
      OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
    message(STATUS "Repository status :")
    message(STATUS "  Repository revision is ${OTB_WC_REVISION}")
    if(OTB_WC_STATUS)
      message(STATUS "  Local file modifications:")
      string(REPLACE "\n" "\n--     " OTB_WC_STATUS_PRETTYPRINT "    ${OTB_WC_STATUS}")
      message(STATUS "${OTB_WC_STATUS_PRETTYPRINT}")
    else()
      message(STATUS "  No files modified locally")
    endif()
  endif()
endif()

if(OTB_DATA_ROOT)
  if(EXISTS "${OTB_DATA_ROOT}/.hg")
    if(NOT Mercurial_FOUND)
      find_package(Mercurial)
    endif()
    if(Mercurial_FOUND)
      Mercurial_WC_IDENTIFY(${OTB_DATA_ROOT} OTB_DATA)
      set(OTB_DATA_WC_REVISION ${OTB_DATA_WC_REVISION} CACHE STRING "Repository version" FORCE)
      mark_as_advanced(OTB_DATA_WC_REVISION)
    endif()
  endif()

  if(EXISTS "${OTB_DATA_ROOT}/.git")
    if(NOT GIT_FOUND)
      find_package(Git)
    endif()
    if(GIT_FOUND)
      execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%H
        WORKING_DIRECTORY ${OTB_DATA_ROOT}
        OUTPUT_VARIABLE OTB_DATA_WC_REVISION
        OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
      set(OTB_DATA_WC_REVISION ${OTB_DATA_WC_REVISION} CACHE STRING "Repository version" FORCE)
      mark_as_advanced(OTB_DATA_WC_REVISION)
    endif()
  endif()
endif()
