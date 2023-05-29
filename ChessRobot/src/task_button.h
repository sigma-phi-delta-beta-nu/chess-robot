/** @file task_button.h
 *  This is the header file for the done move button.
 * 
 *  @author Corey Agena
 *  @date   2023-Feb-23
 */

#ifndef _TASK_BUTTON_H_
#define _TASK_BUTTON_H_

/** @brief   Task which implements the done move button.
 *  @details This task looks for a button press and communicates
 *           the flag to the rest of the system.
 */
void task_button (void* p_params);

#endif // _TASK_BUTTON_H_