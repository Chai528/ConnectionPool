#pragma once
#include <mysql.h>
#include <string>
#include <iostream>
using namespace std;
#include "public.h"
#include <ctime> // 记录空闲时间
// 数据库操作类
class Connection
{
public:
	// 初始化数据库连接
	Connection();
	// 释放数据库连接资源
	~Connection();

	// 连接数据库
	bool connect(string ip,
		unsigned short port,
		string user,
		string password,
		string dbname);  //选择的数据库名称

	// 更新操作 insert、delete、update
	bool update(string sql);
	// 查询操作 select
	MYSQL_RES* query(string sql);

	//刷新一下连接的 起始空闲时间
	void refreshAliveTime() { _alivetime = clock(); }
	//返回存活的时间
	clock_t getAliveTime() const { return clock() - _alivetime; }

private:
	MYSQL* _conn; // 表示和MySQL Server的一条连接
	clock_t _alivetime; //记录进入空闲时间状态后的 起始存活时间
};