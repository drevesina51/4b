#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "tree.h"
#include "task.h"

int dialog(const char *msgs[], int N) {
        char *errmsg = "";
        int rc;
        int i, n;
        do{
                puts(errmsg);
                errmsg = "\nYou are wrong. Repeate, please!";
                for(i = 0; i < N; ++i)
                        puts(msgs[i]);
                puts("Make your choice: --> ");
                n = scanf("%d", &rc);
		if (n == EOF) return 0;
                if(n == 0)
                        rc = 0;
        } while(rc < 0 || rc >= N);
        return rc;
}

int main(){
        Tree *root = (Tree *) calloc(1, sizeof(Tree)); // создание пустой таблицы
        if(root == NULL) {
                   printf("Error try alloc\n");
                   return 0;
        }
        init_tree(root);
        const char *msgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show", "5. Same", "6. Timing", "7. File", "8. Show_key"};
        const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
        int dialog(const char *msgs[], int);
        int (*fptr[])(Tree *) = {NULL, NULL, D_Find, NULL, D_Show, D_Same, D_Timing, D_File, D_Show_key};
        int rc;
        while(rc = dialog(msgs, NMsgs)){
		if (rc == 1){
			root = D_Add(root);
			if (root == NULL)
				break;
		}else if (rc == 3){
                        root = D_Delete(root);
                        if (root == NULL)
                                break;
		}else if(!fptr[rc](root))
                     		break;
	}
        printf("End.\n");
        delTree(root); //удаление таблицы
	return 0;
}
