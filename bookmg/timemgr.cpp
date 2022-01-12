#include "pch.h"
#include <stdio.h>
#include <time.h>
#include "timemg.h"


void timeMgr(time_t ttt, int flag) {
	struct tm *tt;
	if (flag == 0) {
		tt = localtime(&ttt);
		printf("%d년", tt->tm_year + 1900);
		printf("%d월", tt->tm_mon + 1);
		printf("%d일", tt->tm_mday);
	}
	else {
		tt = gmtime(&ttt);
		printf("%d일", tt->tm_mday-1);
	}
	printf("%d시", tt->tm_hour);
	printf("%d분", tt->tm_min);
	printf("%d초\n", tt->tm_sec);
	if (flag) printf("경과되었습니다.\n");
}