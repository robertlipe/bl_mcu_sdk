/**
 * @file hal_emac.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */

#ifndef __HAL_EMAC_H__
#define __HAL_EMAC_H__

#include "drv_device.h"
#include "bl702_emac.h"
#include "bl702_config.h"

typedef struct emac_device {
    struct device parent;
    uint8_t mac_addr[6]; /*!< mac address */
} emac_device_t;

/**
 *  @brief EMAC PHY configuration type definition
 */
typedef struct
{
    uint8_t auto_negotiation; /*!< Speed and mode auto negotiation */
    uint8_t full_duplex;      /*!< Duplex mode */
    uint16_t speed;           /*!< Speed mode */
    uint16_t phy_address;     /*!< PHY address */
} emac_phy_cfg_t;

#define EMAC_TX_COMMON_FLAGS (EMAC_BD_FIELD_MSK(TX_RD) |  \
                              EMAC_BD_FIELD_MSK(TX_IRQ) | \
                              EMAC_BD_FIELD_MSK(TX_PAD) | \
                              EMAC_BD_FIELD_MSK(TX_CRC))

#define EMAC_RX_COMMON_FLAGS    (ETH_MAX_PACKET_SIZE << 16) | \
    EMAC_BD_FIELD_MSK(RX_IRQ) )

typedef enum _BD_TYPE_ {
    EMAC_BD_TYPE_INVLAID,
    EMAC_BD_TYPE_TX,
    EMAC_BD_TYPE_RX,
    EMAC_BD_TYPE_NONE,
    EMAC_BD_TYPE_MAX = 0x7FFFFFFF
} EMAC_BD_TYPE_e;

int32_t emac_init(emac_device_t *emac_cfg);
int emac_bd_init(uint8_t *ethTxBuff, uint8_t txBufCount, uint8_t *ethRxBuff, uint8_t rxBufCount);
int emac_bd_tx_enqueue(uint32_t flags, uint32_t len, const uint8_t *data_in);
int emac_bd_rx_dequeue(uint32_t flags, uint32_t *len, uint8_t *data_out);
__WEAK void emac_rx_done_callback_app(void);
__WEAK void emac_rx_error_callback_app(void);
__WEAK void emac_rx_busy_callback_app(void);
__WEAK void emac_tx_error_callback_app(void);
__WEAK void emac_tx_done_callback_app(void);
int emac_phy_set_address(uint16_t phyAddress);
int emac_phy_config_full_duplex(uint8_t fullDuplex);
int emac_phy_reg_read(uint16_t phyReg, uint16_t *regValue);
int emac_phy_reg_write(uint16_t phyReg, uint16_t regValue);
int emac_stop(void);
int emac_start(void);

#endif
