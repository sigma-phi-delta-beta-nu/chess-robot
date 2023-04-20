/** @file task_z.h
 *  This is the header file for the z-axis.
 * 
 *  @author Corey Agena
 *  @date   2023-Apr-20
 */

#ifndef _TASK_Z_H_
#define _TASK_Z_H_

/** @brief   Task which implements the z-axis motor control.
 *  @details This task uses inputs from the python file and
 *           sets a position for the z-axis motor.
 */
void task_z (void* p_params);

#endif // _TASK_Z_H_