cmake_minimum_required(VERSION 3.22)
project(fsg_ipv6_multicast)

SET(BAP_SRC_DIR BAP)
SET(BAPGEN_DIR FSG/FsgLarge)
SET(FSG_SERVER_DIR FSG/Fsgserver)
SET(PDU_LIB_DIR libPDU_MultiPlex)

ADD_DEFINITIONS(${LSG_DEF} ${VAR_DEF} -DBAP_USES_ASSERT -DBAP_INTEGRATIONSBEISPIEL -DCYGWIN_GCC)

add_compile_options(-Wno-unused-local-typedefs)
add_compile_options(-Wno-conversion)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-error")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error")

if(WIN32)
    link_directories(C:/msys64/ucrt64/lib)
else()
    link_directories(/usr/lib)
endif()

if(MINGW OR CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
    add_link_options(-static)
endif()

# BAP core sources (matching the root FSG-Server set; excludes target-specific
# files like sw_timer.c / TC29x SFR includes and unused CAN vector backends).
###bap_stack###
SET(BAP_SRC
    ${BAP_SRC_DIR}/bal/bap_bal.c
    ${BAP_SRC_DIR}/bal/bap_balutil.c
    ${BAP_SRC_DIR}/bcl/bap_bcl.c
    ${BAP_SRC_DIR}/bcl/bap_bclcan.c
    ${BAP_SRC_DIR}/bcl/bap_bclutil.c
    ${BAP_SRC_DIR}/bpl/bap_bpl.c
    ${BAP_SRC_DIR}/bpl/bap_bplutil.c
    ${BAP_SRC_DIR}/util/bap_controller.c
    ${BAP_SRC_DIR}/debug/bap_debug.c
    ${BAP_SRC_DIR}/util/bap_util.c
    ${BAP_SRC_DIR}/palb/palb.c
)

### BAPgen Output (FSG configuration)###
SET(BAPGEN_SRC
    ${BAPGEN_DIR}/fsg.c
    ${BAPGEN_DIR}/palb_cfg.c
)

### FSG server application sources ###
file(GLOB FSG_APP_SOURCES
    "${FSG_SERVER_DIR}/src/*.cpp"
    "${FSG_SERVER_DIR}/src/*.c"
    "${FSG_SERVER_DIR}/src/handler/*.cpp"
)

### libPDU_MultiPlex sources ###
file(GLOB PDU_LIB_SOURCES "${PDU_LIB_DIR}/src/*.cpp" "${PDU_LIB_DIR}/src/*.c")

### Main entry point ###
SET(MAIN_SRC main.cpp)

include_directories(
    ### BAP Headers ###
    ${BAP_SRC_DIR}/bal
    ${BAP_SRC_DIR}/bcl
    ${BAP_SRC_DIR}/bpl
    ${BAP_SRC_DIR}/debug
    ${BAP_SRC_DIR}/include
    ${BAP_SRC_DIR}/integration
    ${BAP_SRC_DIR}/palb
    ${BAP_SRC_DIR}/util
    ### BAP Gen / FSG ###
    ${BAPGEN_DIR}
    ### FSG include ###
    FSG/include
    ### FSG server ###
    ${FSG_SERVER_DIR}/inc
    ${FSG_SERVER_DIR}/inc/common
    ${FSG_SERVER_DIR}/inc/log
    ${FSG_SERVER_DIR}/inc/handler
    ### libPDU_MultiPlex ###
    ${PDU_LIB_DIR}/include
    ### Workspace root (for "IPv6_Multicast/..." relative includes) ###
    ..
    ### Workspace-level shared ###
    ../include
)

add_executable(${PROJECT_NAME}
    ${BAP_SRC}
    ${BAPGEN_SRC}
    ${FSG_APP_SOURCES}
    ${PDU_LIB_SOURCES}
    ${MAIN_SRC}
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        ws2_32
        wsock32
        iphlpapi
        pthread
    )
else()
    target_link_libraries(${PROJECT_NAME}
        pthread
    )
endif()

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}/${FSG_SERVER_DIR}/inc"
        "${CMAKE_CURRENT_SOURCE_DIR}/${PDU_LIB_DIR}/include"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17 c_std_11)

install(TARGETS ${PROJECT_NAME} DESTINATION bin/)

set(NODE_JS_EXE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../runtime_fsg_simulation/simulation_executable_file")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${NODE_JS_EXE_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:${PROJECT_NAME}> "${NODE_JS_EXE_DIR}/"
    COMMENT "Copying compiled binary to Node.js simulation folder..."
)
