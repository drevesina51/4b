#ifndef TASK_H
#define TASK_H
#include "tree.h"

Tree *D_Add(Tree *); //вставка элемента в дерево
Tree *D_Delete(Tree *); //удаление по ключу
int D_Find(Tree *), //поиск элемента в дереве по ключу
    D_Show(Tree *), //вывод дерева на экран
    D_Same(Tree *), //поиск максимально отличающегося
    D_Timing(Tree *), // таймирование
    D_File(Tree *), // ввод из вайла
    D_Show_key(Tree *); // вывод по началу ключа
#endif // TASK_H
