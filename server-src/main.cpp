#include "baseserver.h"


int main(){

	BaseServer server(1000000, 25341);

	server.init();

	server.loop();

	return 0;
}
