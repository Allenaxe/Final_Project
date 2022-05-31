#include "object.h"

typedef struct TYPE {
	char name[10];
	int BorderLeft, BorderRight, BorderUp, BorderDown;
}type;

typedef struct Node {
	struct Node* next;
	type data;
}Node;

Node *head = NULL;

void object_construct(char *src, int B_X_UL, int B_X_UR, int B_Y_DL, int B_Y_UL) {
	if (head == NULL) {
		head = (Node*)malloc(sizeof(Node));
		if (head) {
			strcpy_s(head->data.name, sizeof(head->data.name) / sizeof(char), src);
			head->data.BorderLeft = B_X_UL, head->data.BorderRight = B_X_UR, head->data.BorderUp = B_Y_UL, head->data.BorderDown = B_Y_DL;
			head->next = NULL;
			//printf("%s %d Object Add Success", head->data.name, head->data.BorderLeft);
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
		//printf("Object Add Success");
	}
	return;
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
			if (A_X_UR == current->data.BorderLeft) {
				printf("1");
				return 1;
			}
			else if (A_X_UL == current->data.BorderRight) {
				printf("2");
				return 2;
			}
			else if (A_Y_DL == current->data.BorderUp) {
				printf("3");
				return 3;
			}
			else if (A_Y_UL == current->data.BorderDown) {
				printf("4");
				if (!strcmp(current->data.name, "statue1")) statue_trigger();
				return 4;
			}
		}
		current = current->next;
	}
	return 0;
}