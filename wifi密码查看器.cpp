#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <iostream>

#define WIFI_NAME_LENGTH 240

/*
功能介绍：查看本机连接过的所有wifi密码
作者(author)：PrideAssassin
*/


FILE * file;											//获取命令输出流
char line[WIFI_NAME_LENGTH];							//获取一行的长度
char wifi_name[100][100] = {};							//wifi名称
char * str;
char buf[100];

int main()
{	
	system("color 06");																			//改变控制台颜色
	printf("功能:查看所有连接过的wifi密码\n\n");
	

	while (true)
	{
		printf("-----------当前设备所有连接过的wifi-------------\n\n");
									
		char wifi_history[] = "netsh wlan show profile | find \"所有用户配置文件\" ";					//cmd命令：查看曾经连接过的wifi
		int x = 1;																						//wifi序号
		
		file=_popen(wifi_history,"r");																	//使用popen执行命令，获取命令输出

		while (fgets(line, WIFI_NAME_LENGTH, file) != NULL)															
		{
			str= strrchr(line,' ');																		//从字符串后面往前查找空格(过滤出需要的字符串)
			str = str++;																				//字符串前面有空格剔除掉
			char * find=strchr(str, '\n');																//找到字符串换行符的地址(指针)，用'\0'替换掉
			if (find)
				*find = '\0';

			printf("%d：%s\n", x, str);																	//按指定格式打印出来，供用户查看
			strcpy_s(wifi_name[x],80,str);																//将数据wifi名存入数组
			x++;																						//每存一次，数组加1，避免多个wifi名称存入同一个位置
		}


		int list = 0;																					//用来获取用户输入的序号

		printf("\n\n-----------选择需要查看密码的wifi------------\n\n");
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

