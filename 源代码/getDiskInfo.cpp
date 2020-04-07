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


///////��ȡ�������� 
void putDrivesType(const char* lpRootPathName)
{
    UINT uDriverType = GetDriveType(lpRootPathName);

    switch(uDriverType) {
    case DRIVE_UNKNOWN  :snprintf(diskInfo.type,10,"δ֪�Ĵ�������"); break;
    case DRIVE_NO_ROOT_DIR: snprintf(diskInfo.type,10,"·����Ч"); break;
    case DRIVE_REMOVABLE: snprintf(diskInfo.type,10,"���ƶ�����"); break;
    case DRIVE_FIXED: snprintf(diskInfo.type,10,"�̶�����"); break;
    case DRIVE_REMOTE: snprintf(diskInfo.type,10,"�������"); break;
    case DRIVE_CDROM: snprintf(diskInfo.type,10,"����"); break;
    case DRIVE_RAMDISK: snprintf(diskInfo.type,10,"�ڴ�ӳ����"); break;
    default: snprintf(diskInfo.type,10,"Error!");break;
    }

}


//////��ȡ����������Ϣ
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
	////��ȡ�߼����������ַ��� 
	
	DWORD dwResult=GetLogicalDriveStrings(dwSize,szLogicalDrives);
	
	if(dwResult>0 && dwResult<=MAX_PATH){
		char* szSingleDrive;
		szSingleDrive=szLogicalDrives;
		/////�ӻ�������ʼ��ַ��ʼ 
		int n;
		int number=diskInfo.present-1;
		for(n=0;n<number;n++)
			szSingleDrive += (strlen(szSingleDrive)+1);
		
		
		
		putDrivesType(szSingleDrive);
			 
		putDrivesFreeSpace(szSingleDrive);
		
		snprintf(diskInfo.name,10,"%s",szSingleDrive); 
		
		
	}

	 
}


