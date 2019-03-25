#ifndef __HEAD_H__
#define __HEAD_H__

#define ROOT 0x01
#define USER 0x02


//用户信息结构体
typedef struct userStruct {
	int id;				//工号
	char name[32];		//姓名
	int age;			//年龄
	char phone[12];		//电话
	char homeaddr[64];	//家庭地址
	char post[32];			//职位
	char inevent[20];		//入职日期
	int level;			//等级
	int wages;			//工资
	char passwd[32];	//密码
	int jurisdiction;	//权限（root/user）
} user_t;




//登录请求结构体
typedef struct loginStruct {
	int jurisdiction;	//权限（root/user）
	char name[32];		//用户名
	char passwd[32];	//密码
}login_t;

#define LOGIN	0x04			//登录
#define INSERT	0x08			//插入信息
#define DELETE	0x10			//删除
#define UPDATA	0x20			//更新数据
#define SELECT	0x40			//查询
#define HISTORY 0x80           //查询历史记录
#define SELECTALL 0x0100        //查询所以记录
#define USERSELECT 0x0200        //user select
#define USERUPDATA 0x0400       

//操作请求
typedef struct operation_request
{
	int		cmd;		 //请求码
	char	data[128];	//附加信息  （更新数据等 时的选择项值）
	login_t login;		//登录信息
	user_t user;		//用户信息
}or_t;


typedef struct retstr{

	int flag; 		//0：结束 1：未结束
	char data[1024];
} retstr_t;


#endif // !__HEAD_H__
