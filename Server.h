#pragma once

// ��ʼ�������׽���
int initListenFd(unsigned short);
// ���� epoll
int epollRun(int lfd);