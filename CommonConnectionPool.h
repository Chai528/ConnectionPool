#pragma once
using namespace std;
#include "Connection.h"
#include <string>
#include <queue>
#include <mutex> 
#include <atomic>
#include <thread>
#include <memory>
#include <functional> // ����bind
#include <condition_variable>  //������������֮���ͨ������     ��������  
/*
ʵ�����ӳع���ģ��
*/
class ConnectionPool
{
public:
	//��ȡ���ӳض���ʵ��
	static ConnectionPool* getConnectionPool();  // ��������������

	//���ⲿ�ṩ�ӿڣ� �����ӳ��л�ȡһ�����õĿ�������
	shared_ptr<Connection> getConnection();

private:
	// ����ģʽ #1 ���캯��˽�л�
	ConnectionPool(); 

	//�������ļ��м���������
	bool loadConfigFile();

	//�����ڶ������߳��� �� ר�Ÿ�������������
	void produceConnectionTask();

	//ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ж������ӵĻ���
	void scannerConnectionTask();

	string _ip; // mysql ��ip ��ַ
	unsigned short _port;  //mysql �Ķ˿ں�
	string _username;  //mysql ��¼�û���
	string _password;  //mysql ��¼����
	string _dbname; // ���ӵ����ݿ�����
	int _initSize;  //���ӳصĳ�ʼ������
	int _maxSize;  // ���ӳص����������
	int _maxIdleTime; // ���ӳ� ������ʱ��
	int _connectionTimeout; //���ӳ� ��ȡ���� �ĳ�ʱʱ��

	queue<Connection*> _connectionQue;  //�洢mysql ���ӵĶ���
	mutex _queueMutex;  // ά�����Ӷ��е��̰߳�ȫ������
	atomic_int _connectionCnt; // ��¼������������connection�������� �����ܳ���_maxSize ,�������̰߳�ȫ
	condition_variable cv;  //������������ ���������������߳� �� ���������̵߳� ͨ��
};

