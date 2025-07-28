#include "Server.h"
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

const int events_num = 1024;

int initListenFd(unsigned short port) {
	// 1. ����������fd
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (lfd == -1) {
		perror("socket");
		return -1;
	}
	// 2. ���ö˿ڸ���
	int opt = 1;
	int ret = setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (ret == -1) {
		perror("setsockopt");
		return -1;
	}
	// 3. ��
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
		addr.sin_port = htons(port);
	ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1) {
		perror("bind");
		return -1;
	}
	// 4. ���ü���
	ret = listen(lfd, 128);
	if (ret == -1) {
		perror("listen");
		return -1;
	}
	// 5. ����fd
	return lfd;
}

int epollRun(int lfd) {
	// 1. ���� epoll ʵ��
	int epfd = epoll_create(1);
	if (epfd == -1) {
		perror("epoll_create");
		return -1;
	}
	// 2. lfd ����
	struct epoll_event ev;
	ev.data.fd = lfd;
	ev.events = EPOLLIN;
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
	if (ret == -1) {
		perror("epoll_ctl");
		return -1;
	}
	// 3. ���
	struct epoll_event evs[events_num];
	while (1) {
		int num = epoll_wait(epfd, evs, events_num, -1);
		for (int i = 0; i < num; i++) {
			int fd = evs[i].data.fd;
			if (fd == lfd) {
				// �������� accept
			} else {
				// ��Ҫ�ǽ��նԶ˵�����
			}
		}
	}
	return 0;
}