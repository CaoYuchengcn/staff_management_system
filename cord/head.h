#ifndef __HEAD_H__
#define __HEAD_H__

#define ROOT 0x01
#define USER 0x02


//�û���Ϣ�ṹ��
typedef struct userStruct {
	int id;				//����
	char name[32];		//����
	int age;			//����
	char phone[12];		//�绰
	char homeaddr[64];	//��ͥ��ַ
	char post[32];			//ְλ
	char inevent[20];		//��ְ����
	int level;			//�ȼ�
	int wages;			//����
	char passwd[32];	//����
	int jurisdiction;	//Ȩ�ޣ�root/user��
} user_t;




//��¼����ṹ��
typedef struct loginStruct {
	int jurisdiction;	//Ȩ�ޣ�root/user��
	char name[32];		//�û���
	char passwd[32];	//����
}login_t;

#define LOGIN	0x04			//��¼
#define INSERT	0x08			//������Ϣ
#define DELETE	0x10			//ɾ��
#define UPDATA	0x20			//��������
#define SELECT	0x40			//��ѯ
#define HISTORY 0x80           //��ѯ��ʷ��¼
#define SELECTALL 0x0100        //��ѯ���Լ�¼
#define USERSELECT 0x0200        //user select
#define USERUPDATA 0x0400       

//��������
typedef struct operation_request
{
	int		cmd;		 //������
	char	data[128];	//������Ϣ  ���������ݵ� ʱ��ѡ����ֵ��
	login_t login;		//��¼��Ϣ
	user_t user;		//�û���Ϣ
}or_t;


typedef struct retstr{

	int flag; 		//0������ 1��δ����
	char data[1024];
} retstr_t;


#endif // !__HEAD_H__
