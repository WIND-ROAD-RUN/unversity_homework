
#define OK 1
#define ERROR 0                                 //���ڱ�������������Ϣ
#define NAMESIZE 20       

#define EMPTY 0
#define ONPOST 1                                //���ڱ�����ְ״̬
#define QUIT  0
                                                //���ڱ����������ݵĽṹ���Ա��
#define NAME 1                          //(p->name)
#define PRODUCT_NAME 2                       //(p->product->product_name)

#define DARKYELLOW 6                        //��ɫ���
#define WHITE 7
#define GREEN 10
#define DARKBLUE 9
#define WATHET 11
#define RED 12

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

typedef int work;                               //����״̬����

typedef char orderstrandtype;                   //kmp�㷨���ô���ԭ��
typedef orderstrandtype orderstrand[NAMESIZE];
typedef int state;

typedef struct  { 
    char product_name[NAMESIZE];
    double product_price;
    int product_quantity;
    double sales_volume;
}sales;             
typedef sales * sale_information;               //��Ʒ���ݽṹ�壨��ΪԱ�����ݽ����֧��

typedef struct staff {
    int id;
    char name[NAMESIZE];
    sale_information  product;
    work con;
    struct staff* next;
}staff;                 //Ա�����ݽṹ�壨��ΪԱ�������㣩
typedef staff * staff_ptr;
         
typedef int state ;                                  //����state ������������������Ϣ

/*main�µ�ֱ�Ӻ���ԭ��*/

//void example(staff_ptr* list);

/*���ݲ���ģ���µ�ֱ�Ӻ���ԭ��*/
state data_operation(staff_ptr* list);

state init_staff_chainlist(staff_ptr * list);
state add_staff(staff_ptr * list);
state sales_staff_chainlist(staff_ptr* list);
state id_staff_chainlist(staff_ptr* list);
state quantity_staff_chainlist(staff_ptr* list);
void swap_staff(staff_ptr* list);
state delete_quit(staff_ptr* list);
void dele_quit(staff_ptr* list);
void  insert_staff(staff_ptr* list, staff_ptr sta);
void change_staff(staff_ptr* list);

/*��ʾģ���µ�ֱ�Ӻ���ԭ��*/
state display_operation(staff_ptr list);
void display_staff(staff_ptr list);
void color(int c);
void show_menu_first();
void show_menu_data();
void show_menu_display();
void show_form_head();
void show_product_infor(staff_ptr list);
void show_menu_search();


/*����ģ���µ�ֱ�Ӻ���ԭ��*/
state search_operation(staff_ptr list);

int search_ordetstrand(orderstrand templatestrand, orderstrand contraststrand, int num);
state sear_number(int n,staff_ptr list);
void search_number(staff_ptr list);

void inti_name(char* name,char * inti_tar);
state sear_name(char* target, staff_ptr list,int nametype);
void search_name(staff_ptr list,int nametype);

void sear_sales(double min, double max,staff_ptr list);
void search_sales(staff_ptr list);
void sear_quantity(double min, double max, staff_ptr list);
void search_quantity(staff_ptr list);

/*���봦��ģ���µ�ֱ�Ӻ���ԭ��*/
int get_number();
void clear_n();
char* s_gets(char* st, int n);
double get_double();
state get_section_int(int* min, int* max);
state get_section_double(double* min, double* max);
int get_con();

/*�ļ�����ģ���µ�ֱ�Ӻ���ԭ��*/
                                                        //�����ļ�
void save_staff(staff_ptr* list, char* name);
void read_staff(staff_ptr* list, char* name);                        //���ļ�



/*������������߲�������*/
int main() {
    staff_ptr stafflist;
    init_staff_chainlist(&stafflist);
    read_staff(&stafflist, "staff.txt");
    //example(&stafflist);
    
    int choice;
    system("cls");
    show_menu_first();
    while (1) {                                     //��һ��˵�
        choice= get_number();
        switch (choice) {
            case 1:
                data_operation(&stafflist);        //���ݲ���
                system("cls");
                show_menu_first();
                break;
            case 2:
                display_operation(stafflist);       //��ʾ����
                system("cls");
                show_menu_first();
                break;
            case 3:
                search_operation(stafflist);        //��ѯ����
                system("cls");
                show_menu_first();
                break;
            case 0:
                
                save_staff(&stafflist,"staff.txt");

                printf("\n��ӭ�ٴ�ʹ�ã�����\n");      //�˳�����
                printf("\n������Զ��˳����򣡣���\n");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".");
                return 0;
            default:
                printf("����ȷ����ѡ��:");
                break;
        }
    }
}

/*��������ѡ����ʾ�˵�*/
      

/*���ݲ���ģ��*/
                                                    //���ݲ���ģ����ƺ���
state data_operation(staff_ptr* list) {
    int choice;

    id_staff_chainlist(list);
    system("cls");
    show_menu_data();

    while (1) {                             //�ڶ���˵�
        choice = get_number();
        switch (choice) {
            case 1:                         //��ӳ�Ա����
                add_staff(list);
                system("cls");
                show_menu_data();
                break;
            case 2:                         //ɾ����Ա����
                dele_quit(list);           
                system("cls");
                show_menu_data();
                break;
            case 3:
                change_staff(list);
                system("cls");
                show_menu_data();
                break;
            case 0:                         //�����ϲ�˵�
                system("cls");
                show_menu_data();
                return OK;
            default:
                printf("����ȷ����ѡ��:");
                break;
        
        }
    }
}       
                                                    //չʾ���ݲ����˵�

                                                    //��ʼ����Ա����
state init_staff_chainlist(staff_ptr * list) {
    staff_ptr p;
    *list = (staff_ptr)malloc(sizeof(staff));
    p = *list;
    if (!p) {
        return ERROR;
    }
    p->id = 0;
    p->next = NULL;
    p->product = NULL;
    p->con = ONPOST;
    return OK;
}       
                                                    //��ӳ�Ա��Ϣ
state add_staff(staff_ptr* list) {
    char c;
    staff_ptr p,q;
    sale_information s;

    p = *list;
    q = (staff_ptr)malloc(sizeof(staff));

    if (!q) {
        return ERROR;
    }
    p->id++;
    while (p->next) {
        p = p->next;
    }
    p->next = q;
    q->next = NULL;
    q->id = (*list)->id;

    s = (sale_information)malloc(sizeof(sales));
    if (!s) {
        return ERROR;
    }
    q->product = s;
    
    clear_n();
    printf("����������:");
    s_gets(q->name,NAMESIZE);
    

    printf("�������Ʒ��:");
    s_gets(q->product->product_name, NAMESIZE);
    

    printf("�������Ʒ����:");
    q->product->product_price =  get_double();

    printf("��������������:");
    q->product->product_quantity = get_number();

    q->product->sales_volume = (q->product->product_price) * (q->product->product_quantity);

    printf("��������ְ״̬(0��ʾ��ְ��1��ʾ��ְ):");
    q->con = get_con();

    printf("��ӳɹ�������");
    printf("\n������������˳�����һ���˵�.....\n");
    scanf("%c", &c);
    clear_n();

    return OK;
}   
                                                    //������ð������
state sales_staff_chainlist(staff_ptr* list) {
    int i, i_;
    staff_ptr p = *list;
    if (p->id < 2) {
        return OK;
    }
    for (i_ = (*list)->id - 1; i_ > 0; i_--) {
        for (i = 0, p = *list; i < i_; i++) {
            if ((p->next->product->sales_volume) < (p->next->next->product->sales_volume)) {
                swap_staff(&p);
            }
            p = p->next;
        }
    }
    return OK;
}
state id_staff_chainlist(staff_ptr* list) {
    int i, i_;
    staff_ptr p = *list;
    if (p->id < 2) {
        return OK;
    }
    for (i_ = (*list)->id - 1; i_ > 0; i_--) {
        for (i = 0, p = *list; i < i_; i++) {
            if ((p->next->id) > (p->next->next->id)) {
                swap_staff(&p);
            }
            p = p->next;
        }
    }
    return OK;
}
state quantity_staff_chainlist(staff_ptr* list) {
    int i, i_;
    staff_ptr p = *list;
    if (p->id < 2) {
        return OK;
    }
    for (i_ = (*list)->id - 1; i_ > 0; i_--) {
        for (i = 0, p = *list; i < i_; i++) {
            if ((p->next->product->product_quantity) < (p->next->next->product->product_quantity)) {
                swap_staff(&p);
            }
            p = p->next;
        }
    }

    return OK;
}
void swap_staff(staff_ptr* list) {
    staff_ptr  p, q;
    p = (*list)->next;
    (*list)->next = p->next;
    q = p->next->next;
    p->next->next = p;
    p->next = q;
}
                                                    //ɾ���Ѿ���ְ�ĳ�Ա
state delete_quit(staff_ptr * list) {
    /*staff_ptr p, q;
    int n=0,number=(*list)->id;
    p = *list;
    (*list)->id= 0;
    while (p->next) {
        if (p->next->con==QUIT) {
            q = p->next;
            p->next= q->next;
            free(q);                        ��p->next������bug��ɾ��һ����ᷢ������
            n++;
        }
        q = p->next;
        q->id = p->id + 1;
        p = p->next;
        (*list)->id = number - n;
    }
    return n;*/   
    staff_ptr p, q;
    int n = 0, number = (*list)->id;
    p = *list;
    (*list)->id = 0;
    while (p->next) {
        if (p->next->con==QUIT) {
            q = p->next;
            if (q->next) {
                q->next->id = p->id + 1;
            }
            p->next = q->next;
            free(q);
            n++;
        }
        else {
            q = p->next;
            q->id = p->id + 1;
            p = p->next;
        }
    }
    (*list)->id = number - n;
    return n;
}
void dele_quit(staff_ptr* list) {
    char c;
    int n;
    n = delete_quit(list);
    system("cls");
    if (n==0) {
        printf("û���ҵ���ְ��Ա��ɾ����0����Ŀ��.....\n");
    }
    else {
        printf("�ܹ�ɾ����%d����ְ��Ա.....\n",n);
    }
    printf("\n������������˳�����һ���˵�.....\n");
    scanf("%c", &c);
    clear_n();
}

void change_staff(staff_ptr* list) {
    char c;
    int num,i=0;
    staff_ptr p = *list;

    printf("����������Ҫ����ı�ţ�");
    num = get_number();

    if (num>(p->id)) {
        printf("������0����Ŀ��δ��ѯ����\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
    else {
        while (i<num) {
            p = p->next;
            i++;
        }
        if (p->con==1) {
            p->con = 0;
            printf("\n�ѽ����Ϊ%d�ĳ�Ա����Ϊ����ְ��\n",num);
        }
        else {
            p->con = 1;
            printf("\n�ѽ����Ϊ%d�ĳ�Ա����Ϊ��ְ��\n", num);
        }
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
}


/*��ʾģ��*/
                                                    //��ʾ�������ƺ���
state display_operation(staff_ptr  list) {
    int choice;
    system("cls");
    show_menu_display();
    while (1) {                                     //�ڶ���˵�
        choice = get_number();
        switch (choice) {
        case 1:                                     //���������ʾ����
            id_staff_chainlist(&list);
            display_staff(list);              
            system("cls");
            show_menu_display();
            break;
        case 2:
            quantity_staff_chainlist(&list);
            display_staff(list);
            system("cls");                          //����������ʾ�������
            show_menu_display();
            break;
        case 3:
            sales_staff_chainlist(&list);
            display_staff(list);
            system("cls");                          //���۶���ʾ�������
            show_menu_display();
            break;
        case 0:                                     //�����ϼ��˵�
            return OK;
        default:
            printf("����ȷ����ѡ��:");
            break;
        }
    }
}
                                                    //��ӡ��ʾ�����˵�
void show_menu_first() {
    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("            ��ӭ����Ա����������ϵͳ                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("������ϵͳ�ṩ�Ĳ�����                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.Ա�����ݵĲ���                                        ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.Ա��������ʾ                                          ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.Ա�����ݵĲ�ѯ                                        ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("           ע�⣺���������Ž�����һ����ѡ�񣨰���0�˳���");
    color(DARKYELLOW);
    printf("*\n*");
    printf("***********************************************************\n");
    color(WHITE);
    printf("���������ѡ�");
}                           //չʾ��Ա��Ϣ
void show_menu_data() {
    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("                       ���ݲ���                           ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("������ϵͳ�ṩ�Ĳ�����                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.���                                                  ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.ɾ������ְ                                            ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.���Ա����ְ״̬                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("   ע�⣺���������Ž�����һ����ѡ�񣨰���0�����ϼ��˵���");
    color(DARKYELLOW);
    printf("*\n************************************************************\n");
    color(WHITE);
    printf("���������ѡ�");
}
void show_menu_search() {

    /* printf("************************************************************\n");
    printf("*                       ��ѯ����                           *\n");
    printf("*������ϵͳ�ṩ�Ĳ�����                                    *\n");
    printf("*                                                          *\n");
    printf("*  1.�������ؼ��ʲ���                                      *\n");
    printf("*  2.����Ų���                                            *\n");
    printf("*  3.�����������������                                    *\n");
    printf("*  4.�����۶��������                                      *\n");
    printf("*  5.����Ʒ���ؼ��ʲ���                                    *\n");
    printf("*                                                          *\n");
    printf("*   ע�⣺���������Ž�����һ����ѡ�񣨰���0�����ϼ��˵���*\n");
    printf("************************************************************\n");
    printf("���������ѡ�");*/

    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("                       ��ѯ����                           ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("������ϵͳ�ṩ�Ĳ�����                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.�������ؼ��ʲ���                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.����Ų���                                            ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.�����������������                                    ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  4.�����۶��������                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  5.����Ʒ���ؼ��ʲ���                                    ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("   ע�⣺���������Ž�����һ����ѡ�񣨰���0�����ϼ��˵���");
    color(DARKYELLOW);
    printf("*\n************************************************************\n");
    color(WHITE);
    printf("���������ѡ�");
}                                    
void show_menu_display() {

    /*    printf("************************************************************\n");
    printf("*                       ��ʾ����                           *\n");
    printf("*������ϵͳ�ṩ�Ĳ�����                                    *\n");
    printf("*                                                          *\n");
    printf("*  1.���������ʾ                                          *\n");
    printf("*  2.��������������ʾ                                      *\n");
    printf("*  3.���۶�������ʾ                                        *\n");
    printf("*                                                          *\n");
    printf("*                                                          *\n");
    printf("*   ע�⣺���������Ž�����һ����ѡ�񣨰���0�����ϼ��˵���*\n");
    printf("************************************************************\n");
    printf("���������ѡ�");*/

    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("                       ��ʾ����                           ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("������ϵͳ�ṩ�Ĳ�����                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.���������ʾ                                          ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.��������������ʾ                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.���۶�������ʾ                                        ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("   ע�⣺���������Ž�����һ����ѡ�񣨰���0�����ϼ��˵���");
    color(DARKYELLOW);
    printf("*\n************************************************************\n");
    color(WHITE);
    printf("���������ѡ�");

}
                                                    //��ӡ���
void display_staff(staff_ptr list) {
    char c;
    staff_ptr p;

    system("cls");
    show_form_head();
   
    p = list;
    int i=0;
    while (i<(list->id)) {
        p = p->next;
        show_product_infor(p);
        i++;
    }
    printf("\n����������˳�����һ���˵�.....\n");
    scanf("%c", &c);
    clear_n();
}
void show_form_head() {
    color(DARKYELLOW);
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("%-6s|%-14s|%-22s|%-16s|%-16s|%-14s|%-6s\n", "���", "����", "���۲�Ʒ��", "��Ʒ���ۣ�Ԫ��", "��������(��)", "���۶Ԫ��", "��ְ״̬");
    printf("-------------------------------------------------------------------------------------------------------------\n");
    color(WHITE);
}
void show_product_infor(staff_ptr p) {
    color(DARKBLUE);
    printf("%-7d", p->id);
    printf("%-15s", p->name);
    printf("%-23s", p->product->product_name);
    printf("%-17.2lf", p->product->product_price);
    printf("%-17d", p->product->product_quantity);
    printf("%-15.2lf", p->product->sales_volume);
    if ((p->con) == ONPOST) {
        color(GREEN);
        printf("%-5s", "��ְ\n");
        color(WHITE);
    }
    else {
        color(RED);
        printf("%-5s", "����ְ\n");
        color(WHITE);
    }
}
                                                    //���Ĵ�ӡ��ɫ
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


/*��ѯģ��*/
                                                    //��ѯ�������ƺ���
state search_operation(staff_ptr list) {
    int choice;
    system("cls");
    show_menu_search();
    while (1) {                                     //�ڶ���˵�
        choice = get_number();
        switch (choice) {
            case 1:
                search_name(list,NAME);                  //���ֲ��Ҳ���
                system("cls");
                show_menu_search();
                break;
            case 2:
                id_staff_chainlist(&list);
                search_number(list);                //��Ų��Ҳ���
                system("cls");
                show_menu_search();
                break;
            case 3:                                 //���������������
                quantity_staff_chainlist(&list);
                search_quantity(list);
                system("cls");
                show_menu_search();
                break;
            case 4:                                 //���۶��������
                sales_staff_chainlist(&list);
                search_sales(list);
                system("cls");
                show_menu_search();
                break;
            case 5:
                search_name(list, PRODUCT_NAME);
                system("cls");
                show_menu_search();
                break;
            case 0:                                 //�����ϼ��˵�
                return OK;      
            default:
                printf("����ȷ����ѡ��:");
                break;
        }
    }
}
                                                    //չʾ��ѯ�����˵�
                   
                                                    //��Ų��Ҵ���
state sear_number(int n, staff_ptr list) {
    char c;
    int i=0;
    staff_ptr p;
    p = list;

    if (n>list->id) {
        return EMPTY;
    }

    while (i<n) {
        p = p->next;
        i++;
    }

    system("cls");
    printf("��ѯ������£�\n");
    show_form_head();
    show_product_infor(p);
    
    printf("\n������������˳�����һ���˵�.....\n");
    scanf("%c", &c);
    clear_n();
    return OK;
}
void search_number( staff_ptr list) {
    char c;
    int n;
    printf("�����������ѯ�ı�ţ�");
    n = get_number();
    if (!sear_number(n,list)) {
        system("cls");
        printf("���޴���\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
}
                                                    //���ֲ��Ҵ�����Ҫ����kmpƥ���㷨�������ֹؼ��ʣ�
int search_ordetstrand(orderstrand templatestrand, orderstrand contraststrand, int num) {
    int i, k, j;
    i = 1;
    k = 0;
    int next[NAMESIZE];
    next[0] = templatestrand[0];
    next[1] = 0;
    while (i < templatestrand[0]) {
        if (k == 0 || templatestrand[i] == templatestrand[k]) {
            i++;
            k++;
            next[i] = k;
        }
        else {
            k = next[k];
        }
    }
    i = num;
    j = 1;
    while (i <= contraststrand[0] && j <= templatestrand[0]) {
        if (j == 0 || contraststrand[i] == templatestrand[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j > templatestrand[0]) {
        return i - templatestrand[0];
    }
    else {
        return 0;
    }
}
void  inti_name(char* name, char * inti_tar) {
    int i, n;
    n = strlen(name);
    strcpy(inti_tar, name);
    for (i = n; i > 0; i--) {
        inti_tar[i] = inti_tar[i-1];
    }
    inti_tar[0] = n;
}
state sear_name(char * target,staff_ptr list,int nametype) {
    char c;

    int  i,sign,sign_i;
    char inti_tar[NAMESIZE];
    inti_name(target, inti_tar);

    char con_list[NAMESIZE];
    staff_ptr p = list;
    i = sign = 0;

    system("cls");
    show_form_head();
    if (nametype==1) {
        while (i < (list->id)) {
            p = p->next;
            inti_name(p->name, con_list);
            sign_i = search_ordetstrand(inti_tar, con_list, 1);
            if (sign_i) {
                show_product_infor(p);
                sign++;
            }
            i++;
        }
    }
    else {
        while (i < (list->id)) {
            p = p->next;
            inti_name(p->product->product_name, con_list);
            sign_i = search_ordetstrand(inti_tar, con_list, 1);
            if (sign_i) {
                show_product_infor(p);
                sign++;
            }
            i++;
        }
    }
    if (sign) {
        printf("\n���鵽%d����Ŀ\n",sign);
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        return OK;
    }
    return EMPTY;
}
void search_name(staff_ptr list,int nametype) {
    char target[NAMESIZE];
    char c;
    printf("�����������ѯ�Ĺؼ��ʣ�");
    s_gets(target,NAMESIZE);
    if (!sear_name(target, list,nametype)) {
        system("cls");
        printf("���޴���\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
    }
}                                         
                                                   //���۶���Ҵ���
void sear_sales(double min,double max, staff_ptr list){
    int n = 0;
    char c;
    staff_ptr p = list;
    if (p->id == 0) {
        printf("\n���鵽0����Ŀ.....\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
        return;
    }
    p = p->next;
    if (p->product->sales_volume < min) {
        printf("\n���鵽0����Ŀ.....\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
    else {
        while (p && (p->product->sales_volume >= min)) {
            if ((p->product->sales_volume) <= max) {
                show_product_infor(p);
                n++;
            }
            p = p->next;
        }
        printf("\n���鵽%d����Ŀ.....\n", n);
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
}
void search_sales(staff_ptr list) {
    double min, max;
    while (!get_section_double(&min, &max)) {
        printf("����ȷ�������䣡\n");
    }
    system("cls");
    show_form_head();
    sear_sales(min, max, list);
}
                                                   //�����������Ҵ���
void sear_quantity(double min, double max, staff_ptr list) {
    int n=0;
    char c;
    staff_ptr p = list;
    if (p->id == 0) {
        printf("\n���鵽0����Ŀ.....\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
        return;
    }
    p = p->next;
    if (p->product->product_quantity < min) {
        printf("\n���鵽0����Ŀ.....\n");
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
    else{
        while (p && (p->product->product_quantity >= min)) {
            if ((p->product->product_quantity) <= max) {
                show_product_infor(p);
                n++;
            }
            p = p->next;
        }
        printf("\n���鵽%d����Ŀ.....\n", n);
        printf("\n������������˳�����һ���˵�.....\n");
        scanf("%c", &c);
        clear_n();
    }
}
void search_quantity(staff_ptr list) {
    int min, max;
    while (!get_section_int(&min, &max)) {
        printf("����ȷ�������䣡\n");
    }
    system("cls");
    show_form_head();
    sear_quantity(min, max, list);
}


/*�������봦��ģ�飨����ģ�飩*/
                                                            //���õĴ�������������߳���³����
int get_number() {
    int op;
    while (scanf("%d", &op) != 1) {
        printf("���������֣�");
        while (getchar() != '\n')
            continue;
    }
    return op;
}     
double get_double() {
    double op;
    while (scanf("%lf", &op) != 1) {
        printf("���������֣�");
        while (getchar() != '\n')
            continue;
    }
    return op;
}
                                                            //���������
void clear_n() {
    while (getchar() != '\n') {
        continue;
    }
}
                                                            //���õĴ����ַ�����������߳���³����
char* s_gets(char* st, int n)
{
    char* re;
    int i = 0;

    re = fgets(st, n, stdin);
    if (re)
    {
        while (st[i] == '\n') 
            re = fgets(st, n, stdin);
        while (st[i] != '\n' && st[i] != '\0')
            i++;
        if (st[i] == '\n')
            st[i] = '\0';
        else 
            while (getchar() != '\n')
                continue;
    }
    return re;
}
                                                            //�����غ����Ĵ������������
state get_section_int(int * min, int *  max) {
    printf("�������������������½磺");
    *min = get_number();
    printf("�������������������Ͻ磺");
    *max = get_number();
    if (*min>*max) {
        return ERROR;
    }
    return OK;
}
state get_section_double(double* min, double* max) {
    printf("���������۶������½磺");
    *min = get_double();
    printf("���������۶������Ͻ磺");
    *max = get_double();
    if (*min > *max) {
        return ERROR;
    }
    return OK;
}
int get_con() {
    int number;
    number = get_number();
    while (number!=0&&number!=1) {
        printf("����ȷ���룺");
        number = get_number();
    }
    return number;

}

/*�ļ�����ģ��*/
                                                            //����Ա������
void save_staff(staff_ptr* list,char * name) {
    id_staff_chainlist(list);
    FILE* fp = fopen(name, "wb");
    staff_ptr p=*list;
    char * onjob="��ְ\n";
    char* offjob = "����ְ\n";
    while (p->next) {
        p = p->next;
        fprintf(fp,"%-7d", p->id);
        fprintf(fp, "%-15s", p->name);
        fprintf(fp, "%-23s", p->product->product_name);
        fprintf(fp, "%-17.2lf", p->product->product_price);
        fprintf(fp, "%-17d", p->product->product_quantity);
        fprintf(fp, "%-15.2lf", p->product->sales_volume);
        fprintf(fp,"%-2d\n",p->con);
    }
    fclose(fp);

}
                                                            //��Ա������
void read_staff(staff_ptr* list, char* name) {
    printf("���ڶ�ȡ�ļ�...\n");
    Sleep(1000);
    FILE* fp = fopen(name, "rb");
    if (!fp) {
        printf("δ��ȡ�������ļ���\n");
        printf("����Ϊ�������µ������ļ�...\n");
        fp = fopen(name, "a+b");
        printf("�����ɹ���\n������Զ�����˵�\n");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        printf(".");
        Sleep(1000);
        printf(".");
    }
    staff_ptr p = *list;
     staff_ptr ptr;
    ptr = (staff_ptr)malloc(sizeof(staff));
    sale_information s;
    s = (sale_information)malloc(sizeof(sales));
    ptr->product = s;
    /*fscanf(fp, "%d%s%s%lf%d%lf%d", 
        &ptr->id, 
        ptr->name, 
        ptr->product->product_name, 
        &ptr->product->product_price
        , &ptr->product->product_quantity,
        &ptr->product->sales_volume, 
        &ptr->con);

    printf("%-7d", ptr->id);
    printf("%-15s", ptr->name);
    printf("%-23s", ptr->product->product_name);
    printf("%-17.2lf", ptr->product->product_price);
    printf("%-17d", ptr->product->product_quantity);
    printf("%-15.2lf", ptr->product->sales_volume);
    printf("%-2d", ptr->con);

    insert_staff(list, ptr);
    ptr = (staff_ptr)malloc(sizeof(staff));
    s = (sale_information)malloc(sizeof(sales));
    ptr->product = s;
    printf("\n");

    fscanf(fp, "%d%s%s%lf%d%lf%d",
        &ptr->id,
        ptr->name,
        ptr->product->product_name,
        &ptr->product->product_price
        , &ptr->product->product_quantity,
        &ptr->product->sales_volume,
        &ptr->con);
    printf("%-7d", ptr->id);
    printf("%-15s", ptr->name);
    printf("%-23s", ptr->product->product_name);
    printf("%-17.2lf", ptr->product->product_price);
    printf("%-17d", ptr->product->product_quantity);
    printf("%-15.2lf", ptr->product->sales_volume);
    printf("%-2d", ptr->con);

    insert_staff(list, ptr);
    ptr = (staff_ptr)malloc(sizeof(staff));
    s = (sale_information)malloc(sizeof(sales));
    ptr->product = s;Sleep(10000);
*/
    
    /*int i = 0;
    while (i<3) {
        fscanf(fp, "%d%s%s%lf%d%lf%d",
            &ptr->id,
            ptr->name,
            ptr->product->product_name,
            &ptr->product->product_price,
            &ptr->product->product_quantity,
            &ptr->product->sales_volume,
            &ptr->con
        );
        insert_staff(list, ptr);
        ptr = (staff_ptr)malloc(sizeof(staff));
        s = (sale_information)malloc(sizeof(sales));
        ptr->product = s;
        i++;
    }*/
     

    while (fscanf(fp, "%d%s%s%lf%d%lf%d",
        &ptr->id,
        ptr->name, 
        ptr->product->product_name,
        &ptr->product->product_price,
        &ptr->product->product_quantity,
        &ptr->product->sales_volume,
        &ptr->con
        )!=EOF) {
        insert_staff( list, ptr);
        ptr = (staff_ptr)malloc(sizeof(staff));
        s = (sale_information)malloc(sizeof(sales));
        ptr->product = s;
    }
    fclose(fp);
}


void  insert_staff(staff_ptr* list, staff_ptr sta) {
    staff_ptr q = *list;
    (*list)->id++;
    while (q->next) {
        q = q->next;
    }
    sta->next = NULL;
    q->next = sta;
}
/*��������void example(staff_ptr* list) {
    *list = (staff_ptr)malloc(sizeof(staff));
    staff_ptr p = *list;
    p->id = 5;

    p->next = (staff_ptr)malloc(sizeof(staff));
    p = p->next;
    p->id = 1;
    p->name[0] = 'A';
    p->name[1] = '\0';
    p->con = 1;
    p->product = (sale_information)malloc(sizeof(sales));
    p->product->product_price = 10;
    p->product->product_name[0] = 'a';
    p->product->product_name[1] = '\0';
    p->product->product_quantity = 10;
    p->product->sales_volume = (p->product->product_price) * (p->product->product_quantity);

    p->next = (staff_ptr)malloc(sizeof(staff));
    p = p->next;
    p->id = 2;
    p->name[0] = 'B';
    p->name[1] = '\0';
    p->con = 0;
    p->product = (sale_information)malloc(sizeof(sales));
    p->product->product_price = 4;
    p->product->product_name[0] = 'b';
    p->product->product_name[1] = '\0';
    p->product->product_quantity = 8;
    p->product->sales_volume = (p->product->product_price) * (p->product->product_quantity);

    p->next = (staff_ptr)malloc(sizeof(staff));
    p = p->next;
    p->id = 3;
    p->name[0] = 'C';
    p->name[1] = '\0';
    p->con = 1;
    p->product = (sale_information)malloc(sizeof(sales));
    p->product->product_price = 10;
    p->product->product_name[0] = 'c';
    p->product->product_name[1] = '\0';
    p->product->product_quantity = 20;
    p->product->sales_volume = (p->product->product_price) * (p->product->product_quantity);

    p->next = (staff_ptr)malloc(sizeof(staff));
    p = p->next;
    p->id = 4;
    p->name[0] = 'F';
    p->name[1] = '\0';
    p->con = 0;
    p->product = (sale_information)malloc(sizeof(sales));
    p->product->product_price = 48;
    p->product->product_name[0] = 'f';
    p->product->product_name[1] = '\0';
    p->product->product_quantity = 23;
    p->product->sales_volume = (p->product->product_price) * (p->product->product_quantity);

    p->next = (staff_ptr)malloc(sizeof(staff));
    p = p->next;
    p->id = 5;
    p->name[0] = 'V';
    p->name[1] = '\0';
    p->con = 1;
    p->product = (sale_information)malloc(sizeof(sales));
    p->product->product_price = 10;
    p->product->product_name[0] = 'v';
    p->product->product_name[1] = '\0';
    p->product->product_quantity = 98;
    p->product->sales_volume = (p->product->product_price) * (p->product->product_quantity);

    p->next = NULL;

}
*/
