#ifndef SOCKETEVENT_H
#define SOCKETEVENT_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <event.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <string.h>
#include <event.h>
#include <sys/types.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <event.h>
#include <unistd.h> 

using namespace std;

#define BACKLOG 5
#define MEM_SIZE 1024

class SocketEvent{
public:
	SocketEvent(int _port);

	void init();

	// 新连接到来处理函数
	static void on_accept(int sock, short event, void *arg);
	// 有数据可读处理函数
	static void on_read(int sock, short event, void *arg);

	void loop();

private:
	int port;
	struct event_base* base;
	struct event listen_ev;
};

#endif