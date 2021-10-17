/*=======================================================================================================*/
/*                                           충북대 알고리즘 과제										 */
/* 학번 : 2018038014                                                                                     */
/* 이름 : 김윤희																						 */
/* 기능: txt 파일에서 데이터 값을 읽어서 이진트리로 만든다. 그 다음 찾고자 하는 값의 존재 여부와 위치를  */
/*		사용자에게 알려준다.																		     */
/*=======================================================================================================*/

#define _CRT_SECURE_NO_WARNINGS				// fsopen, scanf 전처리
#include <stdio.h>
#include <stdlib.h>



typedef struct element {					// 구조체 데이터 타입 정의 
	int key;				
} element;

typedef struct Node* treePointer;			// 구조체 노드 포인터 정의

typedef struct Node {						// 구조체 데이터 구현 
	element data;
	treePointer leftchild, rightchild;		// 오른쪽, 왼쪽 자식노드 
}node;
treePointer root;							// 루트 노드 선언
void insert(treePointer*, int);				// 파일을 읽고 삽입 하는 함수
treePointer modifiedSearch(treePointer p, int x); // 
element* search(treePointer tree, int key);		// 이진트리 탐색 함수  
int OpenFile();									// 파일을 읽어서 노드를 삽입하는 함수
void inorder(treePointer tree);				//중위탐색
void postorder(treePointer tree);			//후위탐색
void preorder(treePointer tree);			//전위탐색
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
	printf("찾고자 하는 key값을 입력하세요.  : ");
	scanf("%d", &findkey);

	status = search(root, findkey);
	if (status == NULL)				// search 탐색을 통해 찾는 노드가 없으면 NULL이 되므로 NULL이면 값이 없다.
	{
		printf("\n당신이 찾고자 하는 값이 없습니다.\n");
	}
	else {														// NULL이 아니면 찾고자 하는 값이 있기 때문에 
		printf("당신이 찾고자 하는 값은 %d 이고 메모리 주소상 위치는 %d 에 위치하고 있습니다. ", status->key, &status);		// 
	}
		
	printf("\n");
	return 0;
}
int OpenFile()
{
	FILE* pFile = fopen("test.txt", "r");		//read mode
	int intTemp = -1;

	if (pFile == NULL) {						// 파일이 존재하지 않으면 경고 문구 출력
		printf("File does not exist");
		return 0;
	}
	// 파일읽기 성공
	while (true)
	{
		fscanf(pFile, "%d", &intTemp);
		if (intTemp < 0)						// 파일의 끝은 -1이므로 -1보다 작으면 반복을 종료
			break;
		insert(&root, intTemp);					// 파일을 읽어오면 노드에 삽입
	}

}
/*노드 삽입함수 */
void insert(treePointer* node, int key)	
{
	treePointer ptr, temp = modifiedSearch(*node, key);	// ptr, temp 노드를 생성하고 두개의 노드가 생성 가능한지 확인
	if (temp || !(*node)) {

		ptr = (treePointer)malloc(sizeof(*ptr));		// ptr 노드 초기화
		ptr->data.key = key;							// 필드의 key값을 읽어온 데이터로 초기화
		ptr->leftchild = NULL; ptr->rightchild = NULL;	// 포인터 초기화

		if (*node) {						 // 노드가 존재하면 
			if (key < temp->data.key) {		 // 찾고자 하는 key보다 부모가 크면
				temp->leftchild = ptr;		 // 왼쪽 자식노드로 이동
			}
			else {							 //ptr 큰 값이면 오른쪽 자식으로
				temp->rightchild = ptr;
			}
		}
		else *node = ptr;					// 노드가 존재 하지 않으면 ptr이 부모 노드 				
	}
}
treePointer modifiedSearch(treePointer root, int k) //삽입이 가능한지 탐색하여 가능여부를 반환
{
	treePointer temp = root;
	while (root)								// 루트가 존재 하면 반복문 시작 
	{
		temp = root;							// temp에 루트를 임시로 저장
		if (k < root->data.key)					// 삽입값이 작으면
			root = root->leftchild;				// 왼쪽으로 가서 다시 검색
		else if (k > root->data.key)			// 삽입값이 크면
			root = root->rightchild;			// 오른쪽으로 가서 다시 검색
		else                                    // 만약 찾고자 하는 값이 없으면 null을 반환
			return NULL;							
	}
	return temp;									// parent 위치 반환
}

/*중위 순회*/
void inorder(treePointer tree)
{
	if (tree)
	{
		inorder(tree->leftchild);
		printf("%d ", tree->data.key);
		inorder(tree->rightchild);
	}
}

/*전위 순회*/
void preorder(treePointer tree)
{
	if (tree) {
		printf("%d ", tree->data.key);
		preorder(tree->leftchild);
		preorder(tree->rightchild);
	}
}

/*후위 순회*/
void postorder(treePointer tree)
{
	if (tree) {
		postorder(tree->leftchild);
		postorder(tree->rightchild);
		printf("%d ", tree->data.key);
	}
}

/*탐색 함수 */
element* search(treePointer tree, int key)
{
	if (!tree) return NULL;												// key 값이 없으면 NULL값 반환
	if (key == tree->data.key)return &(tree->data);						// key 값이 있으면 데이타 포인터 반환
	if (key < tree->data.key)											// 찾고자 하는 키값이 노드보다 작으면
	{
		return search(tree->leftchild, key);							// root부터 찾는 값이 작으면 왼쪽 자식으로 이동
	}
	else                                                                // key값 보다 크면 
	{
		return search(tree->rightchild, key);							// 오른쪽으로 이동
	}
		
}