#
# Arm SCP/MCP Software
# Copyright (c) 2021, Arm Limited and Contributors. All rights reserved.
#
# SPDX-License-Identifier: BSD-3-Clause
#
add_library(${SCP_MODULE_TARGET} SCP_MODULE)

target_include_directories(${SCP_MODULE_TARGET}
                           PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_sources(
    ${SCP_MODULE_TARGET}
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/mod_juno_ram.c"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/juno_wdog_ram.c")

target_link_libraries(${SCP_MODULE_TARGET} PRIVATE module-power-domain)
target_link_libraries(${SCP_MODULE_TARGET} PRIVATE module-system-power)
target_link_libraries(${SCP_MODULE_TARGET} PRIVATE module-timer)
