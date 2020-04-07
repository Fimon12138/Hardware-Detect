#include<stdlib.h>
#include<stdio.h>
#include<string.h>


//////////获取操作系统版本号 

int getOSversion(char* version){
	FILE *fp;
	
	fp=_popen("ver","r");
	
	if(fp==NULL)
		return 0;
	else{
		while(fgets(version,50,fp)){
			if(version[0]!='\n')
				break;		
		}
	}
	
	_pclose(fp);
	
	version[strlen(version)-1]='\0';
	
	return 1;
} 
