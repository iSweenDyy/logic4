#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* root = NULL;


struct Node* CreateTree(struct Node* root, struct Node* r, int data)
{
    if (r == NULL)
    {
        r = (struct Node*)malloc(sizeof(struct Node));
        if (r == NULL)
        {
            printf("Ошибка выделения памяти\n");
            exit(0);
        }

        r->left = NULL;
        r->right = NULL;
        r->data = data;
        if (root == NULL) return r;          
        if (data < root->data) root->left = r;   
        else root->right = r;                    
        return r;
    }

    
    if (data == r->data)
    {
        printf("Число %d уже есть в дереве, повторно не добавлено\n", data);
        return root;
    }

    if (data < r->data)                      
        CreateTree(r, r->left, data);
    else
        CreateTree(r, r->right, data);

    return root;
}

void print_tree(struct Node* r, int l)
{
    if (r == NULL)
    {
        return;
    }

    print_tree(r->right, l + 1);
    for (int i = 0; i < l; i++)
    {
        printf("   ");
    }
    printf("%d\n", r->data);
    print_tree(r->left, l + 1);
}


struct Node* search(struct Node* r, int data)
{
    if (r == NULL) return NULL;              
    if (data == r->data) return r;           
    if (data < r->data) return search(r->left, data);
    return search(r->right, data);
}


int count_value(struct Node* r, int data)
{
    if (r == NULL) return 0;                 
    if (data < r->data) return count_value(r->left, data);
    if (data > r->data) return count_value(r->right, data);
    return 1;                                
}


void free_tree(struct Node* r)
{
    if (r == NULL) return;
    free_tree(r->left);
    free_tree(r->right);
    free(r);
}


int read_int(const char* prompt)
{
    int x;
    while (1)
    {
        printf("%s", prompt);
        if (scanf("%d", &x) == 1) return x;
        printf("Ошибка: нужно ввести целое число\n");
        while (getchar() != '\n');           
    }
}

int main()
{
    setlocale(LC_ALL, "");

    int D, choice;

    printf("-1 - окончание построения дерева\n");
    while (1)
    {
        D = read_int("Введите число: ");
        if (D == -1)
        {
            printf("Построение дерева окончено\n\n");
            break;
        }
        root = CreateTree(root, root, D);
    }

    printf("Дерево (корень слева):\n");
    print_tree(root, 0);

    
    do
    {
        printf("\n1 - найти число, 2 - посчитать вхождения, 0 - выход\n");
        choice = read_int("Выбор: ");

        if (choice == 1)
        {
            D = read_int("Какое число искать: ");
            if (search(root, D) != NULL) printf("Число %d найдено в дереве\n", D);
            else printf("Числа %d в дереве нет\n", D);
        }
        else if (choice == 2)
        {
            D = read_int("Вхождения какого числа посчитать: ");
            printf("Число %d встречается %d раз(а)\n", D, count_value(root, D));
        }
    } while (choice != 0);

    free_tree(root);
    return 0;
}