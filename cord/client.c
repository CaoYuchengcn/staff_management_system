#include <stdio.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "head.h"
int sockfd;

/****************************** ROOT TEAD **********************************/

void root_login_select_name(or_t *or)
{
	retstr_t retstr;
	or->cmd = SELECT;
	printf("请输入要查询的用户名>>");
	fflush(stdout);
	scanf("%s",or->user.name);

	printf("SELECT %d\n",or->cmd);
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 查询请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
	//printf("%s",retstr.data);


	printf("查询结束\n");
}
root_login_select_all(or_t *or)
{
	retstr_t retstr;
	or->cmd = SELECTALL;

	printf("SELECT %d\n",or->cmd);
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 查询请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
	//printf("%s",retstr.data);


	printf("查询结束\n");
}
void root_login_select(or_t *or)
{
	int i = 0;
	while(1)
	{
		printf("*************************************\n");
		printf("*** 1.按人名查找 2.查找所有 3.退出 ***\n");
		printf("**************************************\n");
		scanf("%d",&i);
		switch(i)
		{
		case 1 :
			root_login_select_name(or);
			break;
		case 2 :
			root_login_select_all(or);
			break;
		case 3 :
			goto root_login_select_exit;
		default :
			printf("输入有误，请重新输入! \n");
			break;
		}

	}
root_login_select_exit :
	return ;
}


/////////////

void root_login_updata_name(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"name");
	printf("请输入新用户名>>");
	fflush(stdout);	
	scanf("%s",or->user.name);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_age(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"age");
	printf("请输入新年龄>>");
	fflush(stdout);	
	scanf("%d",&or->user.age);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_homeaddr(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"homeaddr");
	printf("请输入新家庭地址>>");
	fflush(stdout);	
	scanf("%s",or->user.homeaddr);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_phone(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"phone");
	printf("请输入新电话");
	fflush(stdout);	
	scanf("%s",or->user.phone);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_post(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"post");
	printf("请输入新职位>>");
	fflush(stdout);	
	scanf("%s",or->user.post);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_wages(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"wages");
	printf("请输入新工资>>");
	fflush(stdout);	
	scanf("%d",&or->user.wages);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_inevent(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"inevent");
	printf("请输入新入职日期>>");
	fflush(stdout);	
	scanf("%s",or->user.inevent);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_level(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"level");
	printf("请输入新等级>>");
	fflush(stdout);	
	scanf("%d",&or->user.level);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void root_login_updata_passwd(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"passwd");
	printf("请输入新密码>>");
	fflush(stdout);	
	scanf("%s",or->user.passwd);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}

void root_login_updata(or_t *or)
{
	int i = 0;
	retstr_t retstr;

	or->cmd = UPDATA ;
	printf("请输入要修改的工号:\n");
	scanf("%d",&or->user.id);
	strcpy(or->data,"test");
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		//printf("%s",retstr.data);
		fflush(stdout);
		//memset(&retstr,0,sizeof(retstr_t));
	}
	while(retstr.flag);	//0 ： 结束

	if(strncmp(retstr.data,"OK",2) != 0)
	{	
		//printf("%s",retstr.data);

		goto root_login_updata_exit;
	}
	strcpy(or->data,"NULL");
	while(1)
	{
		printf("*************************************\n");
		printf("*** 1.姓名 2.年龄 3.家庭住址 4 电话 ******\n");
		printf("*** 5.职位 6.工资 7.入职年月 8.评级 ******\n");
		printf("*** 9:密码   10:退出 ******\n");
		printf("**************************************\n");
		scanf("%d",&i);
		switch(i)
		{
		case 1:
			root_login_updata_name(or);
			break;
		case 2:
			root_login_updata_age(or);
			break;
		case 3:
			root_login_updata_homeaddr(or);
			break;
		case 4:
			root_login_updata_phone(or);
			break;
		case 5:
			root_login_updata_post(or);
			break;
		case 6:
			root_login_updata_wages(or);
			break;
		case 7:
			root_login_updata_inevent(or);
			break;
		case 8:
			root_login_updata_level(or);
			break;
		case 9:
			root_login_updata_passwd(or);
			break;
		case 10 :
			goto root_login_updata_exit;
		default :
			printf("输入有误，请重新输入! \n");
			break;
		}


	}
root_login_updata_exit:
	return ;
}


void root_login_insert(or_t *or)
{
	retstr_t retstr;
	printf("请输入工号>>");
	fflush(stdout);
	getchar();
	scanf("%d",&or->user.id);
	printf("id : %d\n",or->user.id);

	printf("姓名>>");
	fflush(stdout);
	scanf("%s",or->user.name);
	printf("name : %s\n",or->user.name);

	printf("年龄>>");
	fflush(stdout);
	scanf("%d",&or->user.age);
	printf("age : %d\n",or->user.age);

	printf("电话>>");
	fflush(stdout);
	scanf("%s",or->user.phone);
	printf("phone : %s\n",or->user.phone);

	printf("家庭地址>>");
	fflush(stdout);
	scanf("%s",or->user.homeaddr);
	printf("homeaddr : %s\n",or->user.homeaddr);

	printf("职位>>");
	fflush(stdout);
	scanf("%s",or->user.post);
	printf("post : %s\n",or->user.post);

	printf("入职日期>>");
	fflush(stdout);
	scanf("%s",or->user.inevent);
	printf("inevent : %s\n",or->user.inevent);

	printf("等级>>");
	fflush(stdout);
	scanf("%d",&or->user.level);
	printf("level : %d\n",or->user.level);

	printf("工资>>");
	fflush(stdout);
	scanf("%d",&or->user.wages);
	printf("wages : %d\n",or->user.wages);

	printf("密码>>");
	fflush(stdout);
	scanf("%s",or->user.passwd);
	printf("passwd : %s\n",or->user.passwd);

	printf("权限（1：ROOT 2：USER）>>");
	fflush(stdout);
	scanf("%d",&or->user.jurisdiction);
	printf("jurisdiction : %d\n",or->user.jurisdiction);

	or->cmd = INSERT;
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 插入请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		//memset(&retstr,0,sizeof(retstr_t));
	}
	while(retstr.flag);	//0 ： 结束

}
void root_login_delete(or_t *or)
{
	int i ;
	retstr_t retstr;
	or->cmd = DELETE;
	printf("请输入要删除的用户名:\n");
	scanf("%s",or->user.name);
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 删除请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		//memset(&retstr,0,sizeof(retstr_t));
	}
	while(retstr.flag);	//0 ： 结束

}
void root_login_select_history(or_t *or)
{
	retstr_t retstr;
	or->cmd = HISTORY;
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 历史查询请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		//printf("%s",retstr.data);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束

}


void root_login()
{
	or_t or;
	retstr_t retstr;
	int again = 0 ;

	or.cmd = LOGIN;
	or.login.jurisdiction = ROOT;
login_gagin	:
	printf("请输入用户名>>");
	fflush(stdout);
	scanf("%s",or.login.name);
	printf("请输入密码>>");
	fflush(stdout);
	scanf("%s",or.login.passwd);

	if((send(sockfd,&or,sizeof(or_t),0)) == -1){
		printf("root 登录请求发送失败.\n");
	}
	//printf("%s--%s\n",or.login.name,or.login.passwd);
	recv(sockfd,&retstr,sizeof(retstr_t),0);
	//printf("%s",retstr.data);
	if(strncmp(retstr.data,"ROOT",4) == 0)
	{
		again = 0;

		while(1)
		{
			printf("*******************************************\n");
			printf("** 1. 查询     2. 修改        3. 添加用户 **\n");
			printf("** 4. 删除用户 5. 查询历史记录 6. 退出     **\n");
			printf("********************************************\n");
			int i ;	
			scanf("%d",&i);	
			switch(i)
			{
			case 1:
				root_login_select(&or);
				break;
			case 2:
				root_login_updata(&or);
				break;
			case 3:
				root_login_insert(&or);
				break;
			case 4:
				root_login_delete(&or);
				break;
			case 5:
				root_login_select_history(&or);
				break;
			case 6:
				goto root_exit;
			default :
				printf("输入有误，请重新输入! \n");
				break;

			}
		}
	}
	else if(strncmp(retstr.data,"USER",4) == 0)
	{
		printf("该用户不是ROOT用户，请切换ROOT用户重试\n");
		goto root_exit;

	}
	else
	{
		printf("用户不存在或密码错误,请重试 \n");
		if(again++ >= 2)
		{
			goto root_exit;
		}
		else
		{
			goto login_gagin;
		}

	}
root_exit:
	return ;
}
/********************************* ROOT END **************************************/
/********************************* USER  HEAD *************************************/
void user_login_select(or_t *or)
{
	retstr_t retstr;
	or->cmd = USERSELECT;
	strcpy(or->user.name,or->login.name);
	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 查询请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
	//printf("%s",retstr.data);



	printf("查询结束！ \n");	
}

//////

void user_login_updata_age(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"age");
	printf("请输入新年龄>>");
	fflush(stdout);	
	scanf("%d",&or->user.age);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void user_login_updata_homeaddr(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"homeaddr");
	printf("请输入新家庭地址>>");
	fflush(stdout);	
	scanf("%s",or->user.homeaddr);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void user_login_updata_phone(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"phone");
	printf("请输入新电话");
	fflush(stdout);	
	scanf("%s",or->user.phone);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}
void user_login_updata_post(or_t *or)
{
	retstr_t retstr;
	strcpy(or->data,"post");
	printf("请输入新职位>>");
	fflush(stdout);	
	scanf("%s",or->user.post);

	if((send(sockfd,or,sizeof(or_t),0)) == -1){
		printf("root 更新请求发送失败.\n");
	}
	do{
		recv(sockfd,&retstr,sizeof(retstr_t),0);
		printf("%s",retstr.data);
		fflush(stdout);
		memset(&retstr.data,0,1024);
	}
	while(retstr.flag);	//0 ： 结束
}

////////



void user_login_updata(or_t *or)
{
	int i = 0;
	or->cmd = USERUPDATA;
	while(1)
	{
		printf("*******************************************************\n");
		printf("******* 1.年龄 2.电话 3.家庭住址 4.职位  5.退出 *********\n");
		printf("*******************************************************\n");
		scanf("%d",&i);
		switch(i)
		{
		case 1:
			user_login_updata_age(or);
			break;
		case 2 :
			user_login_updata_phone(or);
			break;
		case 3 :
			user_login_updata_homeaddr(or);
			break;
		case 4 :
			user_login_updata_post(or);
			break;
		case 5 :
			goto user_login_select_exit;
		default :
			printf("输入有误，请重新输入! \n");
			break;
		}

	}
user_login_select_exit:
	return ;
}
void user_login()
{
	or_t or;
	retstr_t retstr;
	int again = 0 ;

	or.cmd = LOGIN;
	or.login.jurisdiction = USER;
user_gagin	:
	printf("请输入用户名>>");
	fflush(stdout);
	scanf("%s",or.login.name);
	printf("请输入密码>>");
	fflush(stdout);
	scanf("%s",or.login.passwd);

	if((send(sockfd,&or,sizeof(or_t),0)) == -1){
		printf("root 登录请求发送失败.\n");
	}
	//printf("%s--%s\n",or.login.name,or.login.passwd);
	recv(sockfd,&retstr,sizeof(retstr_t),0);
	//printf("%s",retstr.data);
	if(strncmp(retstr.data,"USER",4) == 0)
	{
		again = 0;
		int i = 0;
		while(1)
		{
			printf("*************************************\n");
			printf("******* 1.查询 2.修改 3.退出 *********\n");
			printf("**************************************\n");
			scanf("%d",&i);
			switch(i)
			{
			case 1:
				user_login_select(&or);
				break;
			case 2 :
				user_login_updata(&or);
				break;
			case 3 :
				goto user_login_select_exit;
			default :
				printf("输入有误，请重新输入! \n");
				break;
			}

		}

	}
	else if(strncmp(retstr.data,"ROOT",4) == 0)
	{
		printf("该用户不是普通用户，请切换普通用户重试\n");
		goto user_login_select_exit;

	}
	else
	{
		printf("用户不存在或密码错误,请重试 \n");
		if(again++ >= 2)
		{
			goto user_login_select_exit;
		}
		else
		{
			goto user_gagin;
		}

	}


user_login_select_exit:
	return ;
}
/***************************** USER END ***********************************/
int main(int argc, const char *argv[])
{
	//socket->填充->绑定->监听->等待连接->数据交互->关闭 

	int acceptfd;
	ssize_t recvbytes,sendbytes;
	char buf[1024] = {0};
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;
	socklen_t addrlen = sizeof(serveraddr);
	socklen_t cli_len = sizeof(clientaddr);
	//创建网络通信的套接字
	sockfd = socket(AF_INET,SOCK_STREAM, 0);
	if(sockfd == -1){
		perror("socket failed.\n");
		exit(-1);
	}
	printf("sockfd :%d.\n",sockfd); 

	//填充网络结构体
	memset(&serveraddr,0,sizeof(serveraddr));
	memset(&clientaddr,0,sizeof(clientaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port   = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if(connect(sockfd,(const struct sockaddr *)&serveraddr,addrlen) == -1){
		perror("connect failed.\n");
		exit(-1);
	}

	int i = 0;
	while(1){

		printf("*********************************************\n");
		printf("*** 1.管理员登录  2. 普通用户登录  3. 退出 ***\n");
		printf("*********************************************\n");
		scanf("%d",&i);
		switch(i)
		{
		case 1:
			root_login();
			break;
		case 2:
			user_login();
			break;
		case 3:
			goto main_exit;
defaule : 
			printf("输入有误，请重新输入！\n");
			break;
		}
	}
main_exit:
	close(sockfd);

	return 0;
}
