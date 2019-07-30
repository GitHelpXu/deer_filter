
/*********************************************************************************************************************
  Copyright:       NJUST_ZIJIN.
  FileName:        dynamic_filter.c
  Author:          徐益        
  Version :        1.0          
  Date:            19/7/24
  Description:     动态一阶低通滤波
  Version:         1.0
  Function List:   1. float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old)
  Reference:       https://blog.csdn.net/qq_27334499/article/details/52186336
                   
  -------
  History:         1. Author:         徐益
                      Date:           19/7/30
					  Modification:   代码规范性修正
*********************************************************************************************************************/


#include "dynamic_filter.h"
#include "common.h"
#include "math.h"




#define threshold_counter       30          //滤波计数阈值（超过此阈值滤波系数将增大）
#define per_filter_k            0.2         //每当滤波计数器大于滤波计数阈值时 滤波系数所加数值

#define threshold_deviation     8           //滤波差值阈值
#define per_counter             5           //每当当前输入与之前滤波输出差值大于差值阈值时 滤波计数所加数值


float output_now;                           //当前滤波输出
uint8 pom_flag_now=0;                       //当前滤波方向
float filter_k_now=0.0;                     //当前滤波系数
uint16 filter_counter_now=0;                //当前滤波计数器




/*****************************************************************************************************************
  Function:       float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old)
  Description:    思路：1.判断当前滤波方向
                        2.比较当前滤波方向与前一次滤波方向
                          1）.若同向，滤波计数器加1，并比较差值（输入量与前一次滤波输出值的差）是否大于差值阈值
                              若大于差值阈值，加大滤波计数器的累加值；若小于差值阈值，则无特殊操作；当滤波计数器达
                              到计数阈值时，滤波系数增加并且滤波计数器清零，最终得到此次滤波系数k
                          2）.若反向，则滤波系数为0（即屏蔽当前输入值）并且滤波计数器清零
                        3.将所得滤波系数代入公式，求得当前滤波输出值// 函数功能、性能等的描述
  Calls:          // 
  Called By:      // 
  Table Accessed: // 被访问的表（此项仅对于牵扯到数据库操作的程序）
  Table Updated:  // 被修改的表（此项仅对于牵扯到数据库操作的程序）
  Input:          float input_now:当前采集输入值
                  float output_old:前一次滤波输出值
				  float filter_k_old:前一次滤波系数k
				  uint8 pom_flag_old:前一次滤波方向
  Output:         // 
  Return:         float output_now:当前滤波输出
  Others:         // 其它说明
*****************************************************************************************************************/
float dynamic_filter (float input_now, float output_old, float filter_k_old, uint8 pom_flag_old)
{
	/*判断当前滤波方向*/
	if (input_now - output_old > 0)
	{
		pom_flag_now = 1;
	}
	else if (input_now - output_old < 0)
	{
		pom_flag_now = 0;
	}
                     
	/*滤波系数的计算*/
	if (pom_flag_now == pom_flag_old)                               //当前滤波方向与前一次滤波方向相同时
	{                       
		filter_counter_now++;                                       //滤波计数器加1
		if (fabs(input_now - output_old) > threshold_deviation)     //差值大于差值阈值时 
		{
			filter_counter_now += per_counter;                      //滤波计数器加一个较大值
		}
		if (filter_counter_now > threshold_counter)                 //滤波计数器大于计数阈值
		{         
			filter_k_now = filter_k_old + per_filter_k;             //滤波系数增加
			filter_counter_now = 0;                                 //滤波计数清零
		}   
	}
	else                                                            //当前滤波方向与前一次滤波方向相反时
	{                                                              
		filter_counter_now = 0;                                     //滤波计数清零
		filter_k_now = 0.0;                                         //滤波系数清零（即舍弃当前输入值）
	}
	
	output_now = filter_k_now * input_now + (1-filter_k_now) * output_old;
	return output_now;
                       
}