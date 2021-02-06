#ifndef model_h
#define model_h

//卡信息结构体
typedef struct card {       //卡信息

	char number[18];     //卡号
	char password[8];      //卡密码
	int status;     //卡状态 0-未上机 1-正在上机 2-已注销 3-失效
	time_t timeStart;     //开卡时间
	time_t timeEnd;      //截止时间
	float totalUse;      //累计金额
	time_t timeLast;      //最后使用时间
	int useCount;      //使用次数
	float balance;       //余额
	int del;     //删除标志 0-未删除 1-已删除

	struct card * next;

}card;


//计费信息结构体
typedef struct billing {       //计费信息

	char number[18];    //卡号
	time_t timeStart;      //上机时间
	time_t timeEnd;      //下机时间
	float amount;      //消费金额
	int status;      //消费状态 0-未结算 1-已经结算
	int del;      //删除标识 0-未删除 1-删除

	struct billing * next;

}billing;




#endif /* model_h */
