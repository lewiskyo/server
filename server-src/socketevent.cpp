#include "socketevent.h"

SocketEvent::SocketEvent(int _port):port(_port){
}

void SocketEvent::init(){

    struct sockaddr_in my_addr;
    int sock;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    int yes = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    memset(&my_addr, 0, sizeof(my_addr));

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(this->port);
    my_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sock, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
    listen(sock, BACKLOG);

    base = event_base_new();
    event_set(&listen_ev, sock, EV_READ|EV_PERSIST, on_accept, this);
    event_base_set(base, &listen_ev);

    event_add(&listen_ev, NULL);
}

void SocketEvent::on_accept(int sock, short event, void *arg){

	SocketEvent* socketEvent = (SocketEvent*)arg;
	struct event_base* base = (struct event_base*) socketEvent->base;

    struct sockaddr_in cli_addr;
    int newfd;
    socklen_t sin_size;


    struct event* read_ev = (struct event*)malloc(sizeof(struct event));
    sin_size = sizeof(struct sockaddr_in);
    newfd = accept(sock, (struct sockaddr*)&cli_addr, &sin_size);//指定服务端去接受客户端的连接

    event_set(read_ev, newfd, EV_READ|EV_PERSIST, on_read, read_ev);
    event_base_set(base, read_ev);
    event_add(read_ev, NULL);
}

void SocketEvent::on_read(int sock, short event, void *arg){
    struct event* write_ev;
    int size;
    char* buffer = (char*)malloc(MEM_SIZE);
    bzero(buffer, MEM_SIZE);
    size = recv(sock, buffer, MEM_SIZE, 0);
    printf("receive data:%s, size:%d\n", buffer, size);
    if (size == 0)
    {
        event_del((struct event*)arg);

        free((struct event*)arg);
        close(sock);
        return;
    }

    send(sock, buffer, strlen(buffer), 0);
    free(buffer);
}

void SocketEvent::loop(){
	int ret = event_base_loop(base, EVLOOP_ONCE | EVLOOP_NONBLOCK);

    if (ret != 0  and ret != 1){
    	cout << "event_base_loop error, return" << endl;
    	exit(1);
    }

    cout << "loop finish" << endl;

}