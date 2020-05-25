# Doubly_Linkedlist  
## 1. Doubly_Linkedlist 구성  
- __양방향으로 traverse 가능하도록 linked list 보완__  
![doubly 구성](https://user-images.githubusercontent.com/41607872/82788179-e9a4be80-9ea2-11ea-8c52-4b1546999ad2.jpg)  
- __그림상의 네모를 노드라 할때, 각 노드의 전 노드 주소는 prev pointer에 저장하고 다음 노드의 주소는 next pointer에 저장한다.__
- __각 노드가 메모리에 여기저기 흩어져 있기 때문에 리스트의 첫 노드(elemnet)주소를 기억해야한다.__  
  1. _head pointer_: 첫 노드의 주소 저장  
  2. _tail pointer_: 마지막 노드의 주소 저장  
  3. 리스트의 마지막 노드의 next값은 NULL로 지정(마지막 노드 체크을 위해서)  
  4. 리스트의 첫번째 노드의 prev값은 NULL로 지정(첫번째 노드 체크을 위해서)  
#### code  
```c  
typedef struct DList_
{
	int	    size;
	DListElmt*  head;
	DListElmt*  tail;

	int		(*match)(const void* key1, const void* key2);
	void	(*destroy)(void* data);
}DList;
```  
***  
## 2. 노드(또는 element)의 구성(ListElmt)  
- __데이터 포인터(void* data):__  저장할 데이터의 주소를 가진다.  
  _자료형 void*인 이유는? 테이터의 타입이 정해져 있지 않기 때문이다. 예로 학생데이터 또는 로봇데이터가 저장되있을 수 있다. 그래서 나중에 캐스팅해준다._
- __next 포인터(ListElmt* next):__  다음 노드의 주소를 저장, 즉 연결선  
- __prev 포인터(ListElmt* prev):__  전 노드의 주소를 저장  
#### code  

```c
typedef struct DListElmt_
{
	void	  *data;	/* pointer to data storage */
	struct DListElmt_ *next;	/* next pointer */
	struct DListElmt_ *prev;	/* previous pointer */

}DListElmt;  
```
***  
## 3. Linled list 인터페이스 함수  
### 3-1. Doubly Linked lsit 초기화 함수: dlist_init(DList* list, void (*destroy)(void* data))  
- dlist(Doubly Linked list 전체)의 Doubly linked list를 초기화. 리스트를 사용하기 전에 항상 제일 먼저 호출되어야 한다. destroy는 data에 동적 할당된 메모리를 해제하기 위해 호출되는 함수의 포인터. 
특별히 할당된 메모리 해제가 필요 없으면 NULL로 지정한다.  
- head와 tail은 NULL 값으로 지정, list의 size 즉, 데이터의 개수 0으로 지정  
- Linked list와 동일하다.  
#### code  
```c
void dlist_init(DList* list, void (*destroy)(void* data)) {

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}
```  
### 3-2. 데이터를 Linked list(element 다음 노드)에 끼워넣는 함수: dlist_ins_next(DList* list, DListElmt* element, const void* data)  
- 구현
  1. 성공하면 return 0, 실패하면 return -1.
  2. element의 바로 뒤에 끼워 넣기.  
  3. 순서  
    [1] new_element 메모리 할당  
    [2] new_element->data에 데이터 연결  
    [3] new_element의 next pointer와 element의 다음 노드 주소 연결(new_element->next = element->next)    
    [4] new_element의 prev pointer와 element 연결(new_element->prev = element)      
    [5] element의 다음 노드의 prev pointer와 new_element 연결(element->next->prev = new_element)   
    [6] element의 next pointer와 new_elemnet 연결(element->next = new_elemnet)  
    _※ 처음 노드 추가할 때: head와 tail을 new_element지정, next와 prev pointer을 NULL로 지정._  
    _※ element가 tail일 경우: tail을 new_element지정._  
    
#### 1) 노드가 중간에 들어올 때  
![1_ins3](https://user-images.githubusercontent.com/41607872/82790163-97659c80-9ea6-11ea-9e73-0e48b39b8bf8.jpg)  
![1_ins4](https://user-images.githubusercontent.com/41607872/82790191-a8161280-9ea6-11ea-81d2-78bc78a31841.jpg)  
![1_ins5](https://user-images.githubusercontent.com/41607872/82790197-a9dfd600-9ea6-11ea-9ff0-845e820742c6.jpg)  
![1_ins6](https://user-images.githubusercontent.com/41607872/82790203-acdac680-9ea6-11ea-9033-494056c3cf75.jpg)  
#### code   
```c  
int dlist_ins_next(DList* list, DListElmt* element, const void* data)
{
	// element 메모리 할당
	DListElmt* new_element;

	if (element == NULL && dlist_size(list) != 0)
		return -1;

	if ((new_element = (DListElmt*)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	// new_element->data에 데이터 연결
	new_element->data = (void*)data;

	// Handle insertion when the list is empty
	if (dlist_size(list) == 0)
	{
		list->head = new_element;
		list->head->next = NULL;
		list->head->prev = NULL;
		list->tail = new_element;
	}
	else // Handle insertion when not empty
	{
		new_element->next = element->next;
		new_element->prev = element;

		// element가 마지막인지 체크
		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;
		element->next = new_element;
	}

	list->size++;
	return 0;
}  
```  
### 3-3. 데이터를 Linked list(element 전 노드)에 끼워넣는 함수: dlist_ins_prev(DList* list, DListElmt* element, const void* data)    
- 구현
  1. 성공하면 return 0, 실패하면 return -1.  
  2. element의 바로 앞에 끼워 넣기.  
3. 순서    
    [1] new_element 메모리 할당  
    [2] new_element->data에 데이터 연결  
    [3] new_element의 next pointer와 element연결(new_element->next = element)     
    [4] new_element의 prev pointer와 element의 prev pointer연결(new_element->prev = element->prev)          
    [5] element의 전 노드의 next pointer와 new_element연결(element->prev->next = new_element)  
    [6] element의 prev pointer와 new_element연결(element->prev = new_element)   
    _※ 처음 노드 추가할 때, element가 head일 때 고려_  
    
#### 1) 노드가 중간에 들어올 때      
![isert3](https://user-images.githubusercontent.com/41607872/82791936-8d916880-9ea9-11ea-9b86-721974b1045e.jpg)
![inser4](https://user-images.githubusercontent.com/41607872/82791939-8ff3c280-9ea9-11ea-8c4a-722a88d6bd4a.jpg)
![insert5](https://user-images.githubusercontent.com/41607872/82791949-91bd8600-9ea9-11ea-99b7-f924ce8e7257.jpg)
![insert6](https://user-images.githubusercontent.com/41607872/82791953-941fe000-9ea9-11ea-9fcc-afef532f5390.jpg)  
#### code  
```c  
int dlist_ins_prev(DList* list, DListElmt* element, const void* data)
{
	DListElmt* new_element;

	// Do not allow a NULL element unless the list is empty.
	if (element == NULL && dlist_size(list) != 0)
		return -1;

	// 메모리 할당
	if ((new_element = (DListElmt*)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	// 데이터 연결
	new_element->data = (void*)data;


	// Handle insertion when the list is empty.
	if (dlist_size(list) == 0)
	{
		list->head = new_element;
		list->head->next = NULL;
		list->head->prev = NULL;
		list->tail = new_element;

	}
	else // Handle insertion when the list is not empty.
	{
		new_element->next = element;
		new_element->prev = element->prev;

		if (element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;
		element->prev = new_element;
	}

	list->size++;

	return 0;
}
```  
### 3-4. 데이터를 linked list에서 삭제하는 함수: int dlist_remove(DList* list, DListElmt* element, void** data)  
- parmamter
  1. _ListElmt* element:_ 삭제할 노드  
  2. _void **data:_ 삭제할 data을 담기위한 매개변수
  ※ (data안에 연속적으로 동적할당 될 경우때문에 함수 자체 내에서 free하지 않는다.)  
- 구현  
  1. 성공하면 return 0, 실패하면 return -1.  
  2. element로 지정된 노드를 삭제(prev 포인터로 인해 지정된 element삭제 가능) return시에 삭제되는 element에 연결된 데이터의 포인터가 data에 저장됨  
- 순서  
  [1] element의 전 노드의 next pointer와 element의 다음 노드 연결(element->prev->next = element->next)  
  [2] element의 다음 노드의 prev pointer와 element의 전 노드 연결(element->next->prev = element->prev)  
   _※ element가 head일 경우: element->next을 head로 지정, element->next->prev을 NULL로 지정_    
   _※ element가 head이고 노드가 1개일 경우: tail을 NULL로 지정_    
   _※ elemet가 tail일 경우: element->prev을 tail로 지정_    
  
#### 1) 중간에 데이터를 삭제할 때  
![d1](https://user-images.githubusercontent.com/41607872/82794991-540f2c00-9eae-11ea-8079-93ebe6e3a121.jpg)
![d2](https://user-images.githubusercontent.com/41607872/82795005-57a2b300-9eae-11ea-8417-20d62a24d4ca.jpg)  
#### code  
    
```c  
int dlist_remove(DList* dlist, DListElmt* element, void** data)
{
	
	// Do not allow a NULL element or removal from an empty list. 
	
	if (dlist_size(dlist) == 0 || element == NULL)
		return -1;

	*data = element->data; // 삭제할 데이터 link

	// element가 head일때
	if (element == dlist->head)
	{
		dlist->head = element->next;
		if (dlist->head == NULL) // 노드가 1개일때
			dlist->tail == NULL;
		else
			element->next->prev = NULL;
	}
	else
	{
		element->prev->next = element->next;

		// element가 tail일때
		if (element->next == NULL)
			dlist->tail = element->prev;
		else
			element->next->prev = element->prev;
	}
	
	free(element);

	dlist->size--;

	return 0;
}    
```  
[강릉원주대 박래정교수님 수업 참조]
