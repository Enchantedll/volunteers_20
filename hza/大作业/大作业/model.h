#ifndef model_h
#define model_h

//����Ϣ�ṹ��
typedef struct card {       //����Ϣ

	char number[18];     //����
	char password[8];      //������
	int status;     //��״̬ 0-δ�ϻ� 1-�����ϻ� 2-��ע�� 3-ʧЧ
	time_t timeStart;     //����ʱ��
	time_t timeEnd;      //��ֹʱ��
	float totalUse;      //�ۼƽ��
	time_t timeLast;      //���ʹ��ʱ��
	int useCount;      //ʹ�ô���
	float balance;       //���
	int del;     //ɾ����־ 0-δɾ�� 1-��ɾ��

	struct card * next;

}card;


//�Ʒ���Ϣ�ṹ��
typedef struct billing {       //�Ʒ���Ϣ

	char number[18];    //����
	time_t timeStart;      //�ϻ�ʱ��
	time_t timeEnd;      //�»�ʱ��
	float amount;      //���ѽ��
	int status;      //����״̬ 0-δ���� 1-�Ѿ�����
	int del;      //ɾ����ʶ 0-δɾ�� 1-ɾ��

	struct billing * next;

}billing;




#endif /* model_h */
