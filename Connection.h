#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;
#include "public.h"
#include <ctime> // ��¼����ʱ��
// ���ݿ������
class Connection
{
public:
	// ��ʼ�����ݿ�����
	Connection();
	// �ͷ����ݿ�������Դ
	~Connection();

	// �������ݿ�
	bool connect(string ip,
		unsigned short port,
		string user,
		string password,
		string dbname);  //ѡ������ݿ�����

	// ���²��� insert��delete��update
	bool update(string sql);
	// ��ѯ���� select
	MYSQL_RES* query(string sql);

	//ˢ��һ�����ӵ� ��ʼ����ʱ��
	void refreshAliveTime() { _alivetime = clock(); }
	//���ش���ʱ��
	clock_t getAliveTime() const { return clock() - _alivetime; }

private:
	MYSQL* _conn; // ��ʾ��MySQL Server��һ������
	clock_t _alivetime; //��¼�������ʱ��״̬��� ��ʼ���ʱ��
};