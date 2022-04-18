#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node{  //구조체 Node 정의
	int key;
	struct Node* link; //구조체 포인터 변수 link 선언
} listNode; 

typedef struct Head {  //구조체 Head  정의
	struct Node* first; //구조체 Node의 포인터 변수 first 선언
}headNode; 


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command; //
	int key; // int형 변수key 선언
	headNode* headnode=NULL; //구조체 포인터 변수에 NULL값 저장

	do{
		printf("[----- [윤태경]] [2019038059] -----]");
        printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); 
		scanf(" %c", &command); //커맨드 입력

		switch(command) { 
		case 'z': case 'Z': //z또는 Z를 입력받은 경우
			headnode = initialize(headnode); //initalize 함수 실행 후 리턴값을 headnode에 대입
			break;
		case 'p': case 'P':  //p또는 P 를 입력받은 경우
			printList(headnode); // printList 함수 실행
			break;
		case 'i': case 'I': //i또는 I를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력 
			insertNode(headnode, key);// insertnode 함수 실행 -> key값을 넘겨준다
			break;
		case 'd': case 'D': //d또는D를 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값을 입력
			deleteNode(headnode, key);//deleteNode 함수 실행 -> key값을 넘겨준다 
			break;
		case 'n': case 'N'://n을 입력받은 경우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력 
			insertLast(headnode, key);//insertLast 함수 실행 -> key값을 넘겨준다
			break;
		case 'e': case 'E'://e또는 E를 입력받은 경우
			deleteLast(headnode);//deleteLast 함수 실행 
			break;
		case 'f': case 'F'://f또는 F를  입력받은 겨우
			printf("Your Key = ");
			scanf("%d", &key);//key값 입력
			insertFirst(headnode, key);//insertFirst 함수 실행 -> key값을 넘겨준다
			break;
		case 't': case 'T'://t또는 T를 입력받은 경우
			deleteFirst(headnode);//deleteFirst 함수 실행
			break;
		case 'r': case 'R'://r또는 R을 입력받은 경우
			invertList(headnode);//invertList 함수 실행
			break;
		case 'q': case 'Q'://q또는 Q를 입력받은 경우
			freeList(headnode);//freeList 함수 실행
			break;
		default://다른 커맨드를 입력받은 경우 집중이라는 경고 메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); 

	return 1;
}

headNode* initialize(headNode* h) {   //hadenode 포인터 변수를 동적할당 및 메모리 해제하는 함수

	
	if(h != NULL) // headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제
		freeList(h);

	
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode에 대한 포인터 변수 temp 메모리 동적 할당
	temp->first = NULL; // 새로운 공백 리스트를 만든다
	return temp; //temp 리턴
}

int freeList(headNode* h){ 
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //구조체 listNode의 포인터 변수 p에 리스트의 시작 주소 대입

	listNode* prev = NULL; //prev라는 새로운 공백 리스트 생성
	while(p != NULL) {   //p값이 NULL이 아닐때 실행
		prev = p; //prev에 p 대입한다
		p = p->link;//p값에 p->link 대입한다
		free(prev);//prev 메모리 할당 해제 
	}
	free(h);//h 메모리 할당 해제
	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) { //노드에 값을 입력하는 함수

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode 구조체 포인터 변수 node를 동적할당
	node->key = key;  // 새로운 노드의 key값에 입력받은 key값을 대입
	node->link = NULL;// node->link가 연결된 값이 없음을 나타냄

	if (h->first == NULL) //노드가 NULL일경우
	{
		h->first = node; //첫번째 노드에 입력받은 node 값 대입
		return 0;
	}
    
	listNode* n = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입
	listNode* trail = h->first; // 새로운 노드를 만든 후 연결리스트 첫번째 주소를 대입

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) 
    { 
		if(n->key >= key) /* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
        { 
			
			if(n == h->first) // n이 헤드 노드일 경우(첫번째 노드인 경우)
            {
				h->first = node;  //입력받은 노드를 헤드 노드로 바꾼다
				node->link = n;  //노드의 링크를 n과 연결
			} 
            else /* 중간이거나 마지막인 경우 */
            { 
				node->link = n; 
				trail->link = node;
			}
			return 0;
		}
             // 한칸씩 이동하면서 넣어줄 자리를 찾는다
		trail = n; //trail에n대입
		n = n->link;
	}

	/* 마지막 노드까지 찾지 못한 경우 , 마지막에 삽입 */
	trail->link = node;
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //구조체 노드를 동적할당 해줌
	node->key = key;  //노드의 키값에 입력받은 값 대입
	node->link = NULL; //새로만든 노드의 링크는 NULL

	if (h->first == NULL) //헤드 노드의 값이 NULL인경우
	{
		h->first = node; //헤드노드가 node를 가리킴
		return 0;
	}

	listNode* n = h->first; // 연결리스트 노드 n이 h_>first를 나타냄
	while(n->link != NULL) { //노드의 링크가 NULL이 아닌경우 
		n = n->link; //노드가 한칸씩 이동 
	}
	n->link = node; // 마지막노드 뒤에 삽입 
	return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node 동적 할당 해줌
	node->key = key; //node key값에 입력받은 key값을 대입

	node->link = h->first; //node ->link가 첫번째 노드를 가리키게 함
	h->first = node;//헤드노드를 변경

	return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) { 

	if (h->first == NULL)   //헤드 노드의 값이NULL인경우
	{
		printf("nothing to delete.\n");//에러메세지 출력
		return 0;
	}

	listNode* n = h->first;  //n 노드가 첫번 째 노드를 가리킴
	listNode* trail = NULL; // 비어있는 노드 생성

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL) {
		if(n->key == key) {
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 중간인 경우거나 마지막인 경우 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}
         //노드를 한칸씩 이동
		trail = n; 
		n = n->link;
	}  

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key); //입력받은 키값을 찾을수 없다고 뜬다
	return 0;

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //노드의 값이NuLL인경우
	{
		printf("nothing to delete.\n");//에러 메세지 출력
		return 0;
	}

	listNode* n = h->first; //n이 헤드노드 가리킴
	listNode* trail = NULL; //비어있는 노드를 생성한다

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->link == NULL) { 
		h->first = NULL;
		free(n); 
		return 0;
	}

	
	while(n->link != NULL) { //노드를 한칸씩 이동하며 마지막 노드까지 이동
		trail = n;//trail에 n값 대입
		n = n->link;
	}

	// n이 삭제되므로, 이전 노드의 링크 NULL 처리
	trail->link = NULL;
	free(n); //메모리할당 해제

	return 0;
}
/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //헤드노드가 NULL인경우
	{
		printf("nothing to delete.\n");//에러메세지 출력
		return 0;
	}
	listNode* n = h->first; //n이 헤드 노드를 가리킴

	h->first = n->link; //2번째 노드를 헤드노드로 변경 
	free(n);//메모리 할당  해제

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //노드의 값이 NuLL일떄
		printf("nothing to invert...\n");//에러메세지 출력
		return 0;
	}
	listNode *n = h->first; //n이 헤드노드를 가리킴
	listNode *trail = NULL; // 비어있는 노드를 생성
	listNode *middle = NULL; // 비어있는 노드를 생성

	while(n != NULL){// 빈 노드가 나올때까지 반복
		trail = middle;  //trail에 middle값 대입
		middle = n; //middle은 n에 값을  대입
		n = n->link;//n은 n->link를 넣어줌
		middle->link = trail; // middle의 링크가 이전 노드인 trail을 가리킴 
	}

	h->first = middle; //마지막에는 n이 null을 가리키고 middle이 마지막 노드를 가리키기 때문에 middle이 헤드노드가 된다

	return 0;
}


void printList(headNode* h) { //연결리스트를 출력하는 함수
	int i = 0;    
	listNode* p; //구조체 포인터 변수 선언

	printf("\n---PRINT\n");

	if(h == NULL) { //h값이 NULL일때
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p가 헤드노드를 가리킴

	while(p != NULL) { //노드가NULL이 아닐때
		printf("[ [%d]=%d ] ", i, p->key); //인덱스번호와 키값을 출력
		p = p->link; //p에 다음노드를 가리키게 함
		i++; //i를 1씩 증가
	}

	printf("  items = %d\n", i); //존재하는 값의 갯수 출력
}