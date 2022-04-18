#include<stdio.h>
#include<stdlib.h>

/* �ʿ��� ������� �߰� */

typedef struct Node{  //����ü Node ����
	int key;
	struct Node* link; //����ü ������ ���� link ����
} listNode; 

typedef struct Head {  //����ü Head  ����
	struct Node* first; //����ü Node�� ������ ���� first ����
}headNode; 


/* �Լ� ����Ʈ */
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
	int key; // int�� ����key ����
	headNode* headnode=NULL; //����ü ������ ������ NULL�� ����

	do{
		printf("[----- [���°�]] [2019038059] -----]");
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
		scanf(" %c", &command); //Ŀ�ǵ� �Է�

		switch(command) { 
		case 'z': case 'Z': //z�Ǵ� Z�� �Է¹��� ���
			headnode = initialize(headnode); //initalize �Լ� ���� �� ���ϰ��� headnode�� ����
			break;
		case 'p': case 'P':  //p�Ǵ� P �� �Է¹��� ���
			printList(headnode); // printList �Լ� ����
			break;
		case 'i': case 'I': //i�Ǵ� I�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է� 
			insertNode(headnode, key);// insertnode �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'd': case 'D': //d�Ǵ�D�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key���� �Է�
			deleteNode(headnode, key);//deleteNode �Լ� ���� -> key���� �Ѱ��ش� 
			break;
		case 'n': case 'N'://n�� �Է¹��� ���
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է� 
			insertLast(headnode, key);//insertLast �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 'e': case 'E'://e�Ǵ� E�� �Է¹��� ���
			deleteLast(headnode);//deleteLast �Լ� ���� 
			break;
		case 'f': case 'F'://f�Ǵ� F��  �Է¹��� �ܿ�
			printf("Your Key = ");
			scanf("%d", &key);//key�� �Է�
			insertFirst(headnode, key);//insertFirst �Լ� ���� -> key���� �Ѱ��ش�
			break;
		case 't': case 'T'://t�Ǵ� T�� �Է¹��� ���
			deleteFirst(headnode);//deleteFirst �Լ� ����
			break;
		case 'r': case 'R'://r�Ǵ� R�� �Է¹��� ���
			invertList(headnode);//invertList �Լ� ����
			break;
		case 'q': case 'Q'://q�Ǵ� Q�� �Է¹��� ���
			freeList(headnode);//freeList �Լ� ����
			break;
		default://�ٸ� Ŀ�ǵ带 �Է¹��� ��� �����̶�� ��� �޼��� ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); 

	return 1;
}

headNode* initialize(headNode* h) {   //hadenode ������ ������ �����Ҵ� �� �޸� �����ϴ� �Լ�

	
	if(h != NULL) // headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ����
		freeList(h);

	
	headNode* temp = (headNode*)malloc(sizeof(headNode)); // headNode�� ���� ������ ���� temp �޸� ���� �Ҵ�
	temp->first = NULL; // ���ο� ���� ����Ʈ�� �����
	return temp; //temp ����
}

int freeList(headNode* h){ 
	/* h�� ����� listNode �޸� ����
	 * headNode�� �����Ǿ�� ��.
	 */
	listNode* p = h->first; //����ü listNode�� ������ ���� p�� ����Ʈ�� ���� �ּ� ����

	listNode* prev = NULL; //prev��� ���ο� ���� ����Ʈ ����
	while(p != NULL) {   //p���� NULL�� �ƴҶ� ����
		prev = p; //prev�� p �����Ѵ�
		p = p->link;//p���� p->link �����Ѵ�
		free(prev);//prev �޸� �Ҵ� ���� 
	}
	free(h);//h �޸� �Ҵ� ����
	return 0;
}


/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */
int insertNode(headNode* h, int key) { //��忡 ���� �Է��ϴ� �Լ�

	listNode* node = (listNode*)malloc(sizeof(listNode)); //listNode ����ü ������ ���� node�� �����Ҵ�
	node->key = key;  // ���ο� ����� key���� �Է¹��� key���� ����
	node->link = NULL;// node->link�� ����� ���� ������ ��Ÿ��

	if (h->first == NULL) //��尡 NULL�ϰ��
	{
		h->first = node; //ù��° ��忡 �Է¹��� node �� ����
		return 0;
	}
    
	listNode* n = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����
	listNode* trail = h->first; // ���ο� ��带 ���� �� ���Ḯ��Ʈ ù��° �ּҸ� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) 
    { 
		if(n->key >= key) /* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
        { 
			
			if(n == h->first) // n�� ��� ����� ���(ù��° ����� ���)
            {
				h->first = node;  //�Է¹��� ��带 ��� ���� �ٲ۴�
				node->link = n;  //����� ��ũ�� n�� ����
			} 
            else /* �߰��̰ų� �������� ��� */
            { 
				node->link = n; 
				trail->link = node;
			}
			return 0;
		}
             // ��ĭ�� �̵��ϸ鼭 �־��� �ڸ��� ã�´�
		trail = n; //trail��n����
		n = n->link;
	}

	/* ������ ������ ã�� ���� ��� , �������� ���� */
	trail->link = node;
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //����ü ��带 �����Ҵ� ����
	node->key = key;  //����� Ű���� �Է¹��� �� ����
	node->link = NULL; //���θ��� ����� ��ũ�� NULL

	if (h->first == NULL) //��� ����� ���� NULL�ΰ��
	{
		h->first = node; //����尡 node�� ����Ŵ
		return 0;
	}

	listNode* n = h->first; // ���Ḯ��Ʈ ��� n�� h_>first�� ��Ÿ��
	while(n->link != NULL) { //����� ��ũ�� NULL�� �ƴѰ�� 
		n = n->link; //��尡 ��ĭ�� �̵� 
	}
	n->link = node; // ��������� �ڿ� ���� 
	return 0;
}

/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //node ���� �Ҵ� ����
	node->key = key; //node key���� �Է¹��� key���� ����

	node->link = h->first; //node ->link�� ù��° ��带 ����Ű�� ��
	h->first = node;//����带 ����

	return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) { 

	if (h->first == NULL)   //��� ����� ����NULL�ΰ��
	{
		printf("nothing to delete.\n");//�����޼��� ���
		return 0;
	}

	listNode* n = h->first;  //n ��尡 ù�� ° ��带 ����Ŵ
	listNode* trail = NULL; // ����ִ� ��� ����

	/* key�� �������� ������ ��ġ�� ã�´� */
	while(n != NULL) {
		if(n->key == key) {
			/* ù ��� ���ʿ� �����ؾ��� ��� ���� �˻� */
			if(n == h->first) {
				h->first = n->link;
			} else { /* �߰��� ���ų� �������� ��� */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}
         //��带 ��ĭ�� �̵�
		trail = n; 
		n = n->link;
	}  

	/* ã�� �� �Ѱ�� */
	printf("cannot find the node for key = %d\n", key); //�Է¹��� Ű���� ã���� ���ٰ� ���
	return 0;

}

/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {

	if (h->first == NULL) //����� ����NuLL�ΰ��
	{
		printf("nothing to delete.\n");//���� �޼��� ���
		return 0;
	}

	listNode* n = h->first; //n�� ����� ����Ŵ
	listNode* trail = NULL; //����ִ� ��带 �����Ѵ�

	/* ��尡 �ϳ��� �ִ� ���, �� first node == last node��  ��� ó�� */
	if(n->link == NULL) { 
		h->first = NULL;
		free(n); 
		return 0;
	}

	
	while(n->link != NULL) { //��带 ��ĭ�� �̵��ϸ� ������ ������ �̵�
		trail = n;//trail�� n�� ����
		n = n->link;
	}

	// n�� �����ǹǷ�, ���� ����� ��ũ NULL ó��
	trail->link = NULL;
	free(n); //�޸��Ҵ� ����

	return 0;
}
/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL) //����尡 NULL�ΰ��
	{
		printf("nothing to delete.\n");//�����޼��� ���
		return 0;
	}
	listNode* n = h->first; //n�� ��� ��带 ����Ŵ

	h->first = n->link; //2��° ��带 ������ ���� 
	free(n);//�޸� �Ҵ�  ����

	return 0;
}


/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {


	if(h->first == NULL) { //����� ���� NuLL�ϋ�
		printf("nothing to invert...\n");//�����޼��� ���
		return 0;
	}
	listNode *n = h->first; //n�� ����带 ����Ŵ
	listNode *trail = NULL; // ����ִ� ��带 ����
	listNode *middle = NULL; // ����ִ� ��带 ����

	while(n != NULL){// �� ��尡 ���ö����� �ݺ�
		trail = middle;  //trail�� middle�� ����
		middle = n; //middle�� n�� ����  ����
		n = n->link;//n�� n->link�� �־���
		middle->link = trail; // middle�� ��ũ�� ���� ����� trail�� ����Ŵ 
	}

	h->first = middle; //���������� n�� null�� ����Ű�� middle�� ������ ��带 ����Ű�� ������ middle�� ����尡 �ȴ�

	return 0;
}


void printList(headNode* h) { //���Ḯ��Ʈ�� ����ϴ� �Լ�
	int i = 0;    
	listNode* p; //����ü ������ ���� ����

	printf("\n---PRINT\n");

	if(h == NULL) { //h���� NULL�϶�
		printf("Nothing to print....\n");
		return;
	}

	p = h->first; //p�� ����带 ����Ŵ

	while(p != NULL) { //��尡NULL�� �ƴҶ�
		printf("[ [%d]=%d ] ", i, p->key); //�ε�����ȣ�� Ű���� ���
		p = p->link; //p�� ������带 ����Ű�� ��
		i++; //i�� 1�� ����
	}

	printf("  items = %d\n", i); //�����ϴ� ���� ���� ���
}