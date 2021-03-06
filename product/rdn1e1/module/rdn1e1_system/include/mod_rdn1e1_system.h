/*
 * Arm SCP/MCP Software
 * Copyright (c) 2017-2021, Arm Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Description:
 *     RDN1E1 System Support
 */

#ifndef MOD_RDN1E1_SYSTEM_H
#define MOD_RDN1E1_SYSTEM_H

#include <mod_power_domain.h>

/*!
 * \addtogroup GroupRDN1E1Module RDN1E1 Product Modules
 * \{
 */

/*!
 * \defgroup GroupRDN1E1System RDN1E1 System Support
 * \{
 */

/*!
 * \brief Additional RDN1E1 system power states.
 */
enum mod_rdn1e1_system_power_states {
    MOD_RDN1E1_SYSTEM_POWER_STATE_SLEEP0 = MOD_PD_STATE_COUNT,
    MOD_RDN1E1_SYSTEM_POWER_STATE_SLEEP1,
    MOD_RDN1E1_SYSTEM_POWER_STATE_COUNT
};

/*!
 * \brief System power state masks.
 */
enum mod_rdn1e1_system_power_state_masks {
    MOD_RDN1E1_SYSTEM_POWER_STATE_SLEEP0_MASK =
        (1 << MOD_RDN1E1_SYSTEM_POWER_STATE_SLEEP0),
    MOD_RDN1E1_SYSTEM_POWER_STATE_SLEEP1_MASK =
        (1 << MOD_RDN1E1_SYSTEM_POWER_STATE_SLEEP1),
};

/*!
 * \brief Indices of the interfaces exposed by the module.
 */
enum mod_rdn1e1_system_api_idx {
    /*! API index for the driver interface of the SYSTEM POWER module */
    MOD_RDN1E1_SYSTEM_API_IDX_SYSTEM_POWER_DRIVER,

    /*! Number of exposed interfaces */
    MOD_RDN1E1_SYSTEM_API_COUNT
};

/*!
 * \}
 */

/*!
 * \}
 */

#endif /* MOD_RDN1E1_SYSTEM_H */
