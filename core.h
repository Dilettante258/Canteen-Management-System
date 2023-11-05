#ifndef PROJECT_CORE_H
#define PROJECT_CORE_H

#endif //PROJECT_CORE_H
//ͷ�ļ�
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//ȫ�ֱ�������
#define USER_FILE "user.txt"
#define RECORD_FILE "record.txt"
#define FOOD_FILE "food.txt"
#define CONSOLE "CON"
#define BUFLEN 255
#define NUM 50
#define password 123

//================ �ṹ�� ================
struct Student{
    char card_num[20]; //����
    char name[20];//����
    char money[20];//���
    char mode[2];//״̬
};
typedef struct Student student;//����student

struct Food{
    char id[20];
    char name[20];
    char price[20];
    char num[10];
};
typedef struct Food food;//��student��������

struct Record{
    char stu_id[20];
    char food_id[20];
    char food_price[20];
    char record_time[255];
};
typedef struct Record record;//��student��������

//================ �������� ================
//������
int main(void);
//��������
void rerun();
//���˵���ʾ
int menu();
//�ṹ�����ݳ�ʼ��
void init(student *stu,food *fd,record *re);
//���ļ�����ѧ������Ϣ
void readfile(student *stu);
//���ļ������Ʒ��Ϣ
void readfood(food *fd);
//���ļ������¼��Ϣ
void readrecord(record *re);
//����ѧ����Ϣ
void savefile(student *stu);
//����ʳ����Ϣ
void savefood(food *fd);
//�����¼��Ϣ
void saverecord(record *re);

//����ģʽ
void admin_mode(student *stu,food *fd);
//����ģʽ�˵�
int admin_menu();
//ע��ѧ����
void regist();
//��ֵ
void charge(student *stu);
//��ʧ
void report_of_loss(student *stu);
//���
void hanging_solutions(student *stu);
//ע��
void del(student *stu);
//¼���Ʒ
void input(food *fd);
//��ѯ��Ʒ
void check(food *fd);
//ͳ�ƹ��� ����ӡ���в�Ʒ��Ϣ��
void count(food *fd);

//ѧ��ģʽ
void stu_mode(student *stu,food *fd,record *re);
//ѧ��ģʽ�˵�
int stu_menu();
//�����
void surplus(student *stu,char *num);
//���Ѽ�¼
void sturecord(record *re,char *num);
//����
void purchase(student *stu,food *fd,char *num);

//================ ����������ʵ�� ================
//�ṹ�����ݳ�ʼ��
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

//���ļ�����ѧ������Ϣ
void readfile(student *stu){
    int i=0;
    //�����ض��򣬴��ļ����롣
    freopen(USER_FILE, "r", stdin);
    for(i=0;i<NUM;i++){
//      while(~scanf("%s%s%s%s", stu[i].card_num,stu[i].name, stu[i].money,stu[i].mode));
        scanf("%s%s%s%s", stu[i].card_num,stu[i].name, stu[i].money,stu[i].mode);

    }
    //�ض��򷵻�
    freopen("CON", "r", stdin);

}

//���ļ������Ʒ��Ϣ
void readfood(food *fd){
    freopen(FOOD_FILE, "r", stdin);

    for(int i=0;i<NUM;i++){
        scanf("%s%s%s%s", fd[i].id,fd[i].name,fd[i].price,fd[i].num);
    }
    freopen("CON", "r", stdin);

}

//���ļ������¼��Ϣ
void readrecord(record *re){
    freopen(RECORD_FILE, "r", stdin);

    for(int i=0;i<NUM;i++){
        scanf("%s%s%s%s", re[i].stu_id,re[i].food_id,re[i].food_price,re[i].record_time);
    }
    freopen("CON", "r", stdin);
}

//����ѧ����Ϣ
void savefile(student *stu){
    //�ض����ļ������ļ�������
    freopen(USER_FILE, "w", stdout);

    for(int i = 0; i<NUM; i++){
        if(strlen(stu[i].card_num)!=0){
            printf("%s %s %s %s\n",stu[i].card_num,stu[i].name, stu[i].money,stu[i].mode);
        }
    }
    freopen(CONSOLE, "w", stdout);
}

//����ʳ����Ϣ
void savefood(food *fd){
    freopen(FOOD_FILE, "w", stdout);

    for(int i = 0; i<NUM; i++){
        if(strlen(fd[i].id) != 0){
            printf("%s %s %s %s\n",fd[i].id,fd[i].name, fd[i].price,fd[i].num);
        }
    }
    freopen(CONSOLE, "w", stdout);

}

//�����¼��Ϣ
void saverecord(record *re){
    freopen(RECORD_FILE, "w", stdout);

    for(int i=0;i<NUM;i++){
        if(strlen(re[i].stu_id) != 0){
            printf("%s %s %s %s\n",re[i].stu_id,re[i].food_id,re[i].food_price,re[i].record_time);
        }
    }
    freopen(CONSOLE, "w", stdout);
}

//================ ����Ա����ʵ�� ================
//ע��ѧ������Ĭ�ϼ���
void regist(){
    char cardnum[20],name[20]; //�����û�����
    int money,mode=0; //���ʹ��

    printf(" ���뿨�ţ�");
    scanf("%s",cardnum);
    printf(" ����������");
    scanf("%s",name);
    printf(" ������");
    scanf("%d",&money);

    // �ļ�ָ��
    FILE* fp = fopen(USER_FILE, "a+");

    // ������ļ�
    fputs(cardnum, fp);  fputs(" ", fp);
    fputs(name, fp);  fputs(" ", fp);
    char str1[20];
    itoa(money, str1, 10);
    fputs(str1, fp);  fputs(" ", fp);
    char str2[20];
    itoa(mode, str2, 10);
    fputs(str2, fp);  fputs("\n", fp);
    // �ر��ļ�
    fclose(fp);
    printf(" ע��ɹ���\n");

    rerun();//������������
}

//��ֵ
void charge(student *stu){
    readfile(stu);
    char num[20];
    char charge_num[999];
    int charge_money=0,flag=0;
    //printf(" ������Ҫ��ֵ�Ŀ��ţ�");
    //scanf("%s",num);
    //printf(" �������ֵ��");
    //scanf("%s",charge_num);
    charge_money=atol(charge_num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            charge_money=atol(stu[i].money)+charge_money;
            ltoa(charge_money,charge_num,10);
            strcpy(stu[i].money,charge_num);
            flag=1;
            printf(" ��ֵ�ɹ���\n");
            break;
        }
    }
    if(flag==0) printf(" û�иÿ�!\n") ;
    savefile(stu);

    rerun();//������������
}

//��ʧ
void report_of_loss(student *stu){
    readfile(stu);
    int flag=-1;//�����
    char num[20];
    printf(" ������Ҫ��ʧ�Ŀ��ţ�");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            flag=i;
            strcpy(stu[i].mode,"1");
            printf(" ��ʧ�ɹ���\n");
            break;
        }
    }
    if(flag==-1) printf(" ���޴˿�������ע�ᣡ\n");
    savefile(stu);  //���ؼ���Ϣ����

    rerun();//������������
}

//���
void hanging_solutions(student *stu){
    readfile(stu);
    int flag=-1;
    char num[20];

    printf(" ������Ҫ��ҵĿ��ţ�");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            flag=i;
            strcpy(stu[i].mode,"0");
            printf(" ��ҳɹ���\n");
            break;
        }
    }
    if(flag==-1) printf(" ���޴˿�������ע�ᣡ\n");
    savefile(stu);

    rerun();//������������
}

//ע��
void del(student *stu){
    readfile(stu);
    int flag =-1;
    char num[20];
    printf(" ������Ҫע���Ŀ��ţ�");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        //�ҵ������ÿ�
        if(strcmp(stu[i].card_num,num)==0){
            flag=i;
            strcpy(stu[i].card_num,"");
            strcpy(stu[i].name,"");
            strcpy(stu[i].money,"");
            strcpy(stu[i].mode,"");
            printf(" ע���ɹ���\n") ;
        }
    }
    if(flag==-1) printf(" ���޴˿�������ע�ᣡ\n");
    savefile(stu);
    rerun();
}

//¼���Ʒ
void input(food *fd){
    char id[20],name[20],price[20],num[10];

    printf(" �����ƷID��");
    scanf("%s",id);
    printf(" �����Ʒ���ƣ�");
    scanf("%s",name);
    printf(" �����Ʒ�۸�");
    scanf("%s",price);
    printf(" �����Ʒ������");
    scanf("%s",num);

    // �ļ�ָ��
    FILE* fp = fopen(FOOD_FILE, "a+");

    // ������ļ�
    fputs(id, fp);  fputs(" ", fp);
    fputs(name, fp);  fputs(" ", fp);
    fputs(price, fp);  fputs(" ", fp);
    fputs(num, fp);  fputs("\n", fp);

    // �ر��ļ�
    fclose(fp);
    printf(" ¼��ɹ���\n");
    rerun();
}

//��ѯ��Ʒ
void check(food *fd){
    readfood(fd);
    char id[20];
    printf(" ��������Ҫ��ѯ�Ĳ�ƷID��");
    scanf("%s",id);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(fd[i].id,id)==0){
            printf(" ��ƷIDΪ��%s",fd[i].id);
            printf("  ��Ʒ����Ϊ��%s",fd[i].name);
            printf("  ��Ʒ�۸�Ϊ��%s",fd[i].price);
            printf("  ��Ʒ����Ϊ��%s\n",fd[i].num);
        }
    }

    rerun();
}

//ͳ�ƹ��� ����ӡ���в�Ʒ��Ϣ��
void count(food *fd){
    readfood(fd);
    int total_num=0,total_money=0;//��Ʒ�����������۶�
    for(int i =0;i<NUM-1;i++){
        if(strlen(fd[i].id)!=0){
            printf(" ��ƷIDΪ��%s",fd[i].id);
            printf("  ��Ʒ����Ϊ��%s",fd[i].name);
            printf("  ��Ʒ�۸�Ϊ��%s",fd[i].price);
            printf("  ��Ʒ����Ϊ��%s\n",fd[i].num);
            total_num+=atoi(fd[i].num);
            total_money+=atol(fd[i].num)* atol(fd[i].price);
        }
    }
    printf(" ��Ʒ������Ϊ��%d\t",total_num);
    printf(" ��Ʒ�������ܽ��Ϊ��%d\n",total_money);
    rerun();
}

//================ ѧ������ʵ�� ================
//�����
void surplus(student *stu,char *num){
    readfile(stu);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            printf(" �˻����Ϊ��%s\n",stu[i].money);
        }
    }
    rerun();
}

//���Ѽ�¼
void sturecord(record *re,char *num){
    readrecord(re);
    int flag=-1;
    for(int i =0;i<BUFLEN-1;i++){
        if(strcmp(re[i].stu_id,num)==0){
            flag=i;
            printf(" ѧ������Ϊ��%s",re[i].stu_id);
            printf("  �����Ʒ���Ϊ��%s",re[i].food_id);
            printf("  �����Ʒ�۸�Ϊ��%s",re[i].food_price);
            printf("  ����ʱ��Ϊ��%s\n",re[i].record_time);
        }
    }if(flag==-1) printf(" �޼�¼��\n");
    rerun();
}

//����
void purchase(student *stu,food *fd,char *num){
    readfile(stu);
    readfood(fd);

    char stu_id[20];
    char food_id[20];
    char food_price[20];
    char record_time[255];
    char ch_fd[10],money[20];
    int re_id1=-1,re_id2=-1,flag=0;
    //��ȡʱ��
    time_t t = time( 0 );
    char tmpBuf[BUFLEN];
    strftime(tmpBuf, BUFLEN, "%Y-%m-%d-%H:%M:%S", localtime(&t)); //��ʽ��ʱ��


    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0){
            //�ҵ���Ӧ��ѧ�����������Ʒ
            re_id1=i;
            for(int j =0;j<NUM-1;j++){
                if(strlen(fd[j].id)!=0){
                    printf(" ��ƷIDΪ��%s",fd[j].id);
                    printf("  ��Ʒ����Ϊ��%s",fd[j].name);
                    printf("  ��Ʒ�۸�Ϊ��%s",fd[j].price);
                    printf("  ��Ʒ����Ϊ��%s\n",fd[j].num);
                }
            }
            //����ѡ��
            printf(" ����Ҫ�������ƷID��");
            scanf("%s",ch_fd);
            for(int k =0;k<NUM-1;k++){
                if(strcmp(fd[k].id,ch_fd)==0){
                    //�ҵ���Ʒ�� ���Ͳ˼۽��бȽ�
                    if(atoi(stu[i].money)>atoi(fd[k].price)&&fd[k].num>0){
                        printf(" ����ɹ���\n");
                        re_id2=k;
                        savefile(stu);
                        // �ļ�ָ��
                        FILE* fp = fopen(RECORD_FILE, "a+");
                        // ������ļ�
                        fputs(stu[re_id1].card_num, fp);  fputs(" ", fp);
                        fputs(fd[re_id2].id, fp);  fputs(" ", fp);
                        fputs(fd[re_id2].price, fp);  fputs(" ", fp);
                        fputs(tmpBuf, fp);  fputs("\n", fp);
                        // �ر��ļ�
                        fclose(fp);
                        char re_money[20],remun[10];
                        itoa(atoi(stu[i].money)-atoi(fd[k].price),re_money,10);
                        strcpy(stu[i].money,re_money);
                        itoa(atoi(fd[k].num)-1,remun,10);
                        strcpy(fd[k].num,remun);
                        savefile(stu);
                        savefood(fd);
                    } else printf(" ���㣬���ֵ��\n");
                }
            }
        }
    }
    rerun();//������������
}

//================ �˵���ģʽ���================
//����ģʽ�˵�
int admin_menu(){
    int re=0;
    printf("========== ����ģʽ ==========\n");
    printf("   * * * �ͲͿ���� * * *\n");
    printf(" [---- Press 1 ��ע��----]\n");//  regist
    printf(" [---- Press 2 ����ֵ----]\n");//  charge
    printf(" [---- Press 3 ����ʧ----]\n");//  report_of_loss
    printf(" [---- Press 4 �����----]\n");//  hanging_solutions
    printf(" [---- Press 5 ��ע��----]\n\n");//    del
    printf("   * * * ��Ʒ���* * *\n");
    printf(" [---- Press 6 ��¼���Ʒ----]\n");//    input
    printf(" [---- Press 7 ����ѯ��Ʒ----]\n");//    check
    printf(" [---- Press 8 ��ͳ�Ʋ�Ʒ----]\n\n");//  count

    printf(" ����������ѡ��");
    scanf("%d",&re);
    return re;
}

//ѧ��ģʽ�˵�
int stu_menu(){
    int re=0;

    printf("========== ѧ��ģʽ ==========\n");
    printf(" [---- Press 1 ����ѯ���----]\n");//    surplus
    printf(" [---- Press 2 �����Ѽ�¼----]\n");//    record
    printf(" [---- Press 3 �������Ʒ----]\n");//    purchase
    printf(" ����������ѡ��");
    scanf("%d",&re);
    return re;

}

//����ģʽ
void admin_mode(student *stu,food *fd){
    int admin_password=0,menu_ch=0;
    printf(" ���������Ա���룺");
    scanf("%d",&admin_password);
    if(admin_password==password){
        menu_ch = admin_menu();
        switch(menu_ch){
            case 1 :  fflush(stdin);regist();break;//   ע��
            case 2 :  fflush(stdin);charge(stu);break;//    ��ֵ
            case 3 :  fflush(stdin);report_of_loss(stu);break;//    ��ʧ
            case 4 :  fflush(stdin);hanging_solutions(stu);break;// ���
            case 5 :  fflush(stdin);del(stu);break;//   ע��
            case 6 :  fflush(stdin);input(fd);break;//  ¼��
            case 7 :  fflush(stdin);check(fd);break;//  ��ѯ
            case 8 :  fflush(stdin);count(fd);break;//  ͳ��
        }
    }else{
        printf(" ���������ȷ����������ԡ�\n\n");
    }
    admin_mode(stu,fd);//�ٴ�����
}

//ѧ��ģʽ
void stu_mode(student *stu,food *fd,record *re){
    readfile(stu);
    int stu_ch=0,flag=-1;
    char num[20];
    printf(" ���������Ŀ��ţ�");
    scanf("%s",num);
    for(int i =0;i<NUM-1;i++){
        if(strcmp(stu[i].card_num,num)==0 && strcmp(stu[i].mode,"0")==0){
            flag=i;
            stu_ch = stu_menu();
            switch(stu_ch){
                case 1 :  fflush(stdin);surplus(stu,num);break;//   �����
                case 2 :  fflush(stdin);sturecord(re,num);break;//  ���¼
                case 3 :  fflush(stdin);purchase(stu,fd,num);break;//   �����Ʒ
            }
        }
    }
    if(flag==-1) printf(" ��¼������ȷ�ϸÿ��Ƿ���ע����ڹ�ʧ״̬��\n") ;
    rerun();
}

//���˵���ʾ
int menu(){
    int re=0;
    printf("======== ʳ�ù���ϵͳ ========\n");
    printf(" [---- Press 1 ������ģʽ----]\n");
    printf(" [---- Press 2 ��ѧ��ģʽ----]\n");
    printf(" ����������ѡ��");
    scanf("%d",&re);
    return re;
}

//��������
void rerun(){
    //�ж��Ƿ��������б�ϵͳ
    char re_star[2];
    printf("\n Ŀǰ������������ϣ��Ƿ���������������(y or else): ");
    scanf("%s",re_star);
    if (strcmp(re_star,"y")==0){
        main();
    } else {
        system("pause");
        exit(0);
    }
}

int initialize(){
    //�����ṹ��ĳ�ʼ��
    student stu[NUM];
    food fd[NUM];
    record re[BUFLEN];
    init(stu,fd,re);

    //�����ı��ļ�
    readfile(stu);
    readfood(fd);
    readrecord(re);
}
int main1(void){
    //�����ṹ��ĳ�ʼ��
    student stu[NUM];
    food fd[NUM];
    record re[BUFLEN];
    init(stu,fd,re);

    //�����ı��ļ�
    readfile(stu);
    readfood(fd);
    readrecord(re);

    printf("\n");

    int re_menu=0;
    re_menu=menu();
    if (re_menu==1){
        printf("\n �����������ģʽ��\n\n");
        admin_mode(stu,fd);
    } else if(re_menu==2){
        printf("\n ��������ѧ��ģʽ��\n\n");
        stu_mode(stu,fd,re);
    }else{
        printf(" �����������������룡\n");
        fflush(stdin);  //��ջ�����
        main();//���µ��ó�ʼ�˵�����;
    }

    system("pause");
    return 0;

}
