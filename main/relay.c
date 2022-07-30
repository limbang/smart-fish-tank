// Copyright 2022 limbang and contributors.
//
// 此源代码的使用受 GNU AGPLv3 许可证的约束，该许可证可在"LICENSE"文件中找到。
// Use of this source code is governed by the GNU AGPLv3 license that can be found in the "LICENSE" file.

//
// Created by limbang on 2022/7/27.
//

#include "relay.h"

#define CHILLER_RELAY_GPIO CONFIG_CHILLER_RELAY_GPIO

esp_err_t set_chiller_relay_level(uint32_t level) {
    return gpio_set_level(CHILLER_RELAY_GPIO, level);
}

void chiller_relay_init() {
    // 初始化引脚为输出模式,并关闭继电器
    gpio_set_direction(CHILLER_RELAY_GPIO, GPIO_MODE_OUTPUT);
    gpio_set_level(CHILLER_RELAY_GPIO, !CHILLER_RELAY_LEVEL);
}