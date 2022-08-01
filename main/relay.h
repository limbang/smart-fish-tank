// Copyright 2022 limbang and contributors.
//
// 此源代码的使用受 GNU AGPLv3 许可证的约束，该许可证可在"LICENSE"文件中找到。
// Use of this source code is governed by the GNU AGPLv3 license that can be found in the "LICENSE" file.

//
// Created by limbang on 2022/7/27.
//

#ifndef SMART_FISH_TANK_RELAY_H
#define SMART_FISH_TANK_RELAY_H

#include <driver/gpio.h>
#include <esp_err.h>

#define CHILLER_RELAY_LEVEL CONFIG_CHILLER_RELAY_LEVEL
#define LIGHT_RELAY_LEVEL CONFIG_LIGHT_RELAY_LEVEL
#define FILTER_RELAY_LEVEL CONFIG_FILTER_RELAY_LEVEL
#define LOW_LEVEL 0
#define HIGH_LEVEL 1

/**
 * 设置冷水机继电器电平
 * @param level 电平
 * @return 成功返回 ESP_OK
 */
esp_err_t set_chiller_relay_level(uint32_t level) ;

/**
 * 初始化冷水机继电器
 */
void chiller_relay_init();

/**
 * 设置灯光继电器电平
 * @param level 电平
 * @return 成功返回 ESP_OK
 */
esp_err_t set_light_relay_level(uint32_t level);

/**
 * 初始化灯光继电器
 */
void light_relay_init();

/**
 * 设置过滤器水泵继电器电平
 * @param level 电平
 * @return 成功返回 ESP_OK
 */
esp_err_t set_filter_relay_level(uint32_t level);

/**
 * 初始过滤器水泵继电器
 */
void filter_relay_init();

#endif //SMART_FISH_TANK_RELAY_H
