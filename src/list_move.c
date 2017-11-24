/**
**	\file	list_move.c
**	\author	Alexis Guérin
**	\date	10 novembre 2017
**
**	\brief	Fonctions de gestion de déplacement dans la liste.
**
**	L'argument `list` doit toujours être la tête de liste.
*/

#include "ft_select.h"

/**
**	\brief	Déplace le curseur sur l'élément du dessus
*/

int				move_up(t_list *list, struct winsize win)
{
	int		column;
	t_list	*origin;

	if (list)
	{
		origin = ft_lstfind(list, is_oncursor);
		column = nb_column(win, max_size_arg(list));
		list = origin;
		while (list && list->prev && (column-- > 0))
			list = ft_lstfind_prev(list->prev, is_printable);
		if (!(list))
			list = origin;
		if (column <= 0)
		{
			set_cursor(origin->content);
			set_cursor(list->content);
		}
	}
	return (2);
}

/**
**	\brief	Déplace le curseur sur l'élément du dessous.
*/

int				move_down(t_list *list, struct winsize win)
{
	int		column;
	t_list	*origin;

	if (list)
	{
		origin = ft_lstfind(list, is_oncursor);
		column = nb_column(win, max_size_arg(list));
		list = origin;
		while (list && list->next && (column-- > 0))
			list = ft_lstfind(list->next, is_printable);
		if (!(list))
			list = origin;
		if (column <= 0)
		{
			set_cursor(origin->content);
			set_cursor(list->content);
		}
	}
	return (3);
}

/**
**	\brief	Déplace le curseur sur le prochain argument.
*/

int				move_right(t_list *list)
{
	t_list	*head;

	head = ft_lstfind(list, is_printable);
	if (list && (list = ft_lstfind(list, is_oncursor)))
	{
		set_cursor(list->content);
		if (!(list = ft_lstfind(list->next, is_printable)))
			list = head;
		if (list)
			set_cursor(list->content);
	}
	return (1);
}

/**
**	\brief	Déplace le curseur sur le précédent argument.
*/

int				move_left(t_list *list)
{
	t_list	*tail;

	tail = ft_lstfind_prev(ft_lstfind_tail(list), is_printable);
	if (list && (list = ft_lstfind(list, is_oncursor)))
	{
		set_cursor(list->content);
		if (!(list = ft_lstfind_prev(list->prev, is_printable)))
			list = tail;
		if (list)
			set_cursor(list->content);
	}
	return (0);
}
