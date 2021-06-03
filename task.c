#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

    /* массив диагностических сообщений об ошибках */
const char *errmsgs[] = {"Ok", "Duplicate key", "Tree overflow", "Input Error", "alloc error", "no such key", "no keys with such a beginning"};

Tree *D_Add(Tree *root){
	int n, n1, n2, rc = 0, flag_t = 0;
	float num;
        char *string = (char *)calloc(15, sizeof(char));
        if(string == NULL) {
                printf("Error try alloc\n");
                return NULL;
        }
        char *key = (char *)calloc(15, sizeof(char));
        if(key == NULL) {
                printf("Error try alloc\n");
                return NULL;
        }
        printf("Enter key: -->\n");
        n = scanf("%s", key);
	if (n == EOF) return NULL;
        printf("Enter number: -->\n");
        n1 = scanf("%f", &num);
	if (n1 == EOF) return NULL;
	printf("Enter string: -->\n");
        n2 = scanf("%s", string);
        if (n2 == EOF) return NULL;
	if(n == 0 || n1 == 0 || n2 == 0) {
                rc = 3;
                printf("%s\n", errmsgs[rc]);
                return root; //ошибка ввода
        }
        root = insert(root, key, num, string, flag_t);
	if (root == NULL) return NULL;
        printf("%s: %s\n", errmsgs[rc], key);
	return root;
}

int D_Find(Tree *root){
	int n, rc = 0;
	char *key = (char *)calloc(15, sizeof(char));
	printf("Enter key: -->\n");
	n = scanf("%s", key);
        if (n == EOF) return 0;
	rc = T_Find(root, key);
	if (rc == 3) return 0;
	printf("%s\n", errmsgs[rc]);
	return 1;
}

Tree *D_Delete(Tree *root){
        int n, rc = 0, flag = 1;
        char *key = (char *)calloc(15, sizeof(char));
        printf("Enter key: -->\n");
        n = scanf("%s", key);
        if (n == EOF) return NULL;
	rc = T_Delete(root, key, flag);
	printf("%s\n", errmsgs[rc]);
        return root;
}

int D_Same(Tree *root){
	int n, rc = 0;
	char *key = (char *)calloc(15, sizeof(char));
	printf("Enter key: -->\n");
	n = scanf("%s", key);
	if (n == EOF) return 0;
	rc = T_Same(root, key);
	printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Show_key(Tree *root){
        int n, rc = 0;
        char *key = (char *)calloc(15, sizeof(char));
        printf("Enter start of key: -->\n");
        n = scanf("%s", key);
        if (n == EOF) return 0;
	rc = T_Show_key(root, key);
        printf("%s\n", errmsgs[rc]);
	return 1;
}

int D_Show(Tree *root){
	Tree *ptr = root;
	Info *info;
	while(ptr->next != NULL)
		ptr = ptr->next; // находим самый маленький ключ
	while(ptr != NULL){ // идем по возрастанию
		for (int i = 0; i < ptr->lvl; i++) printf("   ");
		printf("   /\n");
		for (int j = 0; j < ptr->lvl; j++) printf("    "); // высота
		printf("%s :  ", ptr->key);
		info = ptr->info;
		while(info != NULL){// проход по всему списку info
			printf("(balance = %d) %f %s; ", ptr->balance, info->num, info->string);
			info = info->next;
		}
		printf("\n");
		for (int c = 0; c < ptr->lvl; c++) printf("   ");
                printf("   \\\n");
		ptr = ptr->prev;
	}
        return 1;
}

int D_File(Tree *root){
        int n, k;
        printf("Enter number or items: -->\n 1<=x<=10\n");
        n = scanf("%d", &k);
        if (n == EOF) return 0;
        T_File(root, k);
	return 1;
}

int D_Timing(Tree *root){
        int n, k;
        printf("Enter number or keys: -->\n");
        n = scanf("%d", &k);
        if (n == EOF) return 0;
	T_Timing(root, k);
	return 1;
}
