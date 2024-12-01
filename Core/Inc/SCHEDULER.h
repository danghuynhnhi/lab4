/*
 * scheduler.h
 *
 *  Created on: Dec 1, 2024
 *      Author: DELL
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

#define SCH_MAX_TASKS 10
#define NO_TASK_ID 0xFFFFFFFF

typedef struct {
    void (*pTask)(void);
    uint32_t delay;
    uint32_t period;
    uint8_t runMe;
    uint32_t taskID;
} sTask;

void SCH_Init(void);
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD);
uint8_t SCH_Delete_Task(uint32_t TASKID);
void SCH_Update(void);
void SCH_Dispatch_Task(void);

#endif /* INC_SCHEDULER_H_ */
