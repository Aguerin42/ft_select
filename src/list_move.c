/**
**	\file	list_move.c
**	\author	Alexis Guérin
**	\date	10 novembre 2017
**
**	\brief	Fonctions de gestion de déplacement dans la liste.
*/

#include "ft_select.h"

static t_list	*find_tail(t_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

static t_list	*find_cursor(t_list *list)
{
	while (list && !(is_oncursor(list->content)))
		list = list->next;
	return (list);
}

t_list	*find_printable(t_list *list)
{
	while (list && !(is_printable(list->content)))
		list = list->next;
	return (list);
}

void			find_previous(t_list *list)
{
	t_list	*tail;

	tail = find_tail(list);
	if (list)
	{
		if ((list = find_cursor(list)))
		{
			if (list->prev)
				set_cursor(list->prev->content);
			else
				set_cursor(tail->content);
			set_cursor(list->content);
		}
	}
}

void			find_next(t_list *list)
{
	t_list	*head;

	head = list;
	if (list)
	{
		if ((list = find_cursor(list)))
		{
			if (list->next)
				set_cursor(list->next->content);
			else
				set_cursor(head->content);
			set_cursor(list->content);
		}
	}
}
