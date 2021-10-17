/*=======================================================================================================*/
/*                                           ��ϴ� �˰��� ����										 */
/* �й� : 2018038014                                                                                     */
/* �̸� : ������																						 */
/* ���: txt ���Ͽ��� ������ ���� �о ����Ʈ���� �����. �� ���� ã���� �ϴ� ���� ���� ���ο� ��ġ��  */
/*		����ڿ��� �˷��ش�.																		     */
/*=======================================================================================================*/

#define _CRT_SECURE_NO_WARNINGS				// fsopen, scanf ��ó��
#include <stdio.h>
#include <stdlib.h>



typedef struct element {					// ����ü ������ Ÿ�� ���� 
	int key;				
} element;

typedef struct Node* treePointer;			// ����ü ��� ������ ����

typedef struct Node {						// ����ü ������ ���� 
	element data;
	treePointer leftchild, rightchild;		// ������, ���� �ڽĳ�� 
}node;
treePointer root;							// ��Ʈ ��� ����
void insert(treePointer*, int);				// ������ �а� ���� �ϴ� �Լ�
treePointer modifiedSearch(treePointer p, int x); // 
element* search(treePointer tree, int key);		// ����Ʈ�� Ž�� �Լ�  
int OpenFile();									// ������ �о ��带 �����ϴ� �Լ�
void inorder(treePointer tree);				//����Ž��
void postorder(treePointer tree);			//����Ž��
void preorder(treePointer tree);			//����Ž��
int main()
{
	element* status;
	int findkey;
	OpenFile();
	printf("\n========================================================================================================================================================================\n");
	printf("Preorder : ");
	preorder(root);
	printf("\n========================================================================================================================================================================\n");
	printf("Inorder : ");
	inorder(root);
	printf("\n========================================================================================================================================================================\n");
	printf("Postorder : ");
	postorder(root);
	printf("\n========================================================================================================================================================================\n");
	printf("ã���� �ϴ� key���� �Է��ϼ���.  : ");
	scanf("%d", &findkey);

	status = search(root, findkey);
	if (status == NULL)				// search Ž���� ���� ã�� ��尡 ������ NULL�� �ǹǷ� NULL�̸� ���� ����.
	{
		printf("\n����� ã���� �ϴ� ���� �����ϴ�.\n");
	}
	else {														// NULL�� �ƴϸ� ã���� �ϴ� ���� �ֱ� ������ 
		printf("����� ã���� �ϴ� ���� %d �̰� �޸� �ּһ� ��ġ�� %d �� ��ġ�ϰ� �ֽ��ϴ�. ", status->key, &status);		// 
	}
		
	printf("\n");
	return 0;
}
int OpenFile()
{
	FILE* pFile = fopen("test.txt", "r");		//read mode
	int intTemp = -1;

	if (pFile == NULL) {						// ������ �������� ������ ��� ���� ���
		printf("File does not exist");
		return 0;
	}
	// �����б� ����
	while (true)
	{
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0)						// ������ ���� -1�̹Ƿ� -1���� ������ �ݺ��� ����
			break;
		insert(&root, intTemp);					// ������ �о���� ��忡 ����
	}

}
/*��� �����Լ� */
void insert(treePointer* node, int key)	
{
	treePointer ptr, temp = modifiedSearch(*node, key);	// ptr, temp ��带 �����ϰ� �ΰ��� ��尡 ���� �������� Ȯ��
	if (temp || !(*node)) {

		ptr = (treePointer)malloc(sizeof(*ptr));		// ptr ��� �ʱ�ȭ
		ptr->data.key = key;							// �ʵ��� key���� �о�� �����ͷ� �ʱ�ȭ
		ptr->leftchild = NULL; ptr->rightchild = NULL;	// ������ �ʱ�ȭ

		if (*node) {						 // ��尡 �����ϸ� 
			if (key < temp->data.key) {		 // ã���� �ϴ� key���� �θ� ũ��
				temp->leftchild = ptr;		 // ���� �ڽĳ��� �̵�
			}
			else {							 //ptr ū ���̸� ������ �ڽ�����
				temp->rightchild = ptr;
			}
		}
		else *node = ptr;					// ��尡 ���� ���� ������ ptr�� �θ� ��� 				
	}
}
treePointer modifiedSearch(treePointer root, int k) //������ �������� Ž���Ͽ� ���ɿ��θ� ��ȯ
{
	treePointer temp = root;
	while (root)								// ��Ʈ�� ���� �ϸ� �ݺ��� ���� 
	{
		temp = root;							// temp�� ��Ʈ�� �ӽ÷� ����
		if (k < root->data.key)					// ���԰��� ������
			root = root->leftchild;				// �������� ���� �ٽ� �˻�
		else if (k > root->data.key)			// ���԰��� ũ��
			root = root->rightchild;			// ���������� ���� �ٽ� �˻�
		else                                    // ���� ã���� �ϴ� ���� ������ null�� ��ȯ
			return NULL;							
	}
	return temp;									// parent ��ġ ��ȯ
}

/*���� ��ȸ*/
void inorder(treePointer tree)
{
	if (tree)
	{
		inorder(tree->leftchild);
		printf("%d ", tree->data.key);
		inorder(tree->rightchild);
	}
}

/*���� ��ȸ*/
void preorder(treePointer tree)
{
	if (tree) {
		printf("%d ", tree->data.key);
		preorder(tree->leftchild);
		preorder(tree->rightchild);
	}
}

/*���� ��ȸ*/
void postorder(treePointer tree)
{
	if (tree) {
		postorder(tree->leftchild);
		postorder(tree->rightchild);
		printf("%d ", tree->data.key);
	}
}

/*Ž�� �Լ� */
element* search(treePointer tree, int key)
{
	if (!tree) return NULL;												// key ���� ������ NULL�� ��ȯ
	if (key == tree->data.key)return &(tree->data);						// key ���� ������ ����Ÿ ������ ��ȯ
	if (key < tree->data.key)											// ã���� �ϴ� Ű���� ��庸�� ������
	{
		return search(tree->leftchild, key);							// root���� ã�� ���� ������ ���� �ڽ����� �̵�
	}
	else                                                                // key�� ���� ũ�� 
	{
		return search(tree->rightchild, key);							// ���������� �̵�
	}
		
}