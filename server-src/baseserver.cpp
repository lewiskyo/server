#include "baseserver.h"

BaseServer::BaseServer(int _loopInterval, int _port): loopInterval(_loopInterval){
	socketEvent = new SocketEvent(_port);
}

void BaseServer::init(){
    vm->init();
	socketEvent->init();
}


bool BaseServer::loop(){
	while(true){

        socketEvent->loop();
		usleep(loopInterval);
	}

	return true;
}
