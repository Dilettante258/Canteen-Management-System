#ifndef PROJECT_CORE_H
#define PROJECT_CORE_H

#endif //PROJECT_CORE_H
//头文件
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//全局变量定义
#define USER_FILE "user.txt"
#define RECORD_FILE "record.txt"
#define FOOD_FILE "food.txt"
#define CONSOLE "CON"
#define BUFLEN 255
#define NUM 50
#define password 123

//================ 结构体 ================
struct Student{
    char card_num[20]; //卡号
    char name[20];//姓名
    char money[20];//余额
    char mode[2];//状态
};
typedef struct Student student;//别名student

struct Food{
    char id[20];
    char name[20];
    char price[20];
    char num[10];
};
typedef struct Food food;//和student内容相似

struct Record{
    char stu_id[20];
    char food_id[20];
    char food_price[20];
    char record_time[255];
};
typedef struct Record record;//和student内容相似

//================ 函数声明 ================
//主函数
int main(void);
//重启函数
void rerun();
//主菜单显示
int menu();
//结构体内容初始化
void init(student *stu,food *fd,record *re);
//从文件读入学生卡信息
void readfile(student *stu);
//从文件读入菜品信息
void readfood(food *fd);
//从文件读入记录信息
void readrecord(record *re);
//保存学生信息
void savefile(student *stu);
//保存食物信息
void savefood(food *fd);
//保存记录信息
void saverecord(record *re);

//管理模式
void admin_mode(student *stu,food *fd);
//管理模式菜单
int admin_menu();
//注册学生卡
void regist();
//充值
void charge(student *stu);
//挂失
void report_of_loss(student *stu);
//解挂
void hanging_solutions(student *stu);
//注销
void del(student *stu);
//录入菜品
void input(food *fd);
//查询菜品
void check(food *fd);
//统计功能 （打印所有菜品信息）
void count(food *fd);

//学生模式
void stu_mode(student *stu,food *fd,record *re);
//学生模式菜单
int stu_menu();
//查余额
void surplus(student *stu,char *num);
//消费记录
void sturecord(record *re,char *num);
//购物
void purchase(student *stu,food *fd,char *num);

//================ 程序辅助功能实现 ================
//结构体内容初始化
void init(student *stu,food *fd,record *re){

    for(int i = 0; i<NUM;i++){
        strcpy(stu[i].card_num,"");
        strcpy(stu[i].name,"");
        strcpy(stu[i].money,"");
        strcpy(stu[i].mode,"");
    }

    for(int i = 0; i<NUM;i++){
        strcpy(fd[i].id,"");
        strcpy(fd[i].name,"");
        strcpy(fd[i].price,"");
        strcpy(fd[i].num,"");
    }

    for(int i = 0; i<BUFLEN;i++){
        strcpy(re[i].stu_id,"");
        strcpy(re[i].food_id,"");
        strcpy(re[i].food_price,"");
        strcpy(re[i].record_time,"");
    }

}

//从文件读入学生卡信息
void readfile(student *stu){
    int i=0;
    //输入重定向，从文件输入。
    freopen(USER_FILE, "r", stdin);
    for(i=0;i<NUM;i++){
//      while(~scanf("%s%s%s%s", stu[i].card_num,stu[i].name, stu[i].money,stu[i].mode));
        scanf("%s%s%s%s", stu[i].card_num,stu[i].name, stu[i].money,stu[i].mode);

    }
    //重定向返回
    freopen("CON", "r", stdin);

}

//从文件读入菜品信息
void readfood(food *fd){
    freopen(FOOD_FILE, "r", stdin);

    for(int i=0;i<NUM;i++){
        scanf("%s%s%s%s", fd[i].id,fd[i].name,fd[i].price,fd[i].num);
    }
    freopen("CON", "r", stdin);

}

//从文件读入记录信息
void readrecord(record *re){
    freopen(RECORD_FILE, "r", stdin);

    for(int i=0;i<NUM;i++){
        scanf("%s%s%s%s", re[i].stu_id,re[i].food_id,re[i].food_price,re[i].record_time);
    }
    freopen("CON", "r", stdin);
}

//保存学生信息
void savefile(student *stu){
    //重定向到文件，向文件中输入
    freopen(USER_FILE, "w", stdout);

    for(int i = 0; i<NUM; i++){
        if(strlen(stu[i].card_num)!=0){
            printf("%s %s %s %s\n",stu[i].card_num,stu[i].name, stu[i].money,stu[i].mode);
        }
    }
    freopen(CONSOLE, "w", stdout);
}

//保存食物信息
void savefood(food *fd){
    freopen(FOOD_FILE, "w", stdout);

    for(int i = 0; i<NUM; i++){
        if(strlen(fd[i].id) != 0){
            printf("%s %s %s %s\n",fd[i].id,fd[i].name, fd[i].price,fd[i].num);
        }
    }
    freopen(CONSOLE, "w", stdout);

}

//保存记录信息
void saverecord(record *re){
    freopen(RECORD_FILE, "w", stdout);

    for(int i=0;i<NUM;i++){
        if(strlen(re[i].stu_id) != 0){
            printf("%s %s %s %s\n",re[i].stu_id,re[i].food_id,re[i].food_price,re[i].record_time);
        }
    }
    freopen(CONSOLE, "w", stdout);
}

//================ 管理员功能实现 ================
//注册学生卡，默认激活
void regist(){
    char cardnum[20],name[20]; //接收用户输入
    int money,mode=0; //标记使用

    printf(" 输入卡号：");
    scanf("%s",cardnum);
    printf(" 输入姓名：");
    scanf("%s",name);
    printf(" 输入余额：");
    scanf("%d",&money);

    // 文件指针
    FILE* fp = fopen(USER_FILE, "a+");

    // 输出到文件
    fputs(cardnum, fp);  fputs(" ", fp);
    fputs(name, fp);  fputs(" ", fp);
    char str1[20];
    itoa(money, str1, 10);
    fputs(str1, fp);  fputs(" ", fp);
    char str2[20];
    itoa(mode, str2, 10);
    fputs(str2, fp);  fputs("\n", fp);
    // 关闭文件
    fclose(fp);
    printf(" 注册成功！\n");

    rerun();//重新启动程序
}

//充值
void charge(student *stu){
    readfile(stu);
    char num[20];
    char charge_num[999];
    int charge_money=0,flag=0;
    //printf(" 请输入要充值的卡号：");
    //scanf("%s",num);
    //printf(" 请输入充值金额：");
    //scanf("%s",charge_num);
    charge_money=atol(charge_num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            charge_money=atol(stu[i].money)+charge_money;
            ltoa(charge_money,charge_num,10);
            strcpy(stu[i].money,charge_num);
            flag=1;
            printf(" 充值成功！\n");
            break;
        }
    }
    if(flag==0) printf(" 没有该卡!\n") ;
    savefile(stu);

    rerun();//重新启动程序
}

//挂失
void report_of_loss(student *stu){
    readfile(stu);
    int flag=-1;//做标记
    char num[20];
    printf(" 请输入要挂失的卡号：");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            flag=i;
            strcpy(stu[i].mode,"1");
            printf(" 挂失成功！\n");
            break;
        }
    }
    if(flag==-1) printf(" 查无此卡，请先注册！\n");
    savefile(stu);  //将关键信息保存

    rerun();//重新启动程序
}

//解挂
void hanging_solutions(student *stu){
    readfile(stu);
    int flag=-1;
    char num[20];

    printf(" 请输入要解挂的卡号：");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            flag=i;
            strcpy(stu[i].mode,"0");
            printf(" 解挂成功！\n");
            break;
        }
    }
    if(flag==-1) printf(" 查无此卡，请先注册！\n");
    savefile(stu);

    rerun();//重新启动程序
}

//注销
void del(student *stu){
    readfile(stu);
    int flag =-1;
    char num[20];
    printf(" 请输入要注销的卡号：");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        //找到卡后置空
        if(strcmp(stu[i].card_num,num)==0){
            flag=i;
            strcpy(stu[i].card_num,"");
            strcpy(stu[i].name,"");
            strcpy(stu[i].money,"");
            strcpy(stu[i].mode,"");
            printf(" 注销成功！\n") ;
        }
    }
    if(flag==-1) printf(" 查无此卡，请先注册！\n");
    savefile(stu);
    rerun();
}

//录入菜品
void input(food *fd){
    char id[20],name[20],price[20],num[10];

    printf(" 输入菜品ID：");
    scanf("%s",id);
    printf(" 输入菜品名称：");
    scanf("%s",name);
    printf(" 输入菜品价格：");
    scanf("%s",price);
    printf(" 输入菜品数量：");
    scanf("%s",num);

    // 文件指针
    FILE* fp = fopen(FOOD_FILE, "a+");

    // 输出到文件
    fputs(id, fp);  fputs(" ", fp);
    fputs(name, fp);  fputs(" ", fp);
    fputs(price, fp);  fputs(" ", fp);
    fputs(num, fp);  fputs("\n", fp);

    // 关闭文件
    fclose(fp);
    printf(" 录入成功！\n");
    rerun();
}

//查询菜品
void check(food *fd){
    readfood(fd);
    char id[20];
    printf(" 请输入需要查询的菜品ID：");
    scanf("%s",id);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(fd[i].id,id)==0){
            printf(" 菜品ID为：%s",fd[i].id);
            printf("  菜品名称为：%s",fd[i].name);
            printf("  菜品价格为：%s",fd[i].price);
            printf("  菜品数量为：%s\n",fd[i].num);
        }
    }

    rerun();
}

//统计功能 （打印所有菜品信息）
void count(food *fd){
    readfood(fd);
    int total_num=0,total_money=0;//菜品数量，总销售额
    for(int i =0;i<NUM-1;i++){
        if(strlen(fd[i].id)!=0){
            printf(" 菜品ID为：%s",fd[i].id);
            printf("  菜品名称为：%s",fd[i].name);
            printf("  菜品价格为：%s",fd[i].price);
            printf("  菜品数量为：%s\n",fd[i].num);
            total_num+=atoi(fd[i].num);
            total_money+=atol(fd[i].num)* atol(fd[i].price);
        }
    }
    printf(" 菜品总数量为：%d\t",total_num);
    printf(" 菜品可销售总金额为：%d\n",total_money);
    rerun();
}

//================ 学生功能实现 ================
//查余额
void surplus(student *stu,char *num){
    readfile(stu);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            printf(" 账户余额为：%s\n",stu[i].money);
        }
    }
    rerun();
}

//消费记录
void sturecord(record *re,char *num){
    readrecord(re);
    int flag=-1;
    for(int i =0;i<BUFLEN-1;i++){
        if(strcmp(re[i].stu_id,num)==0){
            flag=i;
            printf(" 学生卡号为：%s",re[i].stu_id);
            printf("  购买菜品编号为：%s",re[i].food_id);
            printf("  购买菜品价格为：%s",re[i].food_price);
            printf("  购买时间为：%s\n",re[i].record_time);
        }
    }if(flag==-1) printf(" 无记录！\n");
    rerun();
}

//购物
void purchase(student *stu,food *fd,char *num){
    readfile(stu);
    readfood(fd);

    char stu_id[20];
    char food_id[20];
    char food_price[20];
    char record_time[255];
    char ch_fd[10],money[20];
    int re_id1=-1,re_id2=-1,flag=0;
    //获取时间
    time_t t = time( 0 );
    char tmpBuf[BUFLEN];
    strftime(tmpBuf, BUFLEN, "%Y-%m-%d-%H:%M:%S", localtime(&t)); //格式化时间


    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            //找到对应得学生卡后输出菜品
            re_id1=i;
            for(int j =0;j<NUM-1;j++){
                if(strlen(fd[j].id)!=0){
                    printf(" 菜品ID为：%s",fd[j].id);
                    printf("  菜品名称为：%s",fd[j].name);
                    printf("  菜品价格为：%s",fd[j].price);
                    printf("  菜品数量为：%s\n",fd[j].num);
                }
            }
            //购物选择
            printf(" 输入要购买的商品ID：");
            scanf("%s",ch_fd);
            for(int k =0;k<NUM-1;k++){
                if(strcmp(fd[k].id,ch_fd)==0){
                    //找到菜品后 余额和菜价进行比较
                    if(atoi(stu[i].money)>atoi(fd[k].price)&&fd[k].num>0){
                        printf(" 购买成功！\n");
                        re_id2=k;
                        savefile(stu);
                        // 文件指针
                        FILE* fp = fopen(RECORD_FILE, "a+");
                        // 输出到文件
                        fputs(stu[re_id1].card_num, fp);  fputs(" ", fp);
                        fputs(fd[re_id2].id, fp);  fputs(" ", fp);
                        fputs(fd[re_id2].price, fp);  fputs(" ", fp);
                        fputs(tmpBuf, fp);  fputs("\n", fp);
                        // 关闭文件
                        fclose(fp);
                        char re_money[20],remun[10];
                        itoa(atoi(stu[i].money)-atoi(fd[k].price),re_money,10);
                        strcpy(stu[i].money,re_money);
                        itoa(atoi(fd[k].num)-1,remun,10);
                        strcpy(fd[k].num,remun);
                        savefile(stu);
                        savefood(fd);
                    } else printf(" 余额不足，请充值！\n");
                }
            }
        }
    }
    rerun();//重新启动程序
}

//================ 菜单与模式入口================
//管理模式菜单
int admin_menu(){
    int re=0;
    printf("========== 管理模式 ==========\n");
    printf("   * * * 就餐卡相关 * * *\n");
    printf(" [---- Press 1 ：注册----]\n");//  regist
    printf(" [---- Press 2 ：充值----]\n");//  charge
    printf(" [---- Press 3 ：挂失----]\n");//  report_of_loss
    printf(" [---- Press 4 ：解挂----]\n");//  hanging_solutions
    printf(" [---- Press 5 ：注销----]\n\n");//    del
    printf("   * * * 菜品相关* * *\n");
    printf(" [---- Press 6 ：录入菜品----]\n");//    input
    printf(" [---- Press 7 ：查询菜品----]\n");//    check
    printf(" [---- Press 8 ：统计菜品----]\n\n");//  count

    printf(" 请输入您的选择：");
    scanf("%d",&re);
    return re;
}

//学生模式菜单
int stu_menu(){
    int re=0;

    printf("========== 学生模式 ==========\n");
    printf(" [---- Press 1 ：查询余额----]\n");//    surplus
    printf(" [---- Press 2 ：消费记录----]\n");//    record
    printf(" [---- Press 3 ：购买菜品----]\n");//    purchase
    printf(" 请输入您的选择：");
    scanf("%d",&re);
    return re;

}

//管理模式
void admin_mode(student *stu,food *fd){
    int admin_password=0,menu_ch=0;
    printf(" 请输入管理员密码：");
    scanf("%d",&admin_password);
    if(admin_password==password){
        menu_ch = admin_menu();
        switch(menu_ch){
            case 1 :  fflush(stdin);regist();break;//   注册
            case 2 :  fflush(stdin);charge(stu);break;//    充值
            case 3 :  fflush(stdin);report_of_loss(stu);break;//    挂失
            case 4 :  fflush(stdin);hanging_solutions(stu);break;// 解挂
            case 5 :  fflush(stdin);del(stu);break;//   注销
            case 6 :  fflush(stdin);input(fd);break;//  录入
            case 7 :  fflush(stdin);check(fd);break;//  查询
            case 8 :  fflush(stdin);count(fd);break;//  统计
        }
    }else{
        printf(" 密码错误！请确认密码后重试。\n\n");
    }
    admin_mode(stu,fd);//再次载入
}

//学生模式
void stu_mode(student *stu,food *fd,record *re){
    readfile(stu);
    int stu_ch=0,flag=-1;
    char num[20];
    printf(" 请输入您的卡号：");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0 && strcmp(stu[i].mode,"0")==0){
            flag=i;
            stu_ch = stu_menu();
            switch(stu_ch){
                case 1 :  fflush(stdin);surplus(stu,num);break;//   查余额
                case 2 :  fflush(stdin);sturecord(re,num);break;//  查记录
                case 3 :  fflush(stdin);purchase(stu,fd,num);break;//   购买菜品
            }
        }
    }
    if(flag==-1) printf(" 登录出错，请确认该卡是否已注册或处于挂失状态！\n") ;
    rerun();
}

//主菜单显示
int menu(){
    int re=0;
    printf("======== 食堂管理系统 ========\n");
    printf(" [---- Press 1 ：管理模式----]\n");
    printf(" [---- Press 2 ：学生模式----]\n");
    printf(" 请输入您的选择：");
    scanf("%d",&re);
    return re;
}

//重启函数
void rerun(){
    //判断是否重新运行本系统
    char re_star[2];
    printf("\n 目前程序已运行完毕，是否重新启动本程序？(y or else): ");
    scanf("%s",re_star);
    if (strcmp(re_star,"y")==0){
        main();
    } else {
        system("pause");
        exit(0);
    }
}

int initialize(){
    //三个结构体的初始化
    student stu[NUM];
    food fd[NUM];
    record re[BUFLEN];
    init(stu,fd,re);

    //载入文本文件
    readfile(stu);
    readfood(fd);
    readrecord(re);
}
int main1(void){
    //三个结构体的初始化
    student stu[NUM];
    food fd[NUM];
    record re[BUFLEN];
    init(stu,fd,re);

    //载入文本文件
    readfile(stu);
    readfood(fd);
    readrecord(re);

    printf("\n");

    int re_menu=0;
    re_menu=menu();
    if (re_menu==1){
        printf("\n 您将进入管理模式！\n\n");
        admin_mode(stu,fd);
    } else if(re_menu==2){
        printf("\n 您将进入学生模式！\n\n");
        stu_mode(stu,fd,re);
    }else{
        printf(" 输入有误，请重新输入！\n");
        fflush(stdin);  //清空缓冲区
        main();//重新调用初始菜单函数;
    }

    system("pause");
    return 0;

}
