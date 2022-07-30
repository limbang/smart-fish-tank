// Copyright 2022 limbang and contributors.
//
// 此源代码的使用受 GNU AGPLv3 许可证的约束，该许可证可在"LICENSE"文件中找到。
// Use of this source code is governed by the GNU AGPLv3 license that can be found in the "LICENSE" file.

//
// Created by limbang on 2022/7/27.
//

#ifndef SMART_FISH_TANK_SENSOR_H
#define SMART_FISH_TANK_SENSOR_H

#include <driver/gpio.h>
#include <esp_err.h>

/**
 * 初始化鱼缸温度传感器
 */
void fish_tank_temperature_sensor_init();

#endif //SMART_FISH_TANK_SENSOR_H
