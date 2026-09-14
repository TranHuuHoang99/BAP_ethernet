cmake_minimum_required(VERSION 3.22)
project(asg_client)

SET(BAP_SRC_DIR ../BAP)
SET(BAPGEN_DIR ../ASGLarge)
# SET(BAPGEN_DIR ../backup/ASG)

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

# BAP source
###bap_stack###
SET( BAP_SRC
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

### BAPgen Output###
SET(BAPGEN_SRC 
    ${BAPGEN_DIR}/BAP_SW1.12_ICC_MQBevo_V2_187_asg.c
    ${BAPGEN_DIR}/palb_cfg.c
)

file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h")
file(GLOB_RECURSE ALL_SOURCES "src/*.cpp" "src/*.c")

SET(APPL_SRC ${ALL_SOURCES})

include_directories (
    ### Bap Headers ###
    ${BAP_SRC_DIR}/bal
    ${BAP_SRC_DIR}/bcl
    ${BAP_SRC_DIR}/bpl
    ${BAP_SRC_DIR}/debug
    ${BAP_SRC_DIR}/include
    ${BAP_SRC_DIR}/integration
    ${BAP_SRC_DIR}/util
    ${BAP_SRC_DIR}/palb
    ### BAP Gen ###
	${BAPGEN_DIR}
    ### BAP Application ###
    ${LOCAL_HEADER}/manager
    ${LOCAL_HEADER}/handler
    ${LOCAL_HEADER}/util
    ../include
)

add_executable(${PROJECT_NAME} 
    ${BAP_SRC} 
    ${BAPGEN_SRC} 
    ${APPL_SRC}
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME}
        ws2_32
        wsock32
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
        "${CMAKE_CURRENT_SOURCE_DIR}/inc"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc/manager"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc/handler"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc/common"
        "${CMAKE_CURRENT_SOURCE_DIR}/inc/util"
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17 c_std_11)

install(TARGETS ${PROJECT_NAME} DESTINATION bin/)
