// 중복된 자료 하나 남기고 삭제
int remove_duplicat_device(DList* dlist)
{
	DListElmt* search1;
	DListElmt* search2;

	void* data;

	if (dlist->size < 2)
		return -1;

	for (search1 = dlist->head; search1 != NULL; search1 = search1->next)
	{
		for (search2 = search1->next; search2 != NULL; search2 = search2->next)
		{
			if (strcmp(((device*)search1->data)->dv_name, ((device*)search2->data)->dv_name) == 0)
			{
				// search2를 free하면 run time error발생
				search2 = search2->prev;

				dlist_remove(&dlist, search2->next, &data);
				free(data);
			}
		}
	}
	return 0;
}