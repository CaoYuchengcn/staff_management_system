#include<stdio.h>
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
#include <sqlite3.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/select.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>


#define N 128
#define DATA_PATH "./sql.db"

int sockfd;
sqlite3 *db;


struct sockaddr_in serveraddr;
struct sockaddr_in clientaddr;
socklen_t addrlen = sizeof(serveraddr);
socklen_t cli_len = sizeof(clientaddr);


void local_instal();

void init_sqlite3();
void * handle(void * arg);
void do_login(or_t *or,int acceptfd);
void do_insert(or_t *or,int acceptfd) ;
void do_select(or_t *or,int acceptfd);
void do_selectall(or_t *or,int acceptfd);
void do_updata(or_t *or,int acceptfd);
void do_delete(or_t *or,int acceptfd);
void do_user_select(or_t *or,int acceptfd);
void do_user_updata(or_t *or,int acceptfd);
void getNowTime(char * tim);
void insert_hister(char * name , char * ope );
void do_history(or_t *or,int acceptfd);




int main(int argc, const char *argv[])
{
	//socket->填充->绑定->监听->等待连接->数据交互->关闭 

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

	//绑定网络套接字和网络结构体
	if(bind(sockfd, (const struct sockaddr *)&serveraddr,addrlen) == -1){
		printf("bind failed.\n");
		exit(-1);
	}

	//监听套接字，将主动套接字转化为被动套接字
	if(listen(sockfd,10) == -1){
		printf("listen failed.\n");
		exit(-1);
	}

#if 0


	if (sqlite3_open(DATA_PATH, &db) != SQLITE_OK)//打开数据库获得数据库的句柄
	{
		printf("sql error \n %s\n", sqlite3_errmsg(db));
		return ;
	}
	//创建用户信息记录表
	char sql[128];
	char *errmsg;
	sprintf(sql, "create table userinfo (id int,name text, age int, phone test, homeaddr text, post text, inEvent text, level int, wages int, passwd text, jurisdiction int);");
	if (sqlite3_exec((db), sql, NULL, NULL, &errmsg) != SQLITE_OK) {
		printf("errmsg :%s.\n", errmsg);
	}
	else {
		printf("创建用户信息表成功.\n");
	}
	//创建历史表
	sprintf(sql, "create table history (name text, date text ,operate text);"); //用户名	时间	操作
	if (sqlite3_exec((db), sql, NULL, NULL, &errmsg) != SQLITE_OK) {
		printf("errmsg :%s.\n", errmsg);
	}
	else {
		printf("创建历史表成功.\n");
	}

#else

	//初始化sql数据库
	init_sqlite3(db);

#endif

	printf("创建数据库成功！ \n");

	fd_set readfds;
	int select_return;
	struct timeval timeout;

	while (1)
	{
		FD_ZERO(&readfds);
		FD_SET(sockfd, &readfds);
		FD_SET(0, &readfds);

		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		//printf("开始 select ! \n");
		select_return = select(sockfd + 1,&readfds,NULL,NULL,&timeout);
		if (select_return < 0)
		{
			printf("select error ! \n");
			return -1;
		}
		else if (select_return == 0)
		{
			//printf("select 请求超时 ！\n");
		}
		else {
			int i = 0;
			for (i = 0; i <= sockfd; i++)
			{
				if (FD_ISSET(i, &readfds))
				{
					if(i == sockfd)			//并发触发方式为sockfd
					{
						//printf("select 请求成功！\n");
						pthread_t thread;
						pthread_create(&thread,NULL,handle, (void *)&thread);//工作线程


					}
					if(i == 0)
					{
						local_instal();	
					}
				}
			}
		}
	}
	close(sockfd);
	return 0;
}

void * handle(void * arg)
{
	pthread_t pthread = *(pthread_t *)arg;
	int acceptfd;
	or_t or ;
	ssize_t recvbytes;

	//数据交互 
	acceptfd = accept(sockfd, (struct sockaddr *)&clientaddr, &cli_len);
	if (acceptfd == -1) {
		printf("acceptfd failed.\n");
		exit(-1);
	}

	while (1) {
		recvbytes = recv(acceptfd, &or , sizeof(or_t ), 0);
		if (recvbytes == -1) {
			printf("recv failed.\n");
			close(acceptfd);
			break;
		}
		else if (recvbytes == 0) {
			printf("设备离线\n");
			goto head_exit;
			break;
		}
		else {

			printf("CMD : %d\n",or.cmd);
			switch (or .cmd)
			{
			case LOGIN:
				printf("登录请求\n");
				do_login(&or,acceptfd);
				break;
			case INSERT:
				printf("插入请求\n");
				do_insert(&or,acceptfd);
				break;
			case SELECT:
				printf("查询信息请求\n");
				do_select(&or,acceptfd);
				break;
			case SELECTALL:
				printf("查询所以信息请求");
				do_selectall(&or,acceptfd);
				break;
			case UPDATA:
				printf("数据更新请求");
				do_updata(&or,acceptfd);
				break;
			case DELETE:
				printf("数据删除请求");
				do_delete(&or,acceptfd);
				break;
			case USERSELECT:
				printf("USER查询信息请求\n");
				do_user_select(&or,acceptfd);
				break;
			case USERUPDATA:
				printf("USER更新信息请求\n");
				do_user_updata(&or,acceptfd);
				break;
			case HISTORY:
				printf("历史查询请求\n");
				do_history(&or,acceptfd);
				break;
			default:
				printf("请求码查无此项！ \n");
				break;
			}

		}
	}
head_exit :
	pthread_exit(NULL);
}
void local_instal()
{

	or_t or;

	printf("请输入工号>>");
	fflush(stdout);
	getchar();
	scanf("%d",&or.user.id);
	printf("id : %d\n",or.user.id);

	printf("姓名>>");
	fflush(stdout);
	scanf("%s",or.user.name);
	printf("name : %s\n",or.user.name);

	printf("年龄>>");
	fflush(stdout);
	scanf("%d",&or.user.age);
	printf("age : %d\n",or.user.age);

	printf("电话>>");
	fflush(stdout);
	scanf("%s",or.user.phone);
	printf("phone : %s\n",or.user.phone);

	printf("家庭地址>>");
	fflush(stdout);
	scanf("%s",or.user.homeaddr);
	printf("homeaddr : %s\n",or.user.homeaddr);

	printf("职位>>");
	fflush(stdout);
	scanf("%s",or.user.post);
	printf("post : %s\n",or.user.post);

	printf("入职日期>>");
	fflush(stdout);
	scanf("%s",or.user.inevent);
	printf("inevent : %s\n",or.user.inevent);

	printf("等级>>");
	fflush(stdout);
	scanf("%d",&or.user.level);
	printf("level : %d\n",or.user.level);

	printf("工资>>");
	fflush(stdout);
	scanf("%d",&or.user.wages);
	printf("wages : %d\n",or.user.wages);

	printf("密码>>");
	fflush(stdout);
	scanf("%s",or.user.passwd);
	printf("passwd : %s\n",or.user.passwd);

	printf("权限（1：ROOT 2：USER）>>");
	fflush(stdout);
	scanf("%d",&or.user.jurisdiction);
	printf("jurisdiction : %d\n",or.user.jurisdiction);

	strcpy(or.login.name,"SYSTEM");
	do_insert(&or,0);

	printf("本地插入成功\n");

}
void init_sqlite3()
{
	//数据库建立
	if (sqlite3_open(DATA_PATH, &db) != SQLITE_OK)//打开数据库获得数据库的句柄
	{
		printf("sql error \n %s\n", sqlite3_errmsg(db));
		return ;
	}
	//创建用户信息记录表
	char sql[128];
	char *errmsg;
	//	sprintf(sql, "create table userinfo (id int,name text, age int, phone test, homeaddr text, post text, inEvent text, level int, wages int, passwd text, jurisdiction int);");

	if (sqlite3_exec((db),  "create table userinfo (id int,name text, age int, phone test, homeaddr text, post text, inEvent text, level int, wages int, passwd text, jurisdiction int);", NULL, NULL, &errmsg) != SQLITE_OK) {
		printf("errmsg :%s.\n", errmsg);
	}
	else {
		printf("创建用户信息表成功.\n");
	}
#if 1
	//创建历史表
	sprintf(sql, "create table history (name text, date text ,operate text);"); //用户名	时间	操作
	if (sqlite3_exec((db), "create table history (name text, date text ,operate text);", NULL, NULL, &errmsg) != SQLITE_OK) {
		printf("errmsg :%s.\n", errmsg);
	}
	else {
		printf("创建历史表成功.\n");
	}

#endif
}

void do_login(or_t * or,int acceptfd)
{
	char sql[128] = { 0 };
	char *errmsg;
	char **rep;
	int n_row;
	int n_column;
	int i, j;
	retstr_t ret;

	printf("--%s--%s-- \n",or->login.name,or->login.passwd);
	sprintf(sql, "select * from userinfo where name='%s' ", or->login.name);
	if (sqlite3_get_table(db, sql, &rep, &n_row, &n_column, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return;
	}
	else
	{
		if (n_row <= 0)
		{
			//回复：NO
			printf("登录失败，无该用户！ \n");
			ret.flag = 0;
			strcpy(ret.data,"登录失败，无该用户！ \n");
			send(acceptfd,&ret, sizeof(ret), 0);
			insert_hister(or->login.name,"登录失败");
			return;
		}
		else
		{
			char buf[32] = {0};
			strcpy(buf,*(rep + n_column + 9));
			printf("sql->%s    client->%s\n",buf,or->login.passwd);

			if (strcmp(buf, or->login.passwd) == 0)
			{
				if(strncmp(*(rep + n_column + 10),"1",1) == 0)
				{

					printf("ROOT登录成功! \n");
					ret.flag = 0;
					strcpy(ret.data,"ROOT");
					send(acceptfd,&ret, sizeof(ret), 0);

				}
				else
				{
					printf("USER 登录成功！ \n");
					ret.flag = 0;
					strcpy(ret.data,"USER");
					send(acceptfd,&ret, sizeof(ret), 0);

				}
				insert_hister(or->login.name,"登录成功");
			}
			else
			{
				printf("登录失败,密码错误！ \n");
				ret.flag = 0;
				strcpy(ret.data,"登录失败,密码错误！\n");
				send(acceptfd,&ret, sizeof(ret), 0);
				insert_hister(or->login.name,"登录失败");
			}

		}
	}
	//printf("登录请求操作完成");
}
void do_insert(or_t *or,int acceptfd) 
{
	printf("do insttall start! \n");
	char *errmsg;
	char sql[sizeof(or_t)] = { 0 };
	char **rep;
	int n_row;
	int n_column;
	int i, j;
	retstr_t ret;


	printf("判断插入\n");
	sprintf(sql, "select * from userinfo where name='%s' or id = %d ", or->user.name,or->user.id);
	if (sqlite3_get_table(db, sql, &rep, &n_row, &n_column, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		ret.flag = 0;
		strcpy(ret.data,"插入失败，请查证后重试！ \n");
		send(acceptfd,&ret, sizeof(ret), 0);
		insert_hister(or->login.name,"插入数据失败");
		return;
	}
	if (n_row > 0)
	{
		printf("用户已存在!\n");
		ret.flag = 0;
		strcpy(ret.data,"插入失败，用户或工号已存在!\n");
		send(acceptfd,&ret, sizeof(ret), 0);
		insert_hister(or->login.name,"插入数据失败，用户或工号已存在");
	}
	else
	{
		//printf("开始插入\n");
		sprintf(sql, "insert into userinfo values(%d,'%s',%d,'%s','%s','%s','%s',%d,%d,'%s',%d);", or->user.id,or->user.name,or->user.age,or->user.phone,or->user.homeaddr,or->user.post,or->user.inevent,or->user.level,or->user.wages,or->user.passwd,or->user.jurisdiction);
		if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
			printf("errmsg :%s.\n", errmsg);
			ret.flag = 0;
			strcpy(ret.data,"插入失败，请查证后重试！ \n");
			send(acceptfd,&ret, sizeof(ret), 0);
			insert_hister(or->login.name,"插入数据失败");
		}
		else {
			printf("insert data to stu success.\n");
			ret.flag = 0;
			strcpy(ret.data,"插入成功！\n");
			send(acceptfd,&ret, sizeof(ret), 0);
			insert_hister(or->login.name,"插入用户成功");
		}
	}
}

void do_select(or_t *or,int acceptfd)
{
	//printf("-------select--------------\n%d\n%s\n-----------------\n",or->cmd,or->data);
	char sql[128]={0};
	char *errmsg;
	char **rep;
	int n_row;
	int n_column;
	int id;
	int i,j;
	retstr_t ret;
	char buff[1024] = {0};
	char buf[512] = {0};
	switch(or->cmd)
	{
	case SELECT:
	case USERSELECT:
		sprintf(sql,"select * from userinfo where name = '%s'",or->user.name);

		sprintf(buf,"查询%s信息",or->user.name);
		insert_hister(or->login.name,buf);
		break;
	case SELECTALL:
		sprintf(sql,"select * from userinfo ");
		sprintf(buf,"查询所以信息");
		insert_hister(or->login.name,buf);
		break;

	}

	if(sqlite3_get_table(db,sql,&rep,&n_row,&n_column,&errmsg)!=SQLITE_OK)
	{
		printf("%s\n",errmsg);

		//return;
	}
	else
	{
		if(n_row==0)
		{
			puts("query fail!");
		}
		else
		{
			for(i=0;i<n_row+1;i++)
			{
				sprintf(ret.data,"%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s%-15s\n",*(rep + i*n_column + 0),*(rep + i*n_column + 1),*(rep + i*n_column + 2),*(rep + i*n_column + 3),*(rep + i*n_column + 4),*(rep + i*n_column + 5),*(rep + i*n_column + 6),*(rep + i*n_column + 7),*(rep + i*n_column + 8),*(rep + i*n_column + 9),*(rep + i*n_column + 10));

				ret.flag = 1;
				send(acceptfd,&ret, sizeof(ret), 0);
				memset(ret.data,0,sizeof(ret.data));
				usleep(1000);
			}
			ret.flag = 0;
			memset(ret.data,0,sizeof(ret.data));
			send(acceptfd,&ret, sizeof(ret), 0);

			/*
			   for(j=0;j<n_column;j++)
			   {

			   if((strlen(ret.data)+strlen(*(rep + i*n_column + j))) < 1023) //判断是否次次能够填满
			   {
			   sprintf(buff,"%-15s",*(rep + i*n_column + j));
			   strcat(ret.data,buff);		//填充
			   memset(buff,0,sizeof(buff));
			   }
			   else							//填充\0;
			   {		
			   int xx = 0;	
			   for(xx = strlen(ret.data) ; xx < 1024;xx++)
			   {
			   ret.data[xx] = '\0';
			   }
			   ret.flag = 1;
			//strcpy(ret.data,buff);
			send(acceptfd,&ret, sizeof(ret), 0);
			memset(buff,0,sizeof(buff));
			memset(ret.data,0,sizeof(ret.data));
			}
			}
			if((strlen(ret.data)+1) < 1023) //判断是否次次能够填满
			{
			ret.data[strlen(ret.data)] = '\n';
			}
			else							//填充\0;
			{		
			int xx = 0;	
			for(xx = strlen(ret.data) ; xx < 1024;xx++)
			{
			ret.data[xx] = '\0';
			}
			ret.flag = 1;
			//strcpy(ret.data,buff);
			send(acceptfd,&ret, sizeof(ret), 0);
			memset(buff,0,sizeof(buff));
			memset(ret.data,0,sizeof(ret.data));
			}
			}
			ret.flag = 0;
			//strcpy(ret.data,buff);
			send(acceptfd,&ret, sizeof(ret), 0);
			memset(buff,0,sizeof(buff));
			memset(ret.data,0,sizeof(ret.data));

*/
			return;
	}
}
ret.flag = 0;
strcpy(ret.data,"无记录\n");
send(acceptfd,&ret, sizeof(ret), 0);
memset(ret.data,0,sizeof(ret.data));

}
void do_selectall(or_t *or,int acceptfd)
{
	or->cmd == SELECTALL;
	do_select(or,acceptfd);
}
void do_updata(or_t *or,int acceptfd)
{
	char sql[128]={0};
	char *errmsg;
	float score;
	char **rep;
	char buf[512] = {0};
	int n_row;
	int n_column;
	retstr_t ret;
	//判断该ID是否存在
	if(strncmp(or->data,"test",4) == 0)
	{
		sprintf(sql, "select * from userinfo where id= %d", or->user.id);
		if (sqlite3_get_table(db, sql, &rep, &n_row, &n_column, &errmsg) != SQLITE_OK)
		{
			printf("%s\n", errmsg);
			ret.flag = 0;
			strcpy(ret.data,"数据异常，请重试\n");
			send(acceptfd,&ret, sizeof(ret), 0);
			return;
		}
		if (n_row > 0)
		{
			printf("存在该用户!\n");
			ret.flag = 0;
			strcpy(ret.data,"OK");
			send(acceptfd,&ret, sizeof(ret), 0);
		}
		else
		{
			printf("用户不存在!\n");
			ret.flag = 0;
			strcpy(ret.data,"所操作的工号不存在，请查证后重试！\n");
			send(acceptfd,&ret, sizeof(ret), 0);
		}
	}
	else
	{			
				
		if(strcmp(or->data,"name") == 0)
		{
			sprintf(sql, "select * from userinfo where name = '%s'", or->user.name);
				if (sqlite3_get_table(db, sql, &rep, &n_row, &n_column, &errmsg) != SQLITE_OK)
				{
					printf("%s\n", errmsg);
					ret.flag = 0;
					strcpy(ret.data,"数据异常，请重试\n");
					send(acceptfd,&ret, sizeof(ret), 0);
					return;
				}
				if (n_row > 0)
				{
					printf("该用户名已存在!\n");
					ret.flag = 0;
					strcpy(ret.data,"该用户名已存在,请重试!\n");
					send(acceptfd,&ret, sizeof(ret), 0);
					return;
				}
			sprintf(sql,"update userinfo set name='%s' where id=%d",or->user.name,or->user.id);
			sprintf(buf,"更新%s为%s",or->data,or->user.name);
		}
		else if(strcmp(or->data,"age") == 0)
		{
			sprintf(sql,"update userinfo set age=%d where id=%d",or->user.age,or->user.id);
			sprintf(buf,"更新%s为%d",or->data,or->user.age);
		}
		else if(strcmp(or->data,"phone") == 0)
		{
			sprintf(sql,"update userinfo set phone='%s' where id=%d",or->user.phone,or->user.id);
			sprintf(buf,"更新%s为%s",or->data,or->user.phone);
		}
		else if(strcmp(or->data,"homeaddr") == 0)
		{
			sprintf(sql,"update userinfo set homeaddr='%s' where id=%d",or->user.homeaddr,or->user.id);
			sprintf(buf,"更新%s为%s",or->data,or->user.homeaddr);
		}
		else if(strcmp(or->data,"post") == 0)
		{
			sprintf(sql,"update userinfo set post='%s' where id=%d",or->user.post,or->user.id);
			sprintf(buf,"更新%s为%s",or->data,or->user.post);
		}
		else if(strcmp(or->data,"inevent") == 0)
		{
			sprintf(sql,"update userinfo set inevent='%s' where id=%d",or->user.inevent,or->user.id);
			sprintf(buf,"更新%s为%s",or->data,or->user.inevent);
		}
		else if(strcmp(or->data,"level") == 0)
		{
			sprintf(sql,"update userinfo set level=%d where id=%d",or->user.level,or->user.id);
			sprintf(buf,"更新%s为%d",or->data,or->user.level);
		}
		else if(strcmp(or->data,"wages") == 0)
		{
			sprintf(sql,"update userinfo set wages=%d where id=%d",or->user.wages,or->user.id);
			sprintf(buf,"更新%s为%d",or->data,or->user.wages);
		}
		else if(strcmp(or->data,"passwd") == 0)
		{
			sprintf(sql,"update userinfo set passwd='%s' where id=%d",or->user.passwd,or->user.id);
			sprintf(buf,"更新%s为%s",or->data,or->user.passwd);
		}

		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
		{	
			printf("%s\n",errmsg);
			ret.flag = 0;
			strcpy(ret.data,"操作失败，请查证后再试\n");
			send(acceptfd,&ret, sizeof(ret), 0);
			sprintf(buf,"更新%s失败",or->data);
			insert_hister(or->login.name,buf);
			return;
		}

		ret.flag = 0;
		strcpy(ret.data,"操作成功\n");
		send(acceptfd,&ret, sizeof(ret), 0);
		insert_hister(or->login.name,buf);

	}

	return;

}
void do_delete(or_t *or ,int acceptfd)
{
	char sql[128]={0};
	char *errmsg;
	retstr_t ret;

	char buf[512] = {0};

	sprintf(sql,"delete from userinfo where name = '%s'",or->user.name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
	{
		printf("删除失败：%s\n",errmsg);

		ret.flag = 0;
		strcpy(ret.data,"删除失败！\n");
		send(acceptfd,&ret, sizeof(ret), 0);
		sprintf(buf,"删除ID：%d失败",or->user.id);
		insert_hister(or->login.name,"用户删除失败");
		return;
	}
	printf("删除成功.\n");
	ret.flag = 0;
	strcpy(ret.data,"删除成功！\n");
	send(acceptfd,&ret, sizeof(ret), 0);
	sprintf(buf,"删除ID：%d成功",or->user.id);
	insert_hister(or->login.name,"用户删除成功");
	return;
}
void do_user_select(or_t *or,int acceptfd)
{
	do_select(or,acceptfd);
}
void do_user_updata(or_t *or,int acceptfd)
{
	char sql[128]={0};
	char *errmsg;
	float score;
	char **rep;
	int n_row;
	int n_column;
	retstr_t ret;
	//printf("%d,%s,%s,%s\n",or->cmd,or->data,or->login.name,or->user.phone);
	char buf[512] = {0};
	if(strcmp(or->data,"age") == 0)
	{
		sprintf(sql,"update userinfo set age=%d where name='%s'",or->user.age,or->login.name);
		sprintf(buf,"更新%s为%d",or->data,or->user.age);
	}
	else if(strcmp(or->data,"phone") == 0)
	{
		sprintf(sql,"update userinfo set phone='%s' where name='%s'",or->user.phone,or->login.name);
		sprintf(buf,"更新%s为%s",or->data,or->user.phone);
	}
	else if(strcmp(or->data,"homeaddr") == 0)
	{
		sprintf(sql,"update userinfo set homeaddr='%s' where name='%s'",or->user.homeaddr,or->login.name);
		sprintf(buf,"更新%s为%s",or->data,or->user.homeaddr);
	}
	else if(strcmp(or->data,"post") == 0)
	{
		sprintf(sql,"update userinfo set post='%s' where name='%s'",or->user.post,or->login.name);
		sprintf(buf,"更新%s为%s",or->data,or->user.post);
	}

	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg)!=SQLITE_OK)
	{	
		printf("%s\n",errmsg);
		ret.flag = 0;
		strcpy(ret.data,"操作失败，请查证后再试\n");
		send(acceptfd,&ret, sizeof(ret), 0);
		sprintf(buf,"更新%s失败",or->data);
		insert_hister(or->login.name,buf);
		return;
	}

	ret.flag = 0;
	strcpy(ret.data,"操作成功\n");
	send(acceptfd,&ret, sizeof(ret), 0);
	insert_hister(or->login.name,buf);
}
void do_history(or_t *or,int acceptfd)
{
	char buf[512] = {0};
	char sql[128]={0};
	char *errmsg;
	char **rep;
	int n_row;
	int n_column;
	int id;
	int i,j;
	retstr_t ret;
	char buff[1024] = {0};

	sprintf(sql,"select * from history ");
	if(sqlite3_get_table(db,sql,&rep,&n_row,&n_column,&errmsg)!=SQLITE_OK)
	{
		printf("%s\n",errmsg);

		//return;
	}
	else
	{
		if(n_row==0)
		{
			puts("query fail!");
		}
		else
		{
			for(i=0;i<n_row+1;i++)
			{
				memset(ret.data,0,sizeof(ret.data));
				sprintf(ret.data,"%-20s,%-20s,%-20s\n",*(rep + i*n_column + 0),*(rep + i*n_column + 1),*(rep + i*n_column + 2));
				//printf("%s\n",ret.data);
				ret.flag = 1;
				//strcpy(ret.data,buff);
				send(acceptfd,&ret, sizeof(ret), 0);
				memset(ret.data,0,sizeof(ret.data));
				usleep(1000);
			}
			ret.flag = 0;
			memset(ret.data,0,sizeof(ret.data));
			send(acceptfd,&ret, sizeof(ret), 0);
			insert_hister(or->login.name,"查询历史记录");
			//
			/*
			   for(j=0;j<n_column;j++)
			   {


			   if((strlen(ret.data)+strlen(*(rep + i*n_column + j))) < 1023) //判断是否次次能够填满
			   {
			   sprintf(buff,"%-20s",*(rep + i*n_column + j));
			   strcat(ret.data,buff);		//填充
			   memset(buff,0,sizeof(buff));
			   }
			   else							//填充\0;
			   {		
			   int xx = 0;	
			   for(xx = strlen(ret.data) ; xx < 1024;xx++)
			   {
			   ret.data[xx] = '\0';
			   }
			   ret.flag = 1;
			//strcpy(ret.data,buff);
			send(acceptfd,&ret, sizeof(ret), 0);
			printf("%s",ret.data);
			memset(buff,0,sizeof(buff));
			memset(ret.data,0,sizeof(ret.data));
			usleep(2000);
			}
			}
			if((strlen(ret.data)+1) < 1023) //判断是否次次能够填满
			{
			ret.data[strlen(ret.data)] = '\n';
			}
			else							//填充\0;
			{		
			int xx = 0;	
			for(xx = strlen(ret.data) ; xx < 1024;xx++)
			{
			ret.data[xx] = '\0';
			}
			ret.flag = 1;
			//strcpy(ret.data,buff);
			send(acceptfd,&ret, sizeof(ret), 0);
			printf("%s",ret.data);
			memset(buff,0,sizeof(buff));
			memset(ret.data,0,sizeof(ret.data));
			usleep(2000);
			}
			}
			ret.flag = 0;
			//strcpy(ret.data,buff);
			send(acceptfd,&ret, sizeof(ret), 0);
			printf("%s",ret.data);
			memset(buff,0,sizeof(buff));
			memset(ret.data,0,sizeof(ret.data));
			insert_hister(or->login.name,"查询历史记录");
			usleep(2000);
			*/


			return;
	}
}
ret.flag = 0;
strcpy(ret.data,"无记录\n");
send(acceptfd,&ret, sizeof(ret), 0);
memset(ret.data,0,sizeof(ret.data));
//sprintf(buf,);
insert_hister(or->login.name,"查询历史记录失败");

}

void insert_hister(char * name,char * ope)
{
	char sql[128]={0};
	char *errmsg;
	float score;
	char **rep;
	int n_row;
	int n_column;
	char date[64] = {0};
	getNowTime(date);
	sprintf(sql, "insert into history values('%s','%s','%s');",name,date,ope); //姓名 ，时间，操作
	if (sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK) {
		printf("errmsg :%s.\n", errmsg);
	}
	else {
		printf("插入历史记录成功.\n");
	}

}

void getNowTime(char * tim)
{
	struct tm *t;
	time_t tt;
	time(&tt);
	t = localtime(&tt);
	sprintf(tim,"%4d年%02d月%02d日 %02d:%02d:%02d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
}
