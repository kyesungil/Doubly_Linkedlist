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