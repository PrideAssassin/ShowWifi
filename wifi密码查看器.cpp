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

FILE* file;											//��ȡ���������
char line[WIFI_NAME_LENGTH];							//��ȡһ�еĳ���
string name;
string password;
char buf[250];

int main()
{
	describe();									// ��������
	system("color 06");							//�ı����̨��ɫ
	
	// ��������
	while (true)
	{
		cout << "-----------��ǰ�豸�������ӹ���wifi-------------\n" << endl;
		get_name();																		// ��ȡwifi�б�
		no_wifi();																		// ��ǰû�л�ȡ��wifi�б�
		int serial = 0;																					
		cout << "\n\nѡ����Ҫ�鿴�����wifi: " << endl;
		cin >> serial;																	// ѡ��wifi
		get_password(serial);															// ��ʾ����

	}
	
	
	

	
	return 0;
}


// �������������ʹ��
void describe() {
	cout << "\
				  ShowWifi\n\n\
		          ��飺�鿴�������ӹ���wifi���롣\n\
		          �汾��v1.2\n\
		          ���ߣ�PrideAssassin\n\n\n\n"
		<< endl;
}

// ��ȡ���ӹ���wifi�б�
void get_name()
{
	const char* wifi_history = "netsh wlan show profile | find \" �����û������ļ� \" ";				   // cmd�����ַ���
	int x = 0;																								// wifi���
	file = _popen(wifi_history, "r");														//ʹ��popenִ�������ȡ�������
	while (fgets(buf, WIFI_NAME_LENGTH, file) != NULL)
	{
		x++;
		name= strrchr(buf, ' ');																//���ַ���������ǰ���ҿո�(���˳���Ҫ���ַ���)																		
		name.erase(name.begin(), ++(name.begin()));											//ɾ���ַ���ǰ��ո�
		name.pop_back();
		cout << x << ". " << name << endl;																// ��ʾwifi�б�
		wifi_name.push_back(name);
	}
}

// ��ȡ��ѡwifi������
void get_password(int serial)
{
	--serial;
	if (serial<0||serial>=wifi_name.size())
	{
		cout << "\
					--------------------------------------\n\
					error��������wifi����ǰ�棬��Ӧ������\n\
					---------------------------------------\n\
			" << endl;
		wifi_name.clear();
		system("pause&&cls");
		return;
	}

	auto cmd = "netsh wlan show profile " + wifi_name[serial] + " key=clear | find \"�ؼ�����\" ";			//	cmd�����ƴ��
	const char* cmd1 = cmd.c_str();																		// ��string����תΪ_popen���õ�c����
	file = _popen(cmd1, "r");

	while (fgets(buf, WIFI_NAME_LENGTH, file) != NULL)
	{
		password = strrchr(buf, ' ');																//���ַ���������ǰ���ҿո�(���˳���Ҫ���ַ���)
		cout << "���룺" << password << endl;
		wifi_name.clear();
		system("pause&&cls");
	}
}

// δ���ҵ�wifi
void no_wifi() 
{
	if (wifi_name.size() == 0) {
		printf("\n--------------------------------------------------------------\n");
		printf("\n|    Error�� δ�ҵ����ӹ���wifi��(��ȷ�ϵ������������������������ӹ�wifi)     \n|    ���˳�����\n");
		printf("--------------------------------------------------------------\n\n\n\n\n");
		system("pause&&cls");
		exit(0);
	}
}

