/*
 * tasks.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Administrator
 */

#include "tasks.h"

void task_0(void) {
    // Code for task 1 (LED 0)
	HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
}
void task_1(void) {
    // Code for task 1 (LED 1)
	HAL_GPIO_TogglePin(LED_1_GPIO_Port, LED_1_Pin);
}

void task_2(void) {
    // Code for task 2 (LED 2)
	HAL_GPIO_TogglePin(LED_2_GPIO_Port, LED_2_Pin);
}

void task_3(void) {
    // Code for task 3 (LED 3)
	HAL_GPIO_TogglePin(LED_3_GPIO_Port, LED_3_Pin);
}

void task_4(void) {
    // Code for task 4 (LED 4)
	HAL_GPIO_TogglePin(LED_4_GPIO_Port, LED_4_Pin);
}

void task_5(void) {
    // Code for task 5 (LED 5)
	HAL_GPIO_TogglePin(LED_5_GPIO_Port, LED_5_Pin);
}
