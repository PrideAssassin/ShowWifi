#include<stdio.h>
#include<stdlib.h>
#include<string>
#include <iostream>
#include<vector>

#define WIFI_NAME_LENGTH 240
using namespace std;

void describe();
void get_name();
void get_password(int);
void no_wifi();
vector<string> wifi_name;

FILE* file;											//获取命令输出流
char line[WIFI_NAME_LENGTH];							//获取一行的长度
string name;
string password;
char buf[250];

int main()
{
	describe();									// 程序描述信息
	system("color 06");							//改变控制台颜色

	// 运行流程
	while (true)
	{
		cout << "-----------当前设备所有连接过的wifi-------------\n" << endl;
		get_name();																		// 获取wifi列表
		no_wifi();																		// 当前没有获取到wifi列表
		int serial = 0;
		cout << "\n\n选择需要查看密码的wifi: " << endl;
		cin >> serial;																	// 选择wifi
		get_password(serial);															// 显示密码
	}
	return 0;
}

// 对软件的描述和使用
void describe() {
	cout << "\
				  ShowWifi\n\n\
		          简介：查看本机连接过的wifi密码。\n\
		          版本：v1.3\n\
		          作者：PrideAssassin\n\n\n\n"
		<< endl;
}

// 获取连接过的wifi列表
void get_name()
{
	const char* wifi_history = "netsh wlan show profiles | find \"配置文件 : \" ";				   // cmd命令字符串
	int x = 0;																								// wifi序号
	file = _popen(wifi_history, "r");														//使用popen执行命令，获取命令输出
	while (fgets(buf, WIFI_NAME_LENGTH, file) != NULL)
	{
		x++;
		char* pc = strstr(buf, ": ");
		string aa = (string)pc;
		string sub1 = aa.substr(2);
		sub1.pop_back();
		cout << x << ". " << sub1 << endl;																// 显示wifi列表
		wifi_name.push_back(sub1);
	}
}

// 获取所选wifi的密码
void get_password(int serial)
{
	--serial;											// 自减1
	if (serial < 0 || serial >= wifi_name.size())
	{
		cout << "\
					--------------------------------------\n\
					error：请输入wifi名字前面，对应的数字\n\
					---------------------------------------\n\
			" << endl;
		wifi_name.clear();
		system("pause&&cls");
		return;
	}

	auto cmd = "netsh wlan show profiles name=\"" + wifi_name[serial] + "\" key=clear | find \"关键内容\" ";			//	cmd命令的拼接
	const char* cmd1 = cmd.c_str();																		// 将string类型转为_popen可用的c类型
	file = _popen(cmd1, "r");

	if (fgets(buf, WIFI_NAME_LENGTH, file) != NULL)
	{
		password = strrchr(buf, ' ');																//从字符串后面往前查找空格(过滤出需要的字符串)
		cout << "密码：" << password << endl;
		wifi_name.clear();
		system("pause&&cls");
	}
	else
	{
		// 判断是否存在密码
		auto temp = "netsh wlan show profiles name=\"" + wifi_name[serial] + "\" key=clear | find \"安全密钥\"";
		const char* temp1 = temp.c_str();
		auto file1 = _popen(temp1, "r");
		if (fgets(buf, WIFI_NAME_LENGTH, file1) != NULL)
		{
			const char* temp2 = strrchr(buf, ' ');
			if ((strcmp(temp2, " 存在\n")) == 0)
			{
				cout << "ERROR::请使用管理员方式运行程序！---------\n\n" << endl;
				wifi_name.clear();
				system("pause&&cls");
			}
			else
			{
				cout << "ERROR::开放网络没有密码！---------\n\n" << endl;
				wifi_name.clear();
				system("pause&&cls");
			}
		}
		else
		{
			cout << "ERROR::获取wifi名称错误！请手动参考：netsh wlan show profiles\n\n";
			wifi_name.clear();
			system("pause&&cls");
		}
	}
}

// 未能找到wifi
void no_wifi()
{
	if (wifi_name.size() == 0) {
		printf("\n--------------------------------------------------------------\n");
		printf("\n|    Error： 未找到连接过的wifi。(请确认电脑有无线网卡并且曾经连接过wifi)     \n|    请退出程序！\n");
		printf("--------------------------------------------------------------\n\n\n\n\n");
		system("pause&&cls");
		exit(0);
	}
}

