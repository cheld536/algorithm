#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Number;							// ����ü ������ ����


typedef struct TreeNode {
	Number num;
	struct TreeNode* left;					//  
	struct TreeNode* right;
}TreeNode;

TreeNode* root = NULL;

TreeNode* new_node(Number num) {
	TreeNode* n = (TreeNode*)malloc(sizeof(TreeNode));
	n->num = num;
	n->left = NULL;
	n->right = NULL;
	return n;
}

void insert(TreeNode* node, int k);









int main(void)
{
	FILE* pFile = fopen("test.txt", "r"); //read mode 
	int intTemp = -1;

	if (pFile == NULL)
	{
		printf("File does not exist");
		return 0;
	}


	// ���� �б� ����
	while (true) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		// Ʈ������

		// ������ Ʈ������ Ű �˻�

		printf("%d ", intTemp);
	}

	//���� ���·� ��ȯ

	fclose(pFile);          //close file
	return 0;
}