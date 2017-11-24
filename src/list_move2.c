/**
**	\file	list_move2.c
**	\author	Alexis Guérin
**	\date	24 novembre 2017
**
*/

#include "ft_select.h"

/**
**	\brief	Déplace le curseur sur le premier élément.
*/

void				move_first(t_list *list)
{
	t_list	*head;

	if (list)
	{
		head = list;
		list = ft_lstfind(list, is_oncursor);
		set_cursor(list->content);
		set_cursor(head->content);
	}
}

/**
**	\brief	Déplace le curseur sur le dernier élément.
*/

void				move_last(t_list *list)
{
	t_list	*tail;

	if (list)
	{
		tail = ft_lstfind_tail(list);
		list = ft_lstfind(list, is_oncursor);
		set_cursor(list->content);
		set_cursor(tail->content);
	}
}
