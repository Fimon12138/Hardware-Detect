#include<stdio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include"data.h"

extern DATA diskInfo;


int getdisknum(void){
	int number=0;
	
	DWORD driveInfo=GetLogicalDrives();
	while(driveInfo){
		if(driveInfo&1){
			number++;
		}
		driveInfo>>=1;
	}
	
	return number;
}


///////获取磁盘类型 
void putDrivesType(const char* lpRootPathName)
{
    UINT uDriverType = GetDriveType(lpRootPathName);

    switch(uDriverType) {
    case DRIVE_UNKNOWN  :snprintf(diskInfo.type,10,"未知的磁盘类型"); break;
    case DRIVE_NO_ROOT_DIR: snprintf(diskInfo.type,10,"路径无效"); break;
    case DRIVE_REMOVABLE: snprintf(diskInfo.type,10,"可移动磁盘"); break;
    case DRIVE_FIXED: snprintf(diskInfo.type,10,"固定磁盘"); break;
    case DRIVE_REMOTE: snprintf(diskInfo.type,10,"网络磁盘"); break;
    case DRIVE_CDROM: snprintf(diskInfo.type,10,"光驱"); break;
    case DRIVE_RAMDISK: snprintf(diskInfo.type,10,"内存映射盘"); break;
    default: snprintf(diskInfo.type,10,"Error!");break;
    }

}


//////获取磁盘容量信息
void putDrivesFreeSpace(const char* lpRootPathName)
{
    unsigned long long available,total,free;
    if(GetDiskFreeSpaceEx(lpRootPathName,(ULARGE_INTEGER*)&available,(ULARGE_INTEGER*)&total,(ULARGE_INTEGER*)&free)){
    	double av,to,fr;
		av=available/(1024.0*1024.0*1024.0); 
		to=total/(1024.0*1024.0*1024.0); 
    	
    	double percent;
    	percent=(to-av)/to*100.0; 
		
		diskInfo.total=to;
		diskInfo.usage=percent;
        
    }else{
        diskInfo.total=-1;
        diskInfo.usage=-1;
    }
} 


void getDiskInfo(void){
	DWORD dwSize=MAX_PATH;
	char szLogicalDrives[MAX_PATH]={'\0'};	
	////获取逻辑驱动器号字符串 
	
	DWORD dwResult=GetLogicalDriveStrings(dwSize,szLogicalDrives);
	
	if(dwResult>0 && dwResult<=MAX_PATH){
		char* szSingleDrive;
		szSingleDrive=szLogicalDrives;
		/////从缓冲区起始地址开始 
		int n;
		int number=diskInfo.present-1;
		for(n=0;n<number;n++)
			szSingleDrive += (strlen(szSingleDrive)+1);
		
		
		
		putDrivesType(szSingleDrive);
			 
		putDrivesFreeSpace(szSingleDrive);
		
		snprintf(diskInfo.name,10,"%s",szSingleDrive); 
		
		
	}

	 
}


