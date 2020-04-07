#include<Windows.h>
#include<stdio.h>
#include"data.h"

extern HANDLE use;

int getMemoryInfo(char* total_memory){	
	MEMORYSTATUSEX statex;	
	statex.dwLength = sizeof(statex);
	
	int res;		
	res=GlobalMemoryStatusEx(&statex);
	
	if(!res)	return 0;
	
	double t_m=statex.ullTotalPhys/(1024.0*1024.0*1024.0);
	/////ullTotalPhys参数用于获取总的物理内存数量
	sprintf(total_memory,"%.2f",t_m);
	
	
	return 1;
} 

void getMemoryUsage(char* memory_usage){
	MEMORYSTATUSEX statex;	
	statex.dwLength = sizeof(statex);

	
	int res;		
	res=GlobalMemoryStatusEx(&statex);
	if(!res){
		sprintf(memory_usage,"Error!");
		return;
	}
		
	/////dwMemoryLoad参数用于获取内存使用率 
	sprintf(memory_usage,"%d",statex.dwMemoryLoad);

	
}
