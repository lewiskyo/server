#ifndef BASESERVER_H
#define BASESERVER_H



#include "socketevent.h"

using namespace std;

class BaseServer{
public:
	BaseServer(int _loopInterval, int _port);

	// 初始化函数
	void init();
	
	// 主循环函数
	bool loop();
private:
	int loopInterval;  // 单位为毫秒

	SocketEvent* socketEvent;

};

#endif
