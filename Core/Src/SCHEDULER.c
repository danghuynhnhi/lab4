#include "scheduler.h"

static sTask SCH_tasks_G[SCH_MAX_TASKS];
static uint32_t current_taskID = 1;  // ID hiện tại, bắt đầu từ 1

//Xoá tác vụ khỏi mảng khi bắt đầu
void SCH_Init(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        SCH_tasks_G[i].pTask = 0;
        SCH_tasks_G[i].delay = 0;
        SCH_tasks_G[i].period = 0;
        SCH_tasks_G[i].runMe = 0;
        SCH_tasks_G[i].taskID = NO_TASK_ID;
    }
}
//Tìm chỗ trống và thêm tác vụ
uint32_t SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].pTask == 0) {  // Tìm vị trí trống
            SCH_tasks_G[i].pTask = pFunction;
            SCH_tasks_G[i].delay = DELAY;
            SCH_tasks_G[i].period = PERIOD;
            SCH_tasks_G[i].runMe = 0;
            SCH_tasks_G[i].taskID = current_taskID++;
            return SCH_tasks_G[i].taskID;
        }
    }
    return NO_TASK_ID;  // Không còn chỗ để thêm tác vụ
}
//Tìm tác vụ theo taskId và đặt lại mặc định
uint8_t SCH_Delete_Task(uint32_t TASKID) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].taskID == TASKID) {
            SCH_tasks_G[i].pTask = 0;
            SCH_tasks_G[i].delay = 0;
            SCH_tasks_G[i].period = 0;
            SCH_tasks_G[i].runMe = 0;
            SCH_tasks_G[i].taskID = NO_TASK_ID;
            return 1;  // Xóa thành công
        }
    }
    return 0;  // Không tìm thấy tác vụ
}

void SCH_Update(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].pTask) {
            if (SCH_tasks_G[i].delay == 0) {
                SCH_tasks_G[i].runMe += 1;
                if (SCH_tasks_G[i].period > 0) {
                    SCH_tasks_G[i].delay = SCH_tasks_G[i].period;
                }
            } else {
                SCH_tasks_G[i].delay -= 1;
            }
        }
    }
}

void SCH_Dispatch_Task(void) {
    for (int i = 0; i < SCH_MAX_TASKS; i++) {
        if (SCH_tasks_G[i].runMe > 0) {
            (*SCH_tasks_G[i].pTask)();
            SCH_tasks_G[i].runMe -= 1;
            if (SCH_tasks_G[i].period == 0) {
                SCH_Delete_Task(SCH_tasks_G[i].taskID);
            }
        }
    }
}
