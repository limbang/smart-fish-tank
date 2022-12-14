// Copyright 2022 limbang and contributors.
//
// 此源代码的使用受 GNU AGPLv3 许可证的约束，该许可证可在"LICENSE"文件中找到。
// Use of this source code is governed by the GNU AGPLv3 license that can be found in the "LICENSE" file.

#include "sensor.h"
#include "relay.h"

void app_main(void) {
    chiller_relay_init();
    light_relay_init();
    filter_relay_init();
    fish_tank_temperature_sensor_init();
}
