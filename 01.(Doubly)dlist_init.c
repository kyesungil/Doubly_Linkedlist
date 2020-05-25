void dlist_init(DList* list, void (*destroy)(void* data)) {

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;

	return;
}