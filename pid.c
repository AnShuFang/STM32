#include <stdio.h> 
//定义全局变量 
struct PID_TypeDef
{
	float err;
	float err_last;
	float err_sum;
	float kp,ki,kd;
	float setingspeed;
	float realspeed;
	float voltagevalue;
	float Kpout;
	float Kiout;
	float Kdout;
}pid;
 void PID_Init(void) //初始化pid参数 
 {
 	pid.err=0;
 	pid.err_last=0;
 	pid.err_sum=0;
 	pid.ki=0.015;
 	pid.kd=0.2;
 	pid.kp=0.2;
 	pid.realspeed=0;
 	pid.setingspeed=0;
 	pid.voltagevalue=0;
 	pid.Kpout=0;
 	pid.Kiout=0;
 	pid.Kdout=0;
 }
 double PID_Function(float speed) //定义PID功能 
 {
 	int index;
 	pid.setingspeed=speed;
 	pid.err=(pid.setingspeed-pid.realspeed);

 	if(pid.Kiout>=200)
 	{
 		index=0;
 		pid.Kpout=pid.kp*pid.err;
 		pid.Kiout=pid.ki*pid.err_sum;
 		pid.Kdout=pid.kd*(pid.err-pid.err_last);
 		
	 }
	 else
	 {
	 	index=1;
	 	pid.err_sum+=pid.err;
 		pid.Kpout=pid.kp*pid.err;
 		pid.Kiout=pid.ki*pid.err_sum*index;
 		pid.Kdout=pid.kd*(pid.err-pid.err_last);
	 }
	 pid.voltagevalue=pid.Kpout+pid.Kiout+pid.Kdout;
	 pid.err_last=pid.err;
	 pid.realspeed=pid.voltagevalue*1;
	 return pid.realspeed;
 	
 }
 int main() //功能实现 
 {
 	PID_Init();
	 int speed=200;
	 double realspeed;
	 int i;
	 for(i=0;i<=1000;i++) 
	 {
	 	realspeed=PID_Function(speed);
	 	printf("%f\n",realspeed);
	 }
	 printf("计算结束"); 
	 return 0;
 }
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
