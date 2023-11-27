/*
 * scheduler.c
 *
 *  Created on: Nov 23, 2023
 *      Author: Administrator
 */
#include "scheduler.h"

sTask SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_index_task = 0;

void SCH_Init(void) {
	while (current_index_task != 0) {
		SCH_Delete_Task(0);
	}
}

void SCH_Update(void){
    uint8_t Index;
    // NOTE: c alcul a tions are in *TICKS* ( not milliseconds )
    for (Index  = 0; Index < SCH_MAX_TASKS; Index++){
        // Check if there is a task at this location
        if (SCH_tasks_G[Index].pTask){
            if (SCH_tasks_G[Index].Delay == 0){
                // The task is due to run
                // Inc . the ’RunMe’ flag
                SCH_tasks_G[Index].Runme += 1;
                if (SCH_tasks_G[Index].Period){
                    // Schedule periodic tasks to run again
                    SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
                }

            } else {
                // Not yet ready to run : just decrement the delay
                SCH_tasks_G[Index].Delay -= 1;
            }
        }
    }
}

uint8_t SCH_Add_Task(void (*pFunction)(void), unsigned int DELAY, unsigned int PERIOD){
	uint8_t Index = 0;
    // First find a gap in the array (if there is one)
    while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS)){
        Index++;
    }
    // Have we reached the end of the list ?
    if (Index == SCH_MAX_TASKS){
        // Task list is f ull
        // Set the global error variable
        // Error_code_G = ERROR_SCH_TOO_MANY_TASKS;
        // Also return an error code
        return SCH_MAX_TASKS;
    }
    // I f we're here , there is a space in the task array
    SCH_tasks_G[Index].pTask = pFunction;
    SCH_tasks_G[Index].Delay = DELAY/TICK;
    SCH_tasks_G[Index].Period = PERIOD/TICK;
    SCH_tasks_G[Index].Runme = 0;
    SCH_tasks_G[Index].taskID = current_index_task;
    current_index_task++;
    // return position of task (to allow later deletion )
    return Index;
}

void SCH_Dispatch_Tasks(void){
	uint8_t Index;
    // Dispatches (runs ) the next task ( i f one i s ready )
    for (Index = 0; Index < SCH_MAX_TASKS; Index++){
        // Co task can thuc hien
        if (SCH_tasks_G[Index].Runme > 0){
            (*SCH_tasks_G[Index].pTask)(); // Run the task
            SCH_tasks_G[Index].Runme -= 1; // Reset / Reduce  Runme Flag
            // Periodic tasks will au toma tically run again
            // − i f t hi s i s a ’one shot ’ task , remove it from the array
            if (SCH_tasks_G[Index].Period == 0){
                SCH_Delete_Task(Index);
            }
        }
    }
    // // Report system status
    // SCH_Report_Status();
    // // The scheduler enters idle mode at this point
    // SCH_Go_To_Sleep();
}



uint8_t SCH_Delete_Task(const uint8_t TASK_INDEX) {
	if (TASK_INDEX>SCH_MAX_TASKS)
		return TASK_INDEX;
	// Shift left 1
	for (int i = TASK_INDEX; i < SCH_MAX_TASKS-1; i++){
		SCH_tasks_G[i].pTask = SCH_tasks_G[i+1].pTask;
		SCH_tasks_G[i].Delay = SCH_tasks_G[i+1].Delay;
		SCH_tasks_G[i].Period = SCH_tasks_G[i+1].Period;
		SCH_tasks_G[i].Runme =  SCH_tasks_G[i+1].Runme;
	}
		// Reset SCH_tasks_G[SCH_MAX_TASKS-1]
	    SCH_tasks_G[SCH_MAX_TASKS -1].pTask = 0x0000 ;
	    SCH_tasks_G[SCH_MAX_TASKS -1].Delay = 0;
	    SCH_tasks_G[SCH_MAX_TASKS -1].Period = 0;
	    SCH_tasks_G[SCH_MAX_TASKS -1].Runme = 0;
	    current_index_task--;
	return TASK_INDEX;
}
void SCH_Go_To_Sleep(){
    // todo: Optional
}

//void SCH_Report_Status(void){
//#ifdef SCH_REPORT_ERRORS
//// ONLY APPLIES IF WE ARE REPORTING ERRORS
//// Check fo r a new e r ro r code
//    if (Error_code_G != Last_error_code_G) {
//    // Negative l o gic on LEDs assumed
//        Error_port = 255 − Error_code_G ;
//        Last_error_code_G = Error_code_G ;
//        if (Error_code_G != 0) {
//            Error_tick_count_G = 60000;
//        } else {
//            Error_tick_count_G = 0;
//        }
//    } else {
//        if (Error_tick_count_G != 0){
//            if(−−Error_tick_count_G == 0) {
//                Error_code_G = 0; // Reset e r ro r code
//            }
//        }
//    }
//#endif
//}

