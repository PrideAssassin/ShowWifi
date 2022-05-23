#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>

#define WIFI_NAME_LENGTH 240




FILE * file;											//获取命令输出流
char line[WIFI_NAME_LENGTH];							//获取一行的长度
char wifi_name[100][100] = {};							//wifi名称
char * str;
char buf[100];

int main()
{	
	

	system("color 06");																			//改变控制台颜色
	printf(
		"               ShowWifi\n\n"	
		"          简介：查看本机连接过的所有wifi密码，\n\n"
		"          说明：\n"
		"            1. 该软件一般用于笔记本；台式电脑一般都没有无线网卡没有wifi连接记录用不了\n"
		"            2. 只能在windows下使用。选择wifi序列数字时别乱输入，程序有Bug，我懒得改了！\n"
		"            3. 选择wifi序列数字时别乱输入，程序有Bug，我懒得改了！\n\n"
		"          版本：v1.0\n"
		"          作者：PrideAssassin\n\n\n\n"
		 );
	

	while (true)
	{
		printf("-----------当前设备所有连接过的wifi-------------\n\n");
									
		char wifi_history[] = "netsh wlan show profile | find \"所有用户配置文件\" ";					//cmd命令：查看曾经连接过的wifi
		int x = 0;																						//wifi序号
		
		file=_popen(wifi_history,"r");																	//使用popen执行命令，获取命令输出

		while (fgets(line, WIFI_NAME_LENGTH, file) != NULL)															
		{
			x++;
			str= strrchr(line,' ');																		//从字符串后面往前查找空格(过滤出需要的字符串)
			str = str++;																				//字符串前面有空格剔除掉
			char * find=strchr(str, '\n');																//找到字符串换行符的地址(指针)，用'\0'替换掉
			if (find)
				*find = '\0';

			printf("%d. %s\n", x, str);																	//按指定格式打印出来，供用户查看
			strcpy_s(wifi_name[x],80,str);																//将数据wifi名存入数组
																							//每存一次，数组加1，避免多个wifi名称存入同一个位置
		}
		if (x == 0) {
			printf("\n--------------------------------------------------------------\n");
			printf("\n|    Error： 未找到连接过的wifi。(请确认电脑有无线网卡并且曾经连接过wifi)     \n|    请退出程序！\n");
			printf("--------------------------------------------------------------\n\n\n\n\n");
			system("pause&&cls");
			exit(0);
		}
			

		int list = 0;																					//用来获取用户输入的序号

		printf("\n\n\n\n选择需要查看密码的wifi: ");
		scanf_s("%d",&list,100);																		//获取用户输入						
		
		char order[100] = "netsh wlan show profile ";
		char password[50] = " key=clear | find \"关键内容\" ";
		strcat_s(order, wifi_name[list]);
		strcat_s(order, password);																		//cmd：字符串命令的拼接

		file = _popen(order, "r");
		
		while (fgets(line, WIFI_NAME_LENGTH, file) != NULL)
		{
			str = strrchr(line, ' ');																//从字符串后面往前查找空格(过滤出需要的字符串)
			printf("密码：%s",str);																	//按格式打印出来
		}
		
		system("pause&&cls");
	}
	return 0;
}

