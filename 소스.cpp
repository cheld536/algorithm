#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef int Number;							// 구조체 데이터 형식


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


	// 파일 읽기 성공
	while (true) {
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0) break;
		// 트리생성

		// 생성된 트리에서 키 검색

		printf("%d ", intTemp);
	}

	//파일 형태로 반환

	fclose(pFile);          //close file
	return 0;
}