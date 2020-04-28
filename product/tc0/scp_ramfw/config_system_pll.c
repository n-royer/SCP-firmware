/*
 * Arm SCP/MCP Software
 * Copyright (c) 2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "clock_soc.h"
#include "scp_pik.h"
#include "scp_soc_mmap.h"

#include <mod_system_pll.h>

#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_macros.h>
#include <fwk_module.h>

static const struct fwk_element system_pll_element_table[] = {
    [CLOCK_PLL_IDX_CPU0] = {
        .name = "CPU_PLL_0",
        .data = &((struct mod_system_pll_dev_config) {
            .control_reg = (void *)SCP_PLL_CPU0,
            .status_reg = (void *)&SCP_PIK_PTR->PLL_STATUS[1],
            .lock_flag_mask = PLL_STATUS_CPUPLLLOCK(0),
            .initial_rate = 1750 * FWK_MHZ,
            .min_rate = MOD_SYSTEM_PLL_MIN_RATE,
            .max_rate = MOD_SYSTEM_PLL_MAX_RATE,
            .min_step = MOD_SYSTEM_PLL_MIN_INTERVAL,
        }),
    },
    [CLOCK_PLL_IDX_SYS] = {
        .name = "SYS_PLL",
        .data = &((struct mod_system_pll_dev_config) {
            .control_reg = (void *)SCP_PLL_SYSPLL,
            .status_reg = (void *)&SCP_PIK_PTR->PLL_STATUS[0],
            .lock_flag_mask = PLL_STATUS_0_SYSPLLLOCK,
            .initial_rate = 2000 * FWK_MHZ,
            .min_rate = MOD_SYSTEM_PLL_MIN_RATE,
            .max_rate = MOD_SYSTEM_PLL_MAX_RATE,
            .min_step = MOD_SYSTEM_PLL_MIN_INTERVAL,
        }),
    },
    [CLOCK_PLL_IDX_INTERCONNECT] = {
        .name = "INT_PLL",
        .data = &((struct mod_system_pll_dev_config) {
            .control_reg = (void *)SCP_PLL_INTERCONNECT,
            .status_reg = (void *)&SCP_PIK_PTR->PLL_STATUS[0],
            .lock_flag_mask = PLL_STATUS_0_INTPLLLOCK,
            .initial_rate = 2000 * FWK_MHZ,
            .min_rate = MOD_SYSTEM_PLL_MIN_RATE,
            .max_rate = MOD_SYSTEM_PLL_MAX_RATE,
            .min_step = MOD_SYSTEM_PLL_MIN_INTERVAL,
        }),
    },
    [CLOCK_PLL_IDX_DPU] = {
        .name = "DPU_PLL",
        .data = &((struct mod_system_pll_dev_config) {
            .control_reg = (void *)SCP_PLL_DISPLAY,
            .status_reg = (void *)&SCP_PIK_PTR->PLL_STATUS[0],
            .lock_flag_mask = PLL_STATUS_0_DISPLAYPLLLOCK,
            .initial_rate = 600 * FWK_MHZ,
            .min_rate = MOD_SYSTEM_PLL_MIN_RATE,
            .max_rate = MOD_SYSTEM_PLL_MAX_RATE,
            .min_step = MOD_SYSTEM_PLL_MIN_INTERVAL,
            .defer_initialization = false,
        }),
    },
    [CLOCK_PLL_IDX_PIX0] = {
        .name = "PIX0_PLL",
        .data = &((struct mod_system_pll_dev_config) {
            .control_reg = (void *)SCP_PLL_PIX0,
            .status_reg = NULL,
            .initial_rate = 594 * FWK_MHZ,
            .min_rate = 12500 * FWK_KHZ,
            .max_rate = 594 * FWK_MHZ,
            .min_step = 25 * FWK_KHZ,
            .defer_initialization = false,
        }),
    },
    [CLOCK_PLL_IDX_PIX1] = {
        .name = "PIX1_PLL",
        .data = &((struct mod_system_pll_dev_config) {
            .control_reg = (void *)SCP_PLL_PIX1,
            .status_reg = NULL,
            .initial_rate = 594 * FWK_MHZ,
            .min_rate = 12500 * FWK_KHZ,
            .max_rate = 594 * FWK_MHZ,
            .min_step = 25 * FWK_KHZ,
            .defer_initialization = false,
        }),
    },
    [CLOCK_PLL_IDX_COUNT] = { 0 }, /* Termination description. */
};

static const struct fwk_element *system_pll_get_element_table
    (fwk_id_t module_id)
{
    return system_pll_element_table;
}

const struct fwk_module_config config_system_pll = {
    .get_element_table = system_pll_get_element_table,
};
