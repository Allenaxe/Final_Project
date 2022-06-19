#include "object.h"

typedef struct TYPE {
	char name[10];
	int BorderLeft, BorderRight, BorderUp, BorderDown;
}type;

typedef struct Node {
	struct Node* next;
	type data,shop;//000000
}Node;

Node *head = NULL;

void object_construct(char *src, int B_X_UL, int B_X_UR, int B_Y_DL, int B_Y_UL) {
	if (head == NULL) {
		head = (Node*)malloc(sizeof(Node));
		if (head) {
			strcpy_s(head->data.name, sizeof(head->data.name) / sizeof(char), src);
			head->data.BorderLeft = B_X_UL, head->data.BorderRight = B_X_UR, head->data.BorderUp = B_Y_UL, head->data.BorderDown = B_Y_DL;
			head->next = NULL;
			printf("%s Object Add Success\n", head->data.name);
		}
		return;
	}
	Node* current = head;
	while (current->next != NULL) current = current->next;
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (new_node) {
		strcpy_s(new_node->data.name, sizeof(new_node->data.name) / sizeof(char), src);
		new_node->data.BorderLeft = B_X_UL, new_node->data.BorderRight = B_X_UR, new_node->data.BorderUp = B_Y_UL, new_node->data.BorderDown = B_Y_DL;
		new_node->next = NULL;
		current->next = new_node;
		printf("%s Object Add Success\n", new_node->data.name);
	}
	return;
}
//000000
/*Node *item_supplement[10],*item_defence[10];
int blood_control2(){
    for(int i=0;i<10;i++){
    if(collision_judge(item_supplement[i]->data.name,item_supplement[i]->data.BorderLeft, item_supplement[i]->data.BorderRight, item_supplement[i]->data.BorderUp,item_supplement[i]->data.BorderDown)!=0){
    chara.blood=chara.blood+1;//adjust
   }

   if(collision_judge(item_defence[i]->data.name,item_defence[i]->data.BorderLeft, item_defence[i]->data.BorderRight, item_defence[i]->data.BorderUp,item_defence[i]->data.BorderDown)!=0){
    chara.defence=chara.defence+1;//adjust
   }
    }
}*/

void object_delete(char *src) {
	Node *current = head;
	while (current->next != NULL) {
		if (!strcmp(current->next->data.name, src)) {
			Node *tmp = current->next;
			current->next = current->next->next;
			free(tmp);
			break;
		}
		current = current->next;
	}
}

void object_free() {
	if (head == NULL) return;
	Node* current = head;
	while (current != NULL) {
		Node* tmp = current;
		current = current->next;
		free(tmp);
	}
}

void map_free() {
    if (head == NULL) return;
	Node* current = head;
	while (current != NULL) {
        if(!strcmp(current->data.name, "character\0")) {
            head = current;
            current = current->next;
        }
        else {
            Node* tmp = current;
            current = current->next;
            free(tmp);
        }
	}
	head->next = NULL;
}
//0000
void collision_update(char* src, int A_X_UL, int A_X_UR, int A_Y_DL, int A_Y_UL) {
	Node* current = head;
	while (current != NULL) {
		if (!strcmp(current->data.name, src)) {
			current->data.BorderLeft = A_X_UL, current->data.BorderRight = A_X_UR, current->data.BorderUp = A_Y_UL, current->data.BorderDown = A_Y_DL;
			break;
		}
		current = current->next;
	}
}

int collision_judge(char *src, int A_X_UL, int A_X_UR, int A_Y_DL, int A_Y_UL) {
	Node* current = head;
	while(current != NULL) {
		if (strcmp(src, current->data.name) && (A_X_UR >= current->data.BorderLeft && current->data.BorderRight >= A_X_UL && current->data.BorderUp <= A_Y_DL && A_Y_UL <= current->data.BorderDown)) {
			if (!strcmp(src, "character")) {
                int check = monster_delete(current->data.name);
				if (check == 1) {
					object_delete(current->data.name);
					break;
				}
				else if(check == 0 && strcmp(current->data.name, "statue1") && strcmp(current->data.name, "shop")) {
                    chara_lose_blood = 1;
				}
			}
			if (A_X_UR == current->data.BorderLeft) {
				return 1;
			}
			else if (A_X_UL == current->data.BorderRight) {
				return 2;
			}
			else if (A_Y_DL == current->data.BorderUp) {
				return 3;
			}
			else if (A_Y_UL == current->data.BorderDown) {
				if (!strcmp(current->data.name, "statue1") && !strcmp(src, "character")) statue_trigger();
				return 4;
			}
		}
		current = current->next;
	}
	return 0;
}
