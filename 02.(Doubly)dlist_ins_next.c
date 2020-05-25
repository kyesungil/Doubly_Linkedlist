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