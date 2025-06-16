/*
 * state_machine.h
 *
 *  Created on: Jun 16, 2025
 *      Author: joshuawalker
 */

#ifndef INC_STATE_MACHINE_H_
#define INC_STATE_MACHINE_H_

typedef enum {
	STM32_IDLE,
	STM32_MEASURE,
	STM32_DATA_READY,
	STM32_INIT
}StateMachine_Enum;

typedef struct {
	StateMachine_Enum stm32_state;
} Stm32State_TypeDef;

void state_machine_init(Stm32State_TypeDef* stm32_state);
void state_machine_update_state(Stm32State_TypeDef* stm32_state, StateMachine_Enum new_state);

#endif /* INC_STATE_MACHINE_H_ */
