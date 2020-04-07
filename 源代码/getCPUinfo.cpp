#include<Windows.h>
#include<stdio.h>
#include<tchar.h>
#include<intrin.h>

/****
////VC2005���ϲ�֧��Intrinsics�������Ͷ˰汾��֧�� 
#if _MSC_VER>=1400
#include<intrin.h>
#endif
//////////////////////////////////////////////////


#if defined(_WIN64)
/////64λ�²�֧��������࣬��ʹ��__cpuid,__cpuindex��Intrinsics����
#else	////32λ��ʹ��������� 
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
///////VC2008 SP1֮���֧��__cpuidex(��ȷ��) 

//////VC2005��֧��__cpuid 
#if _MSC_VER<1400
void __cpuid(INT32 CPUInfo[4],INT32 InfoType){
	__cpuidex(CPUInfo,InfoType,0);
}
#endif

#endif
*****/

////��ȡ������Ϣ 
int cpu_getvendor(char* pvendor){
	INT32 dwBuf[4];
	
	if(NULL==pvendor)
		return 0;
		
	__cpuid(dwBuf,0);
	
	*(INT32*)&pvendor[0]=dwBuf[1]; ///ebx,ǰ�ĸ��ַ� 
	*(INT32*)&pvendor[4]=dwBuf[3]; ///edx,�м��ĸ��ַ� 
	*(INT32*)&pvendor[8]=dwBuf[2]; ///ecx,����ĸ��ַ�
	
	pvendor[12]='\0';
	return 12; 
}


//////��ȡCPU�̱� 
int cpu_getbrand(char* pbrand){
	INT32 dwBuf[4];

	if (NULL==pbrand)	
		return 0;

	__cpuid(dwBuf,0x80000000);

	if (dwBuf[0]<0x80000004)	
		return 0;


	__cpuid((INT32*)&pbrand[0],0x80000002);	// ǰ16���ַ�
	__cpuid((INT32*)&pbrand[16],0x80000003);	// �м�16���ַ�
	__cpuid((INT32*)&pbrand[32],0x80000004);	// ���16���ַ�
	
	pbrand[48] = '\0';
	return 48;
}

///////��ȡCPU ID 
int cpu_getid(char* pid){
	INT32 dwBuf[4];
	
	__cpuid(dwBuf,0x80000004);
	
	sprintf(pid,"%08x-%08x-%08x-%08x",dwBuf[0],dwBuf[1],dwBuf[2],dwBuf[3]);
	pid[strlen(pid)]='\0';
	
	return strlen(pid);
}
