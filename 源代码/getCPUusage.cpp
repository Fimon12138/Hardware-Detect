#include<Windows.h>
#include<stdio.h>
#include<stdlib.h>


FILETIME pre_idleTime;
FILETIME pre_kernelTime;
FILETIME pre_userTime;
int n=1;


unsigned __int64 CompareFileTime2(FILETIME time1, FILETIME time2){
	
	unsigned __int64 a = ((unsigned __int64)time1.dwHighDateTime) << 32 | time1.dwLowDateTime;
	unsigned __int64 b = ((unsigned __int64)time2.dwHighDateTime) << 32 | time2.dwLowDateTime;
	return b - a;
	
} 

void get_cpu_usage(char* usage){
	FILETIME idleTime;  
    FILETIME kernelTime;  
    FILETIME userTime;
	
	unsigned __int64 idle;
	unsigned __int64 kernel;
	unsigned __int64 user;  
	
	int res; 

	if(1==n){
		res=GetSystemTimes(&pre_idleTime, &pre_kernelTime, &pre_userTime);
		if(!res){
			sprintf(usage,"Error!");
			return;
		}
		n++;	
	} 
	
    res=GetSystemTimes(&idleTime, &kernelTime, &userTime); 
    if(!res){
    	sprintf(usage,"Error!");
    	return;
	}
    
   	idle = CompareFileTime2(pre_idleTime, idleTime);  
   	kernel = CompareFileTime2(pre_kernelTime, kernelTime);  
	user = CompareFileTime2(pre_userTime, userTime);
    	
	double cpu;
    
    if(kernel+user<=0)  
        cpu=0.0;  

    ///////（总的时间-空闲时间）/总的时间=占用cpu的时间就是使用率
	double useful=kernel+user-idle+0.0;
	double total=kernel+user+0.0;  
	cpu=useful/total*100;  

    pre_idleTime = idleTime;  
   	pre_kernelTime = kernelTime;  
    pre_userTime = userTime; 	
    
    sprintf(usage,"%.2f",cpu);		
	
}
