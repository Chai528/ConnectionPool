#pragma once
using namespace std;
#include "Connection.h"
#include <string>
#include <queue>
#include <mutex> 
#include <atomic>
#include <thread>
#include <memory>
#include <functional> // 绑定器bind
#include <condition_variable>  //生产者消费者之间的通信连接     条件变量  
/*
实现连接池功能模块
*/
class ConnectionPool
{
public:
	//获取连接池对象实例
	static ConnectionPool* getConnectionPool();  // 消费者消费连接

	//给外部提供接口， 从连接池中获取一个可用的空闲连接
	shared_ptr<Connection> getConnection();

private:
	// 单例模式 #1 构造函数私有化
	ConnectionPool(); 

	//从配置文件中加载配置项
	bool loadConfigFile();

	//运行在独立的线程中 ， 专门负责生产新连接
	void produceConnectionTask();

	//扫描超过maxIdleTime时间的空闲连接，进行对于连接的回收
	void scannerConnectionTask();

	string _ip; // mysql 的ip 地址
	unsigned short _port;  //mysql 的端口号
	string _username;  //mysql 登录用户名
	string _password;  //mysql 登录密码
	string _dbname; // 连接的数据库名称
	int _initSize;  //连接池的初始连接量
	int _maxSize;  // 连接池的最大连接量
	int _maxIdleTime; // 连接池 最大空闲时间
	int _connectionTimeout; //连接池 获取连接 的超时时间

	queue<Connection*> _connectionQue;  //存储mysql 连接的队列
	mutex _queueMutex;  // 维护连接队列的线程安全互斥锁
	atomic_int _connectionCnt; // 记录连接所创建的connection连接数量 ，不能超过_maxSize ,考虑了线程安全
	condition_variable cv;  //设置条件变量 ，用于连接生产线程 和 连接消费线程的 通信
};

