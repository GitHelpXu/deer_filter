
/*********************************************************************************************************************
  Copyright:       NJUST_ZIJIN.
  FileName:        dynamic_filter.c
  Author:          ����        
  Version :        1.0          
  Date:            19/7/24
  Description:     ��̬һ�׵�ͨ�˲�
  Version:         1.0
  Function List:   1. float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old)
  Reference:       https://blog.csdn.net/qq_27334499/article/details/52186336
                   
  -------
  History:         1. Author:         ����
                      Date:           19/7/30
					  Modification:   ����淶������
*********************************************************************************************************************/


#include "dynamic_filter.h"
#include "common.h"
#include "math.h"




#define threshold_counter       30          //�˲�������ֵ����������ֵ�˲�ϵ��������
#define per_filter_k            0.2         //ÿ���˲������������˲�������ֵʱ �˲�ϵ��������ֵ

#define threshold_deviation     8           //�˲���ֵ��ֵ
#define per_counter             5           //ÿ����ǰ������֮ǰ�˲������ֵ���ڲ�ֵ��ֵʱ �˲�����������ֵ


float output_now;                           //��ǰ�˲����
uint8 pom_flag_now=0;                       //��ǰ�˲�����
float filter_k_now=0.0;                     //��ǰ�˲�ϵ��
uint16 filter_counter_now=0;                //��ǰ�˲�������




/*****************************************************************************************************************
  Function:       float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old)
  Description:    ˼·��1.�жϵ�ǰ�˲�����
                        2.�Ƚϵ�ǰ�˲�������ǰһ���˲�����
                          1��.��ͬ���˲���������1�����Ƚϲ�ֵ����������ǰһ���˲����ֵ�Ĳ�Ƿ���ڲ�ֵ��ֵ
                              �����ڲ�ֵ��ֵ���Ӵ��˲����������ۼ�ֵ����С�ڲ�ֵ��ֵ������������������˲���������
                              ��������ֵʱ���˲�ϵ�����Ӳ����˲����������㣬���յõ��˴��˲�ϵ��k
                          2��.���������˲�ϵ��Ϊ0�������ε�ǰ����ֵ�������˲�����������
                        3.�������˲�ϵ�����빫ʽ����õ�ǰ�˲����ֵ// �������ܡ����ܵȵ�����
  Calls:          // 
  Called By:      // 
  Table Accessed: // �����ʵı����������ǣ�������ݿ�����ĳ���
  Table Updated:  // ���޸ĵı����������ǣ�������ݿ�����ĳ���
  Input:          float input_now:��ǰ�ɼ�����ֵ
                  float output_old:ǰһ���˲����ֵ
				  float filter_k_old:ǰһ���˲�ϵ��k
				  uint8 pom_flag_old:ǰһ���˲�����
  Output:         // 
  Return:         float output_now:��ǰ�˲����
  Others:         // ����˵��
*****************************************************************************************************************/
float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old)
{
	/*�жϵ�ǰ�˲�����*/
	if (input_now - output_old > 0)
	{
		pom_flag_now = 1;
	}
	else if (input_now - output_old < 0)
	{
		pom_flag_now = 0;
	}
                     
	/*�˲�ϵ���ļ���*/
	if (pom_flag_now == pom_flag_old)                               //��ǰ�˲�������ǰһ���˲�������ͬʱ
	{                       
		filter_counter_now++;                                       //�˲���������1
		if (fabs(input_now - output_old) > threshold_deviation)     //��ֵ���ڲ�ֵ��ֵʱ 
		{
			filter_counter_now += per_counter;                      //�˲���������һ���ϴ�ֵ
		}
		if (filter_counter_now > threshold_counter)                 //�˲����������ڼ�����ֵ
		{         
			filter_k_now = filter_k_old + per_filter_k;             //�˲�ϵ������
			filter_counter_now = 0;                                 //�˲���������
		}   
	}
	else                                                            //��ǰ�˲�������ǰһ���˲������෴ʱ
	{                                                              
		filter_counter_now = 0;                                     //�˲���������
		filter_k_now = 0.0;                                         //�˲�ϵ�����㣨��������ǰ����ֵ��
	}
	
	output_now = filter_k_now * input_now + (1-filter_k_now) * output_old;
	return output_now;
                       
}