# ============================================================================
# Project sources
# ============================================================================

set(${PROJECT_NAME}_SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/Event.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FSM.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FSM_State.cpp
)

# ============================================================================
# Target and build options
# ============================================================================

add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_SRC_FILES})

target_link_libraries (${PROJECT_NAME} pthread)

# ============================================================================
# Installation
# ============================================================================

INSTALL (
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h*")

INSTALL(TARGETS ${PROJECT_NAME}
        DESTINATION lib
        )