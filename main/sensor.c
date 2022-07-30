// Copyright 2022 limbang and contributors.
//
// 此源代码的使用受 GNU AGPLv3 许可证的约束，该许可证可在"LICENSE"文件中找到。
// Use of this source code is governed by the GNU AGPLv3 license that can be found in the "LICENSE" file.

#include <sys/cdefs.h>
//
// Created by limbang on 2022/7/27.
//

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <ds18x20.h>
#include <esp_log.h>
#include "sensor.h"
#include "relay.h"

#define DS18X20_MAX CONFIG_FISH_TANK_TEMPERATURE_SENSORS_DS18X20_MAX
#define DS18X20_GPIO CONFIG_FISH_TANK_TEMPERATURE_SENSOR_DS18X20_GPIO

static const char *TAG = "sensor";
static const int RESCAN_INTERVAL = 8;
static const uint32_t LOOP_DELAY_MS = 500;

void read_fish_tank_temperature_task(void *pvParameter) {
    ds18x20_addr_t sensor_addrs[DS18X20_MAX];
    size_t sensor_count = 0;
    // 查找总线上所有 ds18x20 设备的地址
    esp_err_t res = ds18x20_scan_devices(DS18X20_GPIO, sensor_addrs, DS18X20_MAX, &sensor_count);
    // 判断是否扫描失败或者传感器小于1
    if (res != ESP_OK) {
        ESP_LOGE(TAG, "Sensors scan error %d (%s)", res, esp_err_to_name(res));
        return;
    }
    if (!sensor_count) {
        ESP_LOGW(TAG, "No sensors detected!");
        return;
    }
    // 扫描成功
    ESP_LOGI(TAG, "%d sensors detected", sensor_count);
    // 忽略掉多的传感器
    if (sensor_count > DS18X20_MAX)
        sensor_count = DS18X20_MAX;

    // 读取温度
    uint32_t relay_level = !CHILLER_RELAY_LEVEL;
    while (true) {
        float temps[DS18X20_MAX];
        for (int i = 0; i < RESCAN_INTERVAL; i++) {
            esp_err_t res = ds18x20_measure_and_read_multi(DS18X20_GPIO, sensor_addrs, sensor_count, temps);
            if (res != ESP_OK) {
                ESP_LOGE(TAG, "Sensors read error %d (%s)", res, esp_err_to_name(res));
                continue;
            }
            // 求出平均温度
            float average_temp = 0;
            if (sensor_count != 1) {
                for (int j = 0; j < sensor_count; j++) {
                    average_temp += temps[j];
                }
                average_temp = average_temp / sensor_count;
            } else {
                average_temp = temps[0];
            }
            // 如果大于28度就开启冷水机,低于27度关闭冷水机
            if (average_temp > 28) {
                if (!relay_level) {
                    set_chiller_relay_level(HIGH_LEVEL);
                    relay_level = HIGH_LEVEL;
                }
            } else if (average_temp < 27) {
                if (relay_level) {
                    set_chiller_relay_level(LOW_LEVEL);
                    relay_level = LOW_LEVEL;
                }
            }
            ESP_LOGI(TAG, "average %f", average_temp);
        }
        vTaskDelay(pdMS_TO_TICKS(LOOP_DELAY_MS));
    }
}

void fish_tank_temperature_sensor_init() {
    // 将引脚初始化为上拉
    gpio_set_pull_mode(DS18X20_GPIO, GPIO_PULLUP_ONLY);
    // 创建读取鱼缸温度的任务
    xTaskCreate(read_fish_tank_temperature_task, "Fish tank temperature", configMINIMAL_STACK_SIZE * 4, NULL, 5, NULL);
}
