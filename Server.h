#pragma once

// 初始化监听套接字
int initListenFd(unsigned short);
// 启动 epoll
int epollRun(int lfd);