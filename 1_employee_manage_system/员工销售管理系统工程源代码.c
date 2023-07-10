
#define OK 1
#define ERROR 0                                 //用于标明函数返回信息
#define NAMESIZE 20       

#define EMPTY 0
#define ONPOST 1                                //用于标明在职状态
#define QUIT  0
                                                //用于标明函数传递的结构体成员名
#define NAME 1                          //(p->name)
#define PRODUCT_NAME 2                       //(p->product->product_name)

#define DARKYELLOW 6                        //颜色标记
#define WHITE 7
#define GREEN 10
#define DARKBLUE 9
#define WATHET 11
#define RED 12

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <windows.h>

typedef int work;                               //工作状态变量

typedef char orderstrandtype;                   //kmp算法所用串的原型
typedef orderstrandtype orderstrand[NAMESIZE];
typedef int state;

typedef struct  { 
    char product_name[NAMESIZE];
    double product_price;
    int product_quantity;
    double sales_volume;
}sales;             
typedef sales * sale_information;               //产品数据结构体（作为员工数据结点旁支）

typedef struct staff {
    int id;
    char name[NAMESIZE];
    sale_information  product;
    work con;
    struct staff* next;
}staff;                 //员工数据结构体（作为员工链表结点）
typedef staff * staff_ptr;
         
typedef int state ;                                  //定义state 用来标明函数返回信息

/*main下的直接函数原型*/

//void example(staff_ptr* list);

/*数据操作模块下的直接函数原型*/
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

/*显示模块下的直接函数原型*/
state display_operation(staff_ptr list);
void display_staff(staff_ptr list);
void color(int c);
void show_menu_first();
void show_menu_data();
void show_menu_display();
void show_form_head();
void show_product_infor(staff_ptr list);
void show_menu_search();


/*查找模块下的直接函数原型*/
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

/*输入处理模块下的直接函数原型*/
int get_number();
void clear_n();
char* s_gets(char* st, int n);
double get_double();
state get_section_int(int* min, int* max);
state get_section_double(double* min, double* max);
int get_con();

/*文件操作模块下的直接函数原型*/
                                                        //保存文件
void save_staff(staff_ptr* list, char* name);
void read_staff(staff_ptr* list, char* name);                        //读文件



/*主函数——最高层抽象控制*/
int main() {
    staff_ptr stafflist;
    init_staff_chainlist(&stafflist);
    read_staff(&stafflist, "staff.txt");
    //example(&stafflist);
    
    int choice;
    system("cls");
    show_menu_first();
    while (1) {                                     //第一层菜单
        choice= get_number();
        switch (choice) {
            case 1:
                data_operation(&stafflist);        //数据操作
                system("cls");
                show_menu_first();
                break;
            case 2:
                display_operation(stafflist);       //显示操作
                system("cls");
                show_menu_first();
                break;
            case 3:
                search_operation(stafflist);        //查询操作
                system("cls");
                show_menu_first();
                break;
            case 0:
                
                save_staff(&stafflist,"staff.txt");

                printf("\n欢迎再次使用！！！\n");      //退出程序
                printf("\n三秒后自动退出程序！！！\n");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".");
                Sleep(1000);
                printf(".");
                return 0;
            default:
                printf("请正确输入选项:");
                break;
        }
    }
}

/*程序运行选择显示菜单*/
      

/*数据操作模块*/
                                                    //数据操作模块控制函数
state data_operation(staff_ptr* list) {
    int choice;

    id_staff_chainlist(list);
    system("cls");
    show_menu_data();

    while (1) {                             //第二层菜单
        choice = get_number();
        switch (choice) {
            case 1:                         //添加成员操作
                add_staff(list);
                system("cls");
                show_menu_data();
                break;
            case 2:                         //删除成员操作
                dele_quit(list);           
                system("cls");
                show_menu_data();
                break;
            case 3:
                change_staff(list);
                system("cls");
                show_menu_data();
                break;
            case 0:                         //返回上层菜单
                system("cls");
                show_menu_data();
                return OK;
            default:
                printf("请正确输入选项:");
                break;
        
        }
    }
}       
                                                    //展示数据操作菜单

                                                    //初始化成员链表
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
                                                    //添加成员信息
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
    printf("请输入姓名:");
    s_gets(q->name,NAMESIZE);
    

    printf("请输入产品名:");
    s_gets(q->product->product_name, NAMESIZE);
    

    printf("请输入产品单价:");
    q->product->product_price =  get_double();

    printf("请输入销售数量:");
    q->product->product_quantity = get_number();

    q->product->sales_volume = (q->product->product_price) * (q->product->product_quantity);

    printf("请输入在职状态(0表示离职，1表示在职):");
    q->con = get_con();

    printf("添加成功！！！");
    printf("\n按下任意键并退出至上一级菜单.....\n");
    scanf("%c", &c);
    clear_n();

    return OK;
}   
                                                    //单链表冒泡排序
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
                                                    //删除已经离职的成员
state delete_quit(staff_ptr * list) {
    /*staff_ptr p, q;
    int n=0,number=(*list)->id;
    p = *list;
    (*list)->id= 0;
    while (p->next) {
        if (p->next->con==QUIT) {
            q = p->next;
            p->next= q->next;
            free(q);                        由p->next引发的bug当删除一个后会发生跳过
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
        printf("没有找到离职人员（删除了0个条目）.....\n");
    }
    else {
        printf("总共删除了%d个离职人员.....\n",n);
    }
    printf("\n按下任意键并退出至上一级菜单.....\n");
    scanf("%c", &c);
    clear_n();
}

void change_staff(staff_ptr* list) {
    char c;
    int num,i=0;
    staff_ptr p = *list;

    printf("请输入你所要变更的编号：");
    num = get_number();

    if (num>(p->id)) {
        printf("更改了0个条目（未查询到）\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
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
            printf("\n已将编号为%d的成员更改为已离职！\n",num);
        }
        else {
            p->con = 1;
            printf("\n已将编号为%d的成员更改为在职！\n", num);
        }
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        clear_n();
    }
}


/*显示模块*/
                                                    //显示操作控制函数
state display_operation(staff_ptr  list) {
    int choice;
    system("cls");
    show_menu_display();
    while (1) {                                     //第二层菜单
        choice = get_number();
        switch (choice) {
        case 1:                                     //编号排序显示操作
            id_staff_chainlist(&list);
            display_staff(list);              
            system("cls");
            show_menu_display();
            break;
        case 2:
            quantity_staff_chainlist(&list);
            display_staff(list);
            system("cls");                          //销售数量显示排序操作
            show_menu_display();
            break;
        case 3:
            sales_staff_chainlist(&list);
            display_staff(list);
            system("cls");                          //销售额显示排序操作
            show_menu_display();
            break;
        case 0:                                     //返回上级菜单
            return OK;
        default:
            printf("请正确输入选项:");
            break;
        }
    }
}
                                                    //打印显示操作菜单
void show_menu_first() {
    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("            欢迎进入员工销售数据系统                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("以下是系统提供的操作：                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.员工数据的操作                                        ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.员工数据显示                                          ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.员工数据的查询                                        ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("           注意：输入相关序号进入下一操作选择（按下0退出）");
    color(DARKYELLOW);
    printf("*\n*");
    printf("***********************************************************\n");
    color(WHITE);
    printf("请输入你的选项：");
}                           //展示成员信息
void show_menu_data() {
    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("                       数据操作                           ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("以下是系统提供的操作：                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.添加                                                  ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.删除已离职                                            ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.变更员工在职状态                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("   注意：输入相关序号进入下一操作选择（按下0返回上级菜单）");
    color(DARKYELLOW);
    printf("*\n************************************************************\n");
    color(WHITE);
    printf("请输入你的选项：");
}
void show_menu_search() {

    /* printf("************************************************************\n");
    printf("*                       查询操作                           *\n");
    printf("*以下是系统提供的操作：                                    *\n");
    printf("*                                                          *\n");
    printf("*  1.按姓名关键词查找                                      *\n");
    printf("*  2.按编号查找                                            *\n");
    printf("*  3.按销售数量区间查找                                    *\n");
    printf("*  4.按销售额区间查找                                      *\n");
    printf("*  5.按产品名关键词查找                                    *\n");
    printf("*                                                          *\n");
    printf("*   注意：输入相关序号进入下一操作选择（按下0返回上级菜单）*\n");
    printf("************************************************************\n");
    printf("请输入你的选项：");*/

    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("                       查询操作                           ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("以下是系统提供的操作：                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.按姓名关键词查找                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.按编号查找                                            ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.按销售数量区间查找                                    ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  4.按销售额区间查找                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  5.按产品名关键词查找                                    ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("   注意：输入相关序号进入下一操作选择（按下0返回上级菜单）");
    color(DARKYELLOW);
    printf("*\n************************************************************\n");
    color(WHITE);
    printf("请输入你的选项：");
}                                    
void show_menu_display() {

    /*    printf("************************************************************\n");
    printf("*                       显示操作                           *\n");
    printf("*以下是系统提供的操作：                                    *\n");
    printf("*                                                          *\n");
    printf("*  1.编号排序显示                                          *\n");
    printf("*  2.销售数量排序显示                                      *\n");
    printf("*  3.销售额排序显示                                        *\n");
    printf("*                                                          *\n");
    printf("*                                                          *\n");
    printf("*   注意：输入相关序号进入下一操作选择（按下0返回上级菜单）*\n");
    printf("************************************************************\n");
    printf("请输入你的选项：");*/

    color(DARKYELLOW);
    printf("************************************************************\n");
    printf("*");
    color(GREEN);
    printf("                       显示操作                           ");
    color(DARKYELLOW);
    printf("*\n*");
    color(DARKBLUE);
    printf("以下是系统提供的操作：                                    ");
    color(DARKYELLOW);
    printf("*\n*                                                          *\n*");
    color(WATHET);
    printf("  1.编号排序显示                                          ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  2.销售数量排序显示                                      ");
    color(DARKYELLOW);
    printf("*\n*");
    color(WATHET);
    printf("  3.销售额排序显示                                        ");
    color(DARKYELLOW);
    printf("*\n*");
    printf("                                                          *\n");
    printf("*                                                          ");
    printf("*\n*");
    color(RED);
    printf("   注意：输入相关序号进入下一操作选择（按下0返回上级菜单）");
    color(DARKYELLOW);
    printf("*\n************************************************************\n");
    color(WHITE);
    printf("请输入你的选项：");

}
                                                    //打印输出
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
    printf("\n按下任意键退出至上一级菜单.....\n");
    scanf("%c", &c);
    clear_n();
}
void show_form_head() {
    color(DARKYELLOW);
    printf("-------------------------------------------------------------------------------------------------------------\n");
    printf("%-6s|%-14s|%-22s|%-16s|%-16s|%-14s|%-6s\n", "编号", "姓名", "销售产品名", "产品单价（元）", "销售数量(个)", "销售额（元）", "在职状态");
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
        printf("%-5s", "在职\n");
        color(WHITE);
    }
    else {
        color(RED);
        printf("%-5s", "已离职\n");
        color(WHITE);
    }
}
                                                    //更改打印颜色
void color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


/*查询模块*/
                                                    //查询操作控制函数
state search_operation(staff_ptr list) {
    int choice;
    system("cls");
    show_menu_search();
    while (1) {                                     //第二层菜单
        choice = get_number();
        switch (choice) {
            case 1:
                search_name(list,NAME);                  //名字查找操作
                system("cls");
                show_menu_search();
                break;
            case 2:
                id_staff_chainlist(&list);
                search_number(list);                //编号查找操作
                system("cls");
                show_menu_search();
                break;
            case 3:                                 //销售数量区间查找
                quantity_staff_chainlist(&list);
                search_quantity(list);
                system("cls");
                show_menu_search();
                break;
            case 4:                                 //销售额区间查找
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
            case 0:                                 //返回上级菜单
                return OK;      
            default:
                printf("请正确输入选项:");
                break;
        }
    }
}
                                                    //展示查询操作菜单
                   
                                                    //编号查找处理
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
    printf("查询结果如下：\n");
    show_form_head();
    show_product_infor(p);
    
    printf("\n按下任意键并退出至上一级菜单.....\n");
    scanf("%c", &c);
    clear_n();
    return OK;
}
void search_number( staff_ptr list) {
    char c;
    int n;
    printf("请输入你想查询的编号：");
    n = get_number();
    if (!sear_number(n,list)) {
        system("cls");
        printf("查无此人\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        clear_n();
    }
}
                                                    //名字查找处理（主要运用kmp匹配算法查找名字关键词）
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
        printf("\n共查到%d个条目\n",sign);
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        return OK;
    }
    return EMPTY;
}
void search_name(staff_ptr list,int nametype) {
    char target[NAMESIZE];
    char c;
    printf("请输入你想查询的关键词：");
    s_gets(target,NAMESIZE);
    if (!sear_name(target, list,nametype)) {
        system("cls");
        printf("查无此人\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
    }
}                                         
                                                   //销售额查找处理
void sear_sales(double min,double max, staff_ptr list){
    int n = 0;
    char c;
    staff_ptr p = list;
    if (p->id == 0) {
        printf("\n共查到0个条目.....\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        clear_n();
        return;
    }
    p = p->next;
    if (p->product->sales_volume < min) {
        printf("\n共查到0个条目.....\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
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
        printf("\n共查到%d个条目.....\n", n);
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        clear_n();
    }
}
void search_sales(staff_ptr list) {
    double min, max;
    while (!get_section_double(&min, &max)) {
        printf("请正确输入区间！\n");
    }
    system("cls");
    show_form_head();
    sear_sales(min, max, list);
}
                                                   //销售数量查找处理
void sear_quantity(double min, double max, staff_ptr list) {
    int n=0;
    char c;
    staff_ptr p = list;
    if (p->id == 0) {
        printf("\n共查到0个条目.....\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        clear_n();
        return;
    }
    p = p->next;
    if (p->product->product_quantity < min) {
        printf("\n共查到0个条目.....\n");
        printf("\n按下任意键并退出至上一级菜单.....\n");
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
        printf("\n共查到%d个条目.....\n", n);
        printf("\n按下任意键并退出至上一级菜单.....\n");
        scanf("%c", &c);
        clear_n();
    }
}
void search_quantity(staff_ptr list) {
    int min, max;
    while (!get_section_int(&min, &max)) {
        printf("请正确输入区间！\n");
    }
    system("cls");
    show_form_head();
    sear_quantity(min, max, list);
}


/*错入输入处理模块（输入模块）*/
                                                            //更好的处理数字输入提高程序鲁棒性
int get_number() {
    int op;
    while (scanf("%d", &op) != 1) {
        printf("请输入数字：");
        while (getchar() != '\n')
            continue;
    }
    return op;
}     
double get_double() {
    double op;
    while (scanf("%lf", &op) != 1) {
        printf("请输入数字：");
        while (getchar() != '\n')
            continue;
    }
    return op;
}
                                                            //清除缓冲区
void clear_n() {
    while (getchar() != '\n') {
        continue;
    }
}
                                                            //更好的处理字符串的输入提高程序鲁棒性
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
                                                            //针对相关函数的处理的数字输入
state get_section_int(int * min, int *  max) {
    printf("请输入销售数量区间下界：");
    *min = get_number();
    printf("请输入销售数量区间上界：");
    *max = get_number();
    if (*min>*max) {
        return ERROR;
    }
    return OK;
}
state get_section_double(double* min, double* max) {
    printf("请输入销售额区间下界：");
    *min = get_double();
    printf("请输入销售额区间上界：");
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
        printf("请正确输入：");
        number = get_number();
    }
    return number;

}

/*文件操作模块*/
                                                            //保存员工数据
void save_staff(staff_ptr* list,char * name) {
    id_staff_chainlist(list);
    FILE* fp = fopen(name, "wb");
    staff_ptr p=*list;
    char * onjob="在职\n";
    char* offjob = "已离职\n";
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
                                                            //读员工数据
void read_staff(staff_ptr* list, char* name) {
    printf("正在读取文件...\n");
    Sleep(1000);
    FILE* fp = fopen(name, "rb");
    if (!fp) {
        printf("未读取到数据文件！\n");
        printf("正在为您创建新的数据文件...\n");
        fp = fopen(name, "a+b");
        printf("创建成功！\n三秒后自动进入菜单\n");
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
/*测试链表void example(staff_ptr* list) {
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
