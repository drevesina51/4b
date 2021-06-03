#ifndef TREE_H
#define TREE_H
#include <time.h>
#define KeyType char

typedef struct Info{
    double num; //первое число
    char *string; //строка
    struct Info *next; // следущий элемент с таким же ключем
} Info;

typedef struct Tree{
    Info *info; // информационное поле
    KeyType *key; // ключ
    int lvl;
    int balance; // перевес
    struct Tree *parent;
    struct Tree *left; // левое поддерево
    struct Tree *right; // правое поддерево
    struct Tree *next;
    struct Tree *prev;
} Tree;

int T_Find(Tree *, char *), //поиск элемента в дереве по ключу
    T_Delete(Tree *, char *, int), //удаление по ключу
    T_Same(Tree *, char *), //поиск максимально отличающегося
    T_Timing(Tree *, int), // таймирование
    T_File(Tree *, int), // ввод из файла
    T_Show_key(Tree *, char *);
int init_tree(Tree *), // создание нового корня
    delTree(Tree *), // удаление дерева
    lvldown(Tree *),
    lvlup(Tree *),
    find_time(Tree *, char *),
    right_rotate(Tree *),
    left_rotate(Tree *),
    find(Tree *, char *, float, char *, int);
Tree *insert(Tree *root, char *, float, char *, int);
Tree *correct(Tree *, Tree *);
#endif // TREE_H
