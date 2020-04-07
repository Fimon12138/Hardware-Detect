#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<intrin.h>

/****
////VC2005以上才支持Intrinsics函数，低端版本不支持 
#if _MSC_VER>=1400
#include<intrin.h>
#endif
//////////////////////////////////////////////////


#if defined(_WIN64)
/////64位下不支持内联汇编，需使用__cpuid,__cpuindex等Intrinsics函数
#else	////32位下使用内联汇编 
#if _MSC_VER<1600
void __cpuidex(INT32 CPUInfo[4],INT32 InfoType,INT32 ECXValue){
	if(NULL==CPUInfo)
		return;
	_asm{
		mov edi,CPUInfo;
		mov eax,InfoType;
		mov ecx,ECXValue;
		
		cpuid;
		
		mov [edi],eax;
		mov [edi+4],ebx;
		mov [edi+8],ecx;
		mov [edi+12],edx;
	}
}
#endif
///////VC2008 SP1之后才支持__cpuidex(不确定) 

//////VC2005才支持__cpuid 
#if _MSC_VER<1400
void __cpuid(INT32 CPUInfo[4],INT32 InfoType){
	__cpuidex(CPUInfo,InfoType,0);
}
#endif

#endif
*****/

////获取厂商信息 
int cpu_getvendor(char* pvendor){
	INT32 dwBuf[4];
	
	if(NULL==pvendor)
		return 0;
		
	__cpuid(dwBuf,0);
	
	*(INT32*)&pvendor[0]=dwBuf[1]; ///ebx,前四个字符 
	*(INT32*)&pvendor[4]=dwBuf[3]; ///edx,中间四个字符 
	*(INT32*)&pvendor[8]=dwBuf[2]; ///ecx,最后四个字符
	
	pvendor[12]='\0';
	return 12; 
}


//////获取CPU商标 
int cpu_getbrand(char* pbrand){
	INT32 dwBuf[4];

	if (NULL==pbrand)	
		return 0;

	__cpuid(dwBuf,0x80000000);

	if (dwBuf[0]<0x80000004)	
		return 0;


	__cpuid((INT32*)&pbrand[0],0x80000002);	// 前16个字符
	__cpuid((INT32*)&pbrand[16],0x80000003);	// 中间16个字符
	__cpuid((INT32*)&pbrand[32],0x80000004);	// 最后16个字符
	
	pbrand[48] = '\0';
	return 48;
}

///////获取CPU ID 
int cpu_getid(char* pid){
	INT32 dwBuf[4];
	
	__cpuid(dwBuf,0x80000004);
	
	sprintf(pid,"%08x-%08x-%08x-%08x",dwBuf[0],dwBuf[1],dwBuf[2],dwBuf[3]);
	pid[strlen(pid)]='\0';
	
	return strlen(pid);
}
