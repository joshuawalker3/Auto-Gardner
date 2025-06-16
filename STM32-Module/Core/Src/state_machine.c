/*
 * state_machine.c
 *
 *  Created on: Jun 16, 2025
 *      Author: joshuawalker
 */

#include "state_machine.h"

void state_machine_init(Stm32State_TypeDef* stm32_state) {
	stm32_state->stm32_state = STM32_INIT;
}

void state_machine_update_state(Stm32State_TypeDef* stm32_state, StateMachine_Enum new_state) {
	stm32_state->stm32_state = new_state;
}

