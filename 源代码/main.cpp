#include<graphics.h>
#include<stdio.h>
#include"data.h" 

int getOSversion(char* version);//操作系统版本 
int cpu_getvendor(char* pvendor);//cpu厂商 
int cpu_getbrand(char* pbrand);//cpu型号 
int cpu_getid(char* pid);//cpu id 
void get_cpu_usage(char* usage);//cpu实时占用率 
int getMemoryInfo(char* total_memory);//内存总容量 
void getMemoryUsage(char* memory_usage);
int getdisknum(void);
void getDiskInfo(void);
DWORD WINAPI mouse_listening(LPVOID p);

DATA diskInfo;


int main(){
	int j;
	for(j=0;j<10;j++){
		diskInfo.name[j]='\0';
		diskInfo.type[j]='\0';
	}

	initgraph(850,600);
	setbkcolor(WHITE);
	
	
	//line(250,0,250,600);
////////////////////////////////获取操作系统版本号 
	char version[50];
	int i;
	i=getOSversion(version);
	if(!i)	sprintf(version,"Error!");    
	
	setcolor(RED);
	setfont(20,0,"黑体"); 
	outtextxy(270,10,"操作系统：");
	
	setcolor(BLACK);
	setfont(15,0,"宋体"); 
	outtextxy(260,65,"版本：");
	rectangle(335,56,800,91);	
	setfont(15,0,"幼圆");
	outtextxy(344,65,version);
////////////////////////////////获取操作系统版本号	 
	
///////////////////////////////获取CPU信息 
	setcolor(RED);
	setfont(20,0,"黑体");
	outtextxy(270,115,"CPU："); 
	
	
	char szBuf[100];
	cpu_getvendor(szBuf);
	setcolor(BLACK);
	setfont(15,0,"宋体");
	outtextxy(260,155,"CPU厂商：");
	rectangle(335,146,485,181);
	setfont(15,0,"幼圆");
	outtextxy(344,155,szBuf);
	
	cpu_getbrand(szBuf);
	setfont(15,0,"宋体");
	outtextxy(260,200,"CPU型号：");
	rectangle(335,191,800,226);
	setfont(15,0,"幼圆");
	outtextxy(344,200,szBuf);
	
	cpu_getid(szBuf);
	setfont(15,0,"宋体");
	outtextxy(260,245,"CPU ID：");
	rectangle(335,236,800,271);
	setfont(15,0,"幼圆");
	outtextxy(344,245,szBuf);
	
	setfont(15,0,"宋体");
	outtextxy(650,155,"CPU占用率：");
	rectangle(740,146,790,181);
	setfont(16,0,"黑体");
	outtextxy(793,155,"%"); 

///////////////////////////////获取CPU信息 	

//////////////////////////////获取内存信息 
	char memory[10];
	int res;
	
	res=getMemoryInfo(memory);
	if(!res)	sprintf(memory,"Error!");
	
	setcolor(RED);
	setfont(20,0,"黑体"); 
	outtextxy(270,290,"内存：");
	
	setcolor(BLACK);
	setfont(15,0,"宋体");
	outtextxy(260,330,"总容量：");
	rectangle(335,321,385,356);
	setfont(15,0,"幼圆");
	outtextxy(338,330,memory); 
	setfont(16,0,"黑体");
	outtextxy(388,330,"GB");
	 

	setfont(15,0,"宋体");
	outtextxy(673,330,"占用率：");
	rectangle(740,321,790,356);
	setfont(16,0,"黑体");
	outtextxy(793,330,"%");
	
	
//////////////////////////////获取内存信息 

/////////////////////////////获取硬盘信息 
	setcolor(RED);
	setfont(20,0,"黑体"); 
	outtextxy(270,370,"硬盘：");
	
	char disk_num[50];
	int d_n=getdisknum();
	sprintf(disk_num,"共有%d个硬盘",d_n);
	setcolor(BLACK);
	setfont(15,0,"幼圆");
	outtextxy(340,375,disk_num); 
	
	diskInfo.number=d_n;
	diskInfo.present=1;
	
	setfont(15,0,"宋体");
	outtextxy(260,410,"硬盘名称：");
	rectangle(335,401,485,436);
	rectangle(650,401,800,436);
	outtextxy(575,410,"硬盘类型：");
	outtextxy(260,455,"总容量：");
	rectangle(335,446,387,481);
	setfont(16,0,"黑体");
	outtextxy(390,455,"GB");
	setfont(15,0,"宋体");
	rectangle(740,446,790,481); 
	outtextxy(673,455,"占用率：");
	setfont(16,0,"黑体");
	outtextxy(793,455,"%");
	
	PIMAGE img_1,img_2,img_3;
	img_1=newimage();
	img_2=newimage();
	img_3=newimage();
	getimage(img_1,"D:\\OSCourseWork\\left.jpg");
	getimage(img_2,"D:\\OSCourseWork\\right.jpg");
	getimage(img_3,"D:\\OSCourseWork\\bkground.jpg");
	putimage(510,500,30,30,img_1,0,0,171,153);
	putimage(560,500,30,30,img_2,0,0,168,149);
	putimage(100,104,150,494,img_3,0,0,150,489);
	
	setfont(14,0,"宋体");
	outtextxy(480,585,"*对特殊磁盘，如光驱，未作特殊处理，报Error为正常现象"); 

/////////////////////////////获取硬盘信息
	setcolor(BLACK);
	setfont(15,0,"幼圆");
	setfillcolor(WHITE);

	int pt_1[]={740,146,790,146,790,181,740,181};
	int pt_2[]={740,321,790,321,790,356,740,356};
	int pt_3[]={335,401,485,401,485,436,335,436}; 
	int pt_4[]={650,401,800,401,800,436,650,436}; 
	int pt_5[]={335,446,387,446,387,481,335,481}; 
	int pt_6[]={740,446,790,446,790,481,740,481}; 
	
	char cpu_usage[10];
	char memory_usage[10];
	char disk_total[10];
	char disk_usage[10];
	
	HANDLE hThread_4;
	hThread_4=CreateThread(NULL,0,mouse_listening,NULL,0,NULL);
	
	int number_of_disk; 
	while(1){
		get_cpu_usage(cpu_usage);
		
		getMemoryUsage(memory_usage);
		
		number_of_disk=getdisknum();
		if(number_of_disk<diskInfo.number&&diskInfo.present==diskInfo.number){//硬盘数量减少，可能为U盘拔出，如果此时显示的是U盘状态，对显示做修改 
			diskInfo.number=number_of_disk;
			diskInfo.present=diskInfo.number;//显示最后一个盘 
		} 
		else
			diskInfo.number=number_of_disk;
		setfont(15,0,"幼圆");
		outtextxy(340,375,"                        "); 
		sprintf(disk_num,"共有%d个硬盘",diskInfo.number);
		outtextxy(340,375,disk_num); 
		
		getDiskInfo();
		
		fillpoly(4,pt_1);
    	outtextxy(743,155,cpu_usage);
    	
    	fillpoly(4,pt_2);
   		outtextxy(742,330,memory_usage);
   		
   		if(diskInfo.total<0)	sprintf(disk_total,"Error!");
		else	sprintf(disk_total,"%.2f",diskInfo.total);
		if(diskInfo.usage<0)	sprintf(disk_usage,"Error!");
		else	sprintf(disk_usage,"%.2f",diskInfo.usage);
		
		fillpoly(4,pt_3);
		outtextxy(344,410,diskInfo.name);//输出名称		
		fillpoly(4,pt_4);
		outtextxy(659,410,diskInfo.type);	//输出类型
		fillpoly(4,pt_5);
		outtextxy(337,455,disk_total);			//输出总容量
		fillpoly(4,pt_6);
		outtextxy(742,455,disk_usage);//输出占用率 
		
		delay_fps(60);
		Sleep(1000);
	}


	closegraph();
}



DWORD WINAPI mouse_listening(LPVOID p){
	mouse_msg msg;
	for(;is_run();){
		
		
		msg=getmouse();
		
		switch(msg.msg){
			case mouse_msg_down:
				if(msg.x>=510&&msg.x<=540&&msg.y>=500&&msg.y<=530){
					if(diskInfo.present!=1){
						diskInfo.present--;
					}				
				}
				
				if(msg.x>=560&&msg.x<=590&&msg.y>=500&&msg.y<=530){
					if(diskInfo.present<diskInfo.number){
						diskInfo.present++;
					}
				}
				
				break;
				
			default:break;
		}
		
	}
		
}
