/*
	��������� traverse �����ϵ��� linked list ����
*/

typedef struct DListElmt_
{
	void			  *data;	/* pointer to data storage */
	struct DListElmt_ *next;	/* next pointer */
	struct DListElmt_ *prev;	/* previous pointer */

}DListElmt;


typedef struct DList_
{
	int			size;
	DListElmt*  head;
	DListElmt*  tail;

	int		(*match)(const void* key1, const void* key2);
	void	(*destroy)(void* data);
}DList;

#define dlist_size(list) ((list)->size)

#pragma once
