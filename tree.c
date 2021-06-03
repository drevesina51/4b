#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int init_tree(Tree *root){
	root->info = NULL;
	root->key = NULL;
	root->prev = NULL;
	root->next = NULL;
	root->left = NULL;
	root->right = NULL;
	root->parent = NULL;
	root->lvl = 0;// высота
	root->balance = 0;// перевес
	return 1;
}

int delTree(Tree *root){
	if (root->info == NULL){
		free(root);
		return 1;
	}
	Tree *ptr = root;
	Tree *tmp = NULL;
	Info *inf = NULL;
	while(ptr->next != NULL)
                ptr = ptr->next;
        while(ptr != NULL){
		tmp = ptr;
		ptr = ptr->prev;
		inf = tmp->info;
		while (tmp->info){
			inf = tmp->info;
			tmp->info = tmp->info->next;
			free(inf->string);
			free(inf);
		}
		free(tmp->key);
		free(tmp);
	}
	return 1;
}

int find(Tree *root, char *key, float num, char *string, int flag_t){// создание элемента, поиск, добавление
	if (root->info == NULL)
		return 0;//новое дерево
	Tree *ptr = root;
	while(ptr){
                if (strcmp(ptr->key, key) > 0)
			ptr = ptr->right;
		else if (strcmp(ptr->key, key) < 0)
		     	ptr = ptr->left;
		     else if (strcmp(ptr->key, key) == 0){
				if (flag_t != 1) free(key);
        			Info *info = (Info *)calloc(1, sizeof(Info));
        			if(info == NULL){
                			return 3;
        			}
		      	  	Info *last = NULL;
				last = ptr->info;
				while(last->next != NULL)
					last = last->next;
				info->num = num;
				info->string = string;
				info->next = NULL;
				last->next = info;
				return 1; // повторяющися ключ добавлен
			}
	}
	return 0;//нет такого ключа
}

int lvldown(Tree *ptr){
        if (ptr){
                lvldown(ptr->left);
                lvldown(ptr->right);
                ptr->lvl--;
        }
        return 1;
}

int lvlup(Tree *ptr){
        if (ptr){
                lvlup(ptr->left);
                lvlup(ptr->right);
                ptr->lvl++;
        }
        return 1;
}

int left_rotate(Tree *ptr){
	Tree *parent = NULL;
	Tree *a = NULL;
        Tree *b = NULL;
	parent = ptr->parent;
	a = ptr->right;
	if (a == NULL) {
		return 1;
	}
	b = a->left;
	lvldown(a);
	a->left = ptr;
	ptr->right = b;
	if (b != NULL){
		b->parent = ptr;
	}
	a->parent = parent;
	if (parent != NULL){
		if (parent->left == ptr) {
			parent->left = a;
		} else {
			parent->right = a;
			}
	}
	ptr->parent = a;
	lvlup(ptr);
	return 1;
}

int right_rotate(Tree *ptr){
        Tree *parent = NULL;
        Tree *a = NULL;
        Tree *b = NULL;
        parent = ptr->parent;
        a = ptr->left;
        if (a == NULL) {
                return 1;
        }
        b = a->right;
	lvldown(a);
        a->right = ptr;
        ptr->left = b;
        if (b != NULL){
                b->parent = ptr;
        }
        a->parent = parent;
        if (parent != NULL){
                if (parent->left == ptr) {
                        parent->left = a;
                } else {
                        parent->right = a;
                        }
        }
        ptr->parent = a;
	lvlup(ptr);
        return 1;
}

int big_right_rotate(Tree *ptr){
	left_rotate(ptr->left);
	right_rotate(ptr);
	return 1;
}

int big_left_rotate(Tree *ptr){
        right_rotate(ptr->right);
        left_rotate(ptr);
        return 1;
}

int r_correct(Tree *x){
	if (x->right->balance == 1){
                x->balance = 0;
                x->right->balance = 0;
                left_rotate(x);
		return 1;
        }
	if (x->right->balance == 0){
                x->balance = 1;
                x->right->balance = -1;
                left_rotate(x);
		return 1;
        }
	if (x->right->left->balance == -1){
                x->balance = 0;
                x->right->balance = 1;
		x->right->left->balance = 0;
                big_left_rotate(x);
		return 1;
        }
	if (x->right->left->balance == 1){
                x->balance = -1;
		x->right->left->balance = 0;
                x->right->balance = 0;
                big_left_rotate(x);
		return 1;
        }
	if (x->right->left->balance == 0){
                x->balance = 0;
		x->right->left->balance = 0;
                x->right->balance = 0;
                big_left_rotate(x);
		return 1;
        }
	return 1;
}

int l_correct(Tree *x){
        if (x->left->balance == -1){
                x->balance = 0;
                x->left->balance = 0;
                right_rotate(x);
                return 1;
        }
        if (x->left->balance == 0){
                x->balance = -1;
                x->left->balance = 1;
                right_rotate(x);
                return 1;
        }
        if (x->left->right->balance == 1){
                x->balance = 0;
                x->left->balance = -1;
                x->left->right->balance = 0;
                big_right_rotate(x);
                return 1;
        }
        if (x->left->right->balance == -1){
                x->balance = 1;
                x->left->right->balance = 0;
                x->left->balance = 0;
                big_right_rotate(x);
                return 1;
        }
        if (x->left->right->balance == 0){
                x->balance = 0;
                x->left->right->balance = 0;
                x->left->balance = 0;
                big_right_rotate(x);
                return 1;
        }
        return 1;
}
Tree *correct(Tree *root, Tree *x){
	Tree *p;
	do {
		p = x->parent;
		if (x == p->left) p->balance --;
		else p->balance ++;
		x = p;
		if (x->balance == 2) r_correct(x);
		if (x->balance == -2) l_correct(x);
	} while(x != root && x->balance != 0);
	while (root->parent != NULL) root = root->parent;
	return root;
}

Tree *correct_d(Tree *root, Tree *x, int d){
	Tree *p;
	if (d == -1) x->balance ++;
	else x->balance --;
        do {
                if (x->balance == 2) r_correct(x);
                if (x->balance == -2) l_correct(x);
		p = x->parent;
                if (x == p->left) p->balance ++;
                else p->balance --;
                x = p;
        } while(x != root && x->balance != 0);
        while (root->parent != NULL) root = root->parent;
        return root;
}

Tree *newlist(char *key, float num, char *string){
        Info *info = (Info *)calloc(1, sizeof(Info));
        if(info == NULL){
                return NULL;
	}
        Tree *newl = (Tree *)calloc(1, sizeof(Tree));
        if(newl == NULL){
                return NULL;
        }
        info->num = num;
        info->string = string;
        info->next = NULL;
        newl->key = key;
        newl->info = info;
        newl->next = NULL;
        newl->prev = NULL;
        newl->left = NULL;
        newl->right = NULL;
	newl->parent = NULL;
        newl->lvl = 0;
	newl->balance = 0;
        return newl;
}

Tree *insert(Tree *root, char *key, float num, char *string, int flag_t){
        if(find(root, key, num, string, flag_t) == 1)// поиск такого же ключа
                return root;
        else   {
		        Tree *newl = newlist(key, num, string);
			if (newl == NULL) return NULL;
                        Info *info = newl->info;
			if (root->info == NULL) { // заполнение корня
				root->info = info;
				root->key = key;
				free(newl);
				return root;
        		} else {
				int flag = 0;//при изменении направления
                		Tree *ptr = root;
				Tree *par = NULL;
				Tree *tmp = NULL;
				while(ptr){
					newl->lvl++;
					if (strcmp(ptr->key, key) > 0){ // идем в правое поддерево
						if (flag == 0)
							flag = 1;
						else if (flag == -1){// tmp = первое до смены направления
							tmp = ptr->parent;
							flag = 1;
						     }
						if(ptr->right != NULL){
							par = ptr;
							ptr = ptr->right;
							ptr->parent = par;
						} else {
							newl->prev = ptr;
							newl->next = tmp;
							ptr->right = newl;
							ptr->next = newl;
							newl->parent = ptr;
							if (tmp != NULL)
								tmp->prev = newl;
							root = correct(root, newl);
							return root;
							}
					} else { // идем в левое поддерево
						if (flag == 0)
							flag = -1;
						else if (flag == 1){
							flag = -1;
							tmp = ptr->parent;
						     }
						if(ptr->left != NULL){
							par = ptr;
							ptr = ptr->left;
							ptr->parent = par;
						} else {
							newl->next = ptr;
							newl->prev = tmp;
							ptr->left = newl;
							ptr->prev = newl;
							newl->parent = ptr;
							if (tmp != NULL)
								tmp->next = newl;
							root = correct(root, newl);
							return root;
						}
					}
				}
		       }
		}
		return root;
}

int print_find(char *key, Info *info){
        printf("key %s : %f %s \n", key, info->num, info->string);
        return 1;
}

int T_Show_key(Tree *root, char *key){
        Tree *ptr = root;
	while(ptr->prev != NULL)
		ptr = ptr->prev;
	while(ptr != NULL){
                if (strstr(ptr->key, key) == &ptr->key[0]){
			while (strstr(ptr->key, key) == &ptr->key[0]){
				print_find(ptr->key, ptr->info);
				ptr = ptr->next;
		     	}
			return 0;
		}
		ptr = ptr->next;
	}
	return 6;
}

int choose(int n){
        int w;
	int r;
        printf("There are %d info's with this key\nEnter number of info: 1<=x<=%d -->\n", n, n);
        w = scanf("%d", &r);
        if (w == EOF) return 0;
        if (r > n) r = n;
        return r;
}

int T_Find(Tree *root, char *key){
	Tree *ptr = root;
	Info *info = NULL;
	int n, r;
        while(ptr){
        	if (strcmp(ptr->key, key) > 0)
                        ptr = ptr->right;
                else if (strcmp(ptr->key, key) < 0)
                        ptr = ptr->left;
                else if (strcmp(ptr->key, key) == 0){
			if(ptr->info->next != NULL){
				n = 0;
				info = ptr->info;
				while(info != NULL){
					n++;
					info = info->next;
				}
				info = ptr->info;
				if (n > 0){
					r = choose(n);
                                        if (r == 0) return 3;
					for (int i = 0; i<r-1; i++){
						info = info->next;
					}
				}
			} else info = ptr->info;
			print_find(key, info);
			free(key);
			return 0;
		}
	}
	free(key);
        return 5;
}

int T_Delete(Tree *root, char *key, int flag){//удаление корня
        int n, r, d = 0;
        Tree *ptr = root;
        Tree *parent = NULL;
        Info *info = NULL;
        Info *par = NULL;
        while(ptr){
                if (strcmp(ptr->key, key) > 0){
                        parent = ptr;
                        ptr = ptr->right;
                        d = 1;
                }
                else if (strcmp(ptr->key, key) < 0){
                        parent = ptr;
                        ptr = ptr->left;
                        d = -1;
                }
                else if (strcmp(ptr->key, key) == 0){
                        if(ptr->info->next != NULL && flag == 1){
                                n = 0;
                                info = ptr->info;
                                while(info != NULL){
                                        n++;
                                        info = info->next;
                                }
                                info = ptr->info;
                                if (n > 1){
                                        r = choose(n);
                                        if (r == 0) return 3;
                                        if (r == 1){
                                                //info = ptr->info;
                                                ptr->info = info->next;
                                                free(info->string);
                                                free(info);
                                                return 0;
                                        }
                                        for (int i = 0; i < r-1; i++){
                                                par = info;
                                                info = info->next;
                                        }
                                        par->next = info->next;
                                        free(info->string);
                                        free(info);
                                        return 0;
                                }
                        }else {
                                Tree *qwe = NULL;
                                Tree *asd = NULL;
                                if(ptr->left == NULL && ptr->right == NULL){//нет ветвей
                                        if (d == -1) parent->left = NULL;
                                        else parent->right = NULL;
                                }else if (ptr->right == NULL){//одна левая ветвь
                                           if (d == -1) parent->left = ptr->left;
                                           else parent->right = ptr->left;
                                           lvldown(ptr);
                                      }else if (ptr->left == NULL){//одна правая ветвь
                                                if (d == -1) parent->left = ptr->right;
                                                else parent->right = ptr->right;
                                                lvldown(ptr);
                                        }else{//2 ветви
                                                char *key_asd;
                                                Info *info_asd;
                                                char *string_asd;
                                                if (d == -1) asd = ptr->prev;
                                                else asd = ptr->next;
                                                flag = 0;
                                                key_asd = asd->key;
                                                info_asd = asd->info;
                                                string_asd = asd->info->string;
                                                info_asd->string = string_asd;
                                                T_Delete(root, key_asd, flag);
                                                free(ptr->info->string);
                                                free(ptr->info);
                                                free(ptr->key);
                                                ptr->key = key_asd;
                                                ptr->info = info_asd;
                                              return 0;
                                             }
                                qwe = ptr->prev;
                                asd = ptr->next;
				Tree *cor = ptr->parent;
                                if (qwe != NULL) qwe->next = asd;
                                if (asd != NULL) asd->prev = qwe;
                                if (flag == 1){
                                        free(ptr->info->string);
                                        free(ptr->info);
                                        free(ptr->key);
					root = correct_d(root, cor, d);
                                }
                                free(ptr);
                                return 0;
                              }
                }
        }
        return 5;
}

int T_Same(Tree *root, char *key){
	Tree *ptr = root;
	while(ptr){
        	if (strcmp(ptr->key, key) > 0)
                        ptr = ptr->right;
                else if (strcmp(ptr->key, key) < 0)
                        ptr = ptr->left;
                else if (strcmp(ptr->key, key) == 0){
			if (strcmp(ptr->prev->key, key) > strcmp(ptr->next->key, key))
				print_find(ptr->next->key, ptr->next->info);
			else print_find(ptr->prev->key, ptr->prev->info);
			return 0;
		    }
	}
	free(key);
	return 5;
}

int T_File(Tree *root, int m){
        FILE *in;
        in = fopen("filelab4b.txt", "r");
        if(in == NULL){
                printf("Файл не найден\n");
                return 0;
        }
        int flag = 1;
	float num;
        char **key = NULL;
        char **string = NULL;
        key = (char **)calloc(m, sizeof(char *));
        string = (char **)calloc(m, sizeof(char *));
        for (int q = 0; q < m; q++){
                key[q] = (char *)calloc(15, sizeof(char));
                if(key[q] == NULL) {
                        printf("Error try alloc\n");
                        return 0;
                }
                string[q] = (char *)calloc(15, sizeof(char));
                if(string[q] == NULL) {
                        printf("Error try alloc\n");
                        return 0;
                }
        }
        for (int i = 0; i < m; i++) {
                fscanf(in, "%s", key[i]);
                fscanf(in, "%f", &num);
                fscanf(in, "%s", string[i]);
                insert(root, key[i], num, string[i], flag);
        }
        fclose(in);
	return 1;
}

int find_time(Tree *root, char* key){
        Tree *ptr = root;
        while(ptr){
                if (strcmp(ptr->key, key) > 0)
                        ptr = ptr->right;
                else if (strcmp(ptr->key, key) < 0)
                        ptr = ptr->left;
                else if (strcmp(ptr->key, key) == 0) return 1;
	}
	return 0;
}


int T_Timing(Tree *root, int cnt){
        int first, last;
        srand(time(NULL));
	char **key = NULL;
        char **string = NULL;
	key = (char **)calloc(cnt, sizeof(char *));
	string = (char **)calloc(cnt, sizeof(char *));
	for (int q = 0; q < cnt; q++){
		key[q] = (char *)calloc(15, sizeof(char));
		if(key[q] == NULL) {
                        printf("Error try alloc\n");
                        return 0;
                }
		string[q] = (char *)calloc(15, sizeof(char));
                if(string[q] == NULL) {
                        printf("Error try alloc\n");
                        return 0;
                }

	}
	int num, i, m = 0, flag = 1;
	char *x;
	int z, j;
	for (i = 0; i < cnt; i++){
		num = rand() % 100;
		z = rand()%15;
                x = key[i];
                for (j = 0; j < z; j++)
                        x[j] = rand()%26+'A';
		x = string[i];
		z = rand()%5;
		for (j = 0; j < z; j++)
                        x[j] = rand()%26+'A';
		root = insert(root, key[i], num, string[i], flag);
	}
	first = clock();
	for (i = 0; i < cnt; i++)
		if (find_time(root, key[i]))
			++m;
	last = clock();
	printf("number of nodes = %d, time = %d\n", m, last - first);
	return 1;
}

