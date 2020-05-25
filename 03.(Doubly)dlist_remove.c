/*
	데이터를 linked list에서 삭제하는 함수: int dlist_remove(DList* list, DListElmt* element, void** data)

	parameter
	- DListElmt* element: 삭제할 노드
	- void** data: 삭제할 데이터


	- element로 지정된 element를 삭제(prev 포인터로 인해 지정된 element삭제 가능)
	  return시에 삭제되는 element에 연결된 데이터의 포인터가 data에 저장됨
*/
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