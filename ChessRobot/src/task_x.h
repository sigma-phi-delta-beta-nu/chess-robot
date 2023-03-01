/** @file task_x.h
 *  This is the header file for the x-axis.
 * 
 *  @author Corey Agena
 *  @date   2023-Feb-23
 */

#ifndef _TASK_X_H_
#define _TASK_X_H_

/** @brief   Task which implements the x-axis motor control.
 *  @details This task uses inputs from the python file and
 *           sets a position for the x-axis motor.
 */
void task_x (void* p_params);

#endif // _TASK_X_H_