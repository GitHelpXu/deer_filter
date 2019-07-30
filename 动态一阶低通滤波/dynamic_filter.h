/*********************************************************************************************************************
  Copyright��     NJUST_ZIJIN
  File name:      dynamic_filter.h
  Author:         ����
  Version:        1.0
  Date:           19/7/24
  Description:    ��̬һ�׵�ͨ�˲��ĵ��ú���
  Function List:  1. float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old);
  History:       
	              1. Date:           19/7/30
	                 Author:         ����
	                 Modification:   ����淶������
*********************************************************************************************************************/

#ifndef _DYNAMIC_FILTER_H_
#define _DYNAMIC_FILTER_H_
#include "common.h"

extern float output_now;
float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old);

#endif 

