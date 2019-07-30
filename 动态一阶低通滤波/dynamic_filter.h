/*********************************************************************************************************************
  Copyright：     NJUST_ZIJIN
  File name:      dynamic_filter.h
  Author:         徐益
  Version:        1.0
  Date:           19/7/24
  Description:    动态一阶低通滤波的调用函数
  Function List:  1. float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old);
  History:       
	              1. Date:           19/7/30
	                 Author:         徐益
	                 Modification:   代码规范性修正
*********************************************************************************************************************/

#ifndef _DYNAMIC_FILTER_H_
#define _DYNAMIC_FILTER_H_
#include "common.h"

extern float output_now;
float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old);

#endif 

