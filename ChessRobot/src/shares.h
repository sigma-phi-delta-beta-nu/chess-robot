/** @file shares.h
 *  This file contains extern declarations of shares and queues which are used
 *  in more than one file of a demonstration project.
 * 
 *  @author JR Ridgely
 *  @author Corey Agena
 *  @date   2021-Oct-23 Original file
 *  @date   2022-Nov-25 Edited for the Robot Arm Project by Corey Agena
 *  @copyright (c) 2021 by JR Ridgely, released under the LGPL 3.0. 
 */

#ifndef _SHARES_H_
#define _SHARES_H_

#include "taskqueue.h"
#include "taskshare.h"

// Shares which hold the position values motors and linear actuator.
extern Share<uint32_t> x_dist;
extern Share<uint32_t> y_dist;

// Flags for indicating that the position has been reached.
extern Share<uint8_t> x_flag;
extern Share<uint8_t> y_flag;

extern Share<uint8_t> z_trigger;
extern Share<uint8_t> claw_trigger;

#endif // _SHARES_H_