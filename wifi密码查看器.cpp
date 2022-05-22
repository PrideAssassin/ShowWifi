#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*
功能介绍：查看本机连接过的所有wifi密码
作者(author)：PrideAssassin
*/
#include <iostream>

int main()
{
	system("color 06");													//改变控制台颜色
	printf("功能:查看所有连接过的wifi密码\n\n");
	while (true)
	{
		printf("-----------当前设备所有连接过的wifi-------------\n\n");
		char a[25] = "\"所有用户配置文件\"";								//字符串a
		char b[100] = "netsh wlan show profile | find ";					//字符串b
		strcat_s(b, a);														//拼接字符串a和b，合成cmd指令
		system(b);															//执行cmd指令
		printf("\n\n-----------输入需要查看密码的wifi名称------------\n\n");
		char ssid[100] = {};												//字符串变量用来存放用户输入的wifi名称
		scanf_s("%s", &ssid, 100);											//获取用户输入并存入字符串变量ssid
		char order[100] = "netsh wlan show profile ";
		char password[20] = " key=clear";
		strcat_s(order, ssid);
		strcat_s(order, password);
		system("cls");
		strcat_s(order,"| find \"关键内容\"");
		printf("关键内容后面就是密码,\n如果后面什么都没有,说明密码不存在或已经被删除\n退出软件:直接右上角x掉\t\t\t\t\--PrideAssassin\n\n\n\n");
		system(order);
		printf("\n\n\n");
		system("pause&&cls");
	}
}

