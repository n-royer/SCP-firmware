/*
 * Arm SCP/MCP Software
 * Copyright (c) 2019-2020, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "sgm775_scmi.h"

#include <mod_resource_perms.h>
#include <mod_scmi_std.h>

#include <fwk_element.h>
#include <fwk_id.h>
#include <fwk_macros.h>
#include <fwk_module.h>
#include <fwk_module_idx.h>

/*!
 * If the agent wants to modify permissions at run-time these tables
 * must be allocated in writable memory.
 */

#define AGENT_IDX(agent_id) (agent_id - 1)

static struct mod_res_agent_protocol_permissions
    agent_protocol_permissions[] = {
    [AGENT_IDX(SCMI_AGENT_ID_OSPM)] = {
        .protocols = MOD_RES_PERMS_SCMI_ALL_PROTOCOLS_ALLOWED,
    },

    /* PSCI agent has no access to clock protocol */
    [AGENT_IDX(SCMI_AGENT_ID_PSCI)] = {
        .protocols = MOD_RES_PERMS_SCMI_CLOCK_PROTOCOL_DENIED,
    },
};

/*
 * Messages have an index offset from 0x3 as all agents can access
 * the VERSION/ATTRIBUTES/MSG_ATTRIBUTES messages for all
 * protocols, hence message 0x3 maps to bit[0], message 0x4 maps
 * to bit[1], etc.
 */
static struct mod_res_agent_msg_permissions agent_msg_permissions[] = {
    [AGENT_IDX(SCMI_AGENT_ID_OSPM)] = {
        /* Example, Base, disable unused msg 12 */
        .messages[MOD_RES_PERMS_SCMI_BASE_MESSAGE_IDX] = 0x0,
        /* Power Domain */
        .messages[MOD_RES_PERMS_SCMI_POWER_DOMAIN_MESSAGE_IDX] = 0x0,
        /* System Power Domain */
        .messages[MOD_RES_PERMS_SCMI_SYS_POWER_MESSAGE_IDX] = 0x0,
        /* Performance */
        .messages[MOD_RES_PERMS_SCMI_PERF_MESSAGE_IDX] = 0x0,
        /*
         * sgm775 denies access to CONFIG_SET
         */
        .messages[MOD_RES_PERMS_SCMI_CLOCK_MESSAGE_IDX] =
            MOD_RES_PERMS_ACCESS_DENIED <<
            (MOD_SCMI_CLOCK_CONFIG_SET - MOD_SCMI_CLOCK_ATTRIBUTES),
        /* Sensors */
        .messages[MOD_RES_PERMS_SCMI_SENSOR_MESSAGE_IDX] = 0x0,
        /* Reset Domains */
        .messages[MOD_RES_PERMS_SCMI_RESET_DOMAIN_MESSAGE_IDX] = 0x0,
    },
    [AGENT_IDX(SCMI_AGENT_ID_PSCI)] = {
        .messages[0] = 0x0, /* Base */
        .messages[1] = 0x0, /* Power Domain */
        .messages[2] = 0x0, /* System Power Domain */
        .messages[3] = 0x0,
        /*
         * sgm775 denies access to CONFIG_SET
         */
        .messages[4] =
            (1 << (MOD_SCMI_CLOCK_CONFIG_SET - MOD_SCMI_CLOCK_ATTRIBUTES)),
        .messages[5] = 0x0, /* Sensors */
    },
};

static struct mod_res_agent_permission agent_permissions = {
    .agent_protocol_permissions = agent_protocol_permissions,
    .agent_msg_permissions = agent_msg_permissions,
};

struct fwk_module_config config_resource_perms = {
    .data =
        &(struct mod_res_resource_perms_config){
            .agent_permissions = (uintptr_t)&agent_permissions,
            .agent_count = SCMI_AGENT_ID_COUNT,
            .protocol_count = 6,
        },
};
