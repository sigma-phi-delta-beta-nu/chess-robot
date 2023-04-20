/** @file task_y.h
 *  This is the header file for the y-axis.
 * 
 *  @author Corey Agena
 *  @date   2023-Apr-20
 */

#ifndef _TASK_Y_H_
#define _TASK_Y_H_

/** @brief   Task which implements the y-axis motor control.
 *  @details This task uses inputs from the python file and
 *           sets a position for the y-axis motor.
 */
void task_y (void* p_params);

#endif // _TASK_Y_H_