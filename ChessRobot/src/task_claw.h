/** @file task_claw.h
 *  This is the header file for the claw.
 * 
 *  @author Corey Agena
 *  @date   2023-Apr-20
 */

#ifndef _TASK_CLAW_H_
#define _TASK_CLAW_H_

/** @brief   Task which implements the claw servo motor control.
 *  @details This task uses inputs from the python file and
 *           sets a position for the claw servo motor.
 */
void task_claw (void* p_params);

#endif // _TASK_CLAW_H_