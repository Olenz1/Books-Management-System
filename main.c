#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Book information processing module
typedef struct bookinfo
{
    char name[20];
    float price;
    int num;
}bookInfo;
typedef struct _node
{
    bookInfo data;
    struct _node* next;
}Node;
Node* createHead()
{
    Node* headNode = (Node*)malloc(sizeof(Node));
    headNode->next = NULL;
    return headNode;
}
Node* createNode(bookInfo data)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
void printList(Node* list)
{
    Node* pMove = list->next;
    while (pMove != NULL)
    {
        printf("%s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }
}
/*
void insertNodeByHead(Node* headNode, bookInfo bookInfo)
{
    Node* newNode = createNode(bookInfo);
    newNode->next = headNode->next;
    headNode->next = newNode;
}
*/
void insertNodeByTail(Node* headNode, bookInfo bookInfo)
{
    Node* newNode = createNode(bookInfo);
    Node* pMove = headNode;
    while(pMove->next)
    {
        pMove = pMove->next;
    }
    pMove->next = newNode;
}
Node* searchBookByName(Node* headNode, char* bookName)
{
    Node* pMove = headNode->next;
    while (pMove->next != NULL && pMove->data.name != bookName)
    {
        pMove = pMove->next;
    }
    if (pMove == NULL)
    {
        printf("该书籍未在此系统登记！\n");
        return;
    } else {
        return pMove;
    }
}
/*
void borrowBookByName(Node** headNode, char* bookName)
{
    Node* result = searchBookByName(*headNode, bookName);
    result->data.num--;
    printf("书籍借阅成功！\n");
}
void returnBookByName(Node** headNode, char* bookName)
{
    Node* result = searchBookByName(*headNode, bookName);
    result->data.num++;
    printf("书籍归还成功！\n");
}
*/
void deleteNodeByName(Node** headNode, char* bookName)
{
    Node* pMove = *headNode;
    Node* pivit = pMove->next;
    while(pivit != NULL && strcmp(pivit->data.name, bookName))//pivit->data.name != bookName 这里字符串是一致的，但式子实质上是在比较地址。
    {   
        pivit = pivit->next;
    }
    if (pivit == NULL)
    {
        printf("该系统未登记该书籍!\n");
        return;
    }
    else {
        pMove->next = pivit->next;
        free(pivit);
        pivit = NULL;
        printf("成功删除书籍!\n");
    }
}
void saveInfoToFile(const char* fileName, Node* headNode)
{
    FILE* fp = fopen(fileName, "w");
    Node* pMove = headNode->next;
    while (pMove->next)
    {
        fprintf("%s\t%.1f\t%d\n", pMove->data.name, pMove->data.price, pMove->data.num);
        pMove = pMove->next;
    }
    fclose(fp);
}
void readInfoFromFile(const char* fileName, Node** headNode)
{
    FILE* fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        fp = fopen(fileName, "w+");
    }
    bookInfo tempData;
    while (fscanf(fp, "%s\t%f\t%d\n", tempData.name, &tempData.price, &tempData.num) != EOF)
    {
        insertNodeByTail(&(*headNode), tempData);
    }

}

void menu()
{
    printf("-------------------------------\n");
    printf("\t图书信息管理系统\n");
    printf("-------------------------------\n");
    printf("\t  0.退出系统\t\n");
    printf("\t  1.登记书籍\t\n");
    printf("\t  2.浏览书籍\t\n");
    printf("\t  3.借阅书籍\t\n");
    printf("\t  4.归还书籍\t\n");
    printf("\t  5.删除书籍\t\n");
    printf("\t  6.书籍排序\t\n");
    printf("\t  7.查找书籍\t\n");
    printf("-------------------------------\n");

}

void keyDown(Node** pList)
{
    Node* result;
    bookInfo tempInfo;
    int keyBoard;
    printf("请输入数字0-7：");
    scanf_s("%d", &keyBoard);
    switch (keyBoard)
    {
    case 0:
        printf("【退出系统】");
        printf("\n退出成功!\n");
        exit(0);
    case 1:
        printf("【登记】");
        printf("\n请依次输入书名、价格和数量：\n");
        scanf_s("%s", tempInfo.name, 20);
        scanf_s("%f%d", &tempInfo.price, &tempInfo.num);
        //insertNodeByHead(*pList, tempInfo);
        insertNodeByTail(*pList, tempInfo);
        printf("登记成功！\n");
        break;
    case 2:
        printf("【浏览】\n");
        printList(*pList);
        break;
    case 3:
        printf("【借阅书籍】\n");
        printf("请输入要借阅书籍的名称：");
        scanf_s("%s", tempInfo.name, 20);
        result = searchBookByName(*pList, tempInfo.name);
        if (result == NULL)
        {
            printf("该书未在此系统登记！\n");
        }
        else {
            result->data.num--;
            printf("书籍借阅成功！\n");
        }
        break;
    case 4:
        printf("【归还书籍】\n");
        printf("请输入要归还书籍的名称：");
        scanf_s("%s", tempInfo.name, 20);
        result = searchBookByName(*pList, tempInfo.name);
        if (result == NULL)
        {
            printf("该书未在此系统登记！\n");
        }
        else {
            result->data.num++;
            printf("书籍归还成功！\n");
        }
        break;
    case 5:
        printf("【删除书籍】\n");
        printf("请输入要删除书籍的名称：");
        scanf_s("%s", tempInfo.name, 20);
        deleteNodeByName(&(*pList),tempInfo.name);
        break;
    case 6:
        printf("【书籍排序】\n");
        break;
    case 7:
        printf("【查找书籍】\n");
        printf("请输入要查找书籍的名称：");
        scanf_s("%s", tempInfo.name, 20);
        result = searchBookByName(*pList, tempInfo.name);
        if (result == NULL)
        {
            printf("该书未在此系统登记，查询失败！\n");
        } else {
            printf("书籍查询成功！\n");
            printf("%s\t%.1f\t%d\n", result->data.name, result->data.price, result->data.num);
        }
        break;
    }
}

    int main()
    {
        Node* list = createHead();
        while (1) {
            menu();
            keyDown(&list);
            system("pause");
            system("cls");
        }
        system("pause");
        return 0;
    }
