/**
**	\file	list_move.c
**	\author	Alexis Guérin
**	\date	10 novembre 2017
**
**	\brief	Fonctions de gestion de déplacement dans la liste.
**
**	L'argument `list` est toujours la tête de liste.
*/

#include "ft_select.h"

/*
**	\brief	Renvoie la queue de liste.
*/

static t_list	*find_tail(t_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

/*
**	\brief	Renvoie la position du curseur.
*/

static t_list	*find_cursor(t_list *list)
{
	while (list && !(is_oncursor(list->content)))
		list = list->next;
	return (list);
}

/**
**	\brief	Renvoie le prochain argument affichable.
*/

t_list			*find_printable_right(t_list *list)
{
	while (list && !(is_printable(list->content)))
		list = list->next;
	return (list);
}

/*
**	\brief	Renvoie le précédent argument affichable.
*/

static t_list		*find_printable_left(t_list *list)
{
	while (list && !is_printable(list->content))
		list = list->prev;
	return (list);
}

/**
**	\brief	Déplace le curseur sur le premier élément.
*/

void				move_first(t_list *list)
{
	t_list	*head;

	if (list)
	{
		head = list;
		list = find_cursor(list);
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
		tail = find_tail(list);
		list = find_cursor(list);
		set_cursor(list->content);
		set_cursor(tail->content);
	}
}

/**
**	\brief	Déplace le curseur sur l'élément du dessus
*/

int					move_up(t_list *list, struct winsize win)
{
	int		column;
	t_list	*origin;

	if (list)
	{
		origin = find_cursor(list);
		column = nb_column(win, max_size_arg(list));
		list = origin;
		while (list->prev && (column-- > 0))
			list = find_printable_left(list->prev);
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
		origin = find_cursor(list);
		column = nb_column(win, max_size_arg(list));
		list = origin;
		while (list->next && (column-- > 0))
			list = find_printable_right(list->next);
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

	head = find_printable_right(list);
	if (list && (list = find_cursor(list)))
	{
		set_cursor(list->content);
		if (!(list = find_printable_right(list->next)))
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

	tail = find_printable_left(find_tail(list));
	if (list && (list = find_cursor(list)))
	{
		set_cursor(list->content);
		if (!(list = find_printable_left(list->prev)))
			list = tail;
		if (list)
			set_cursor(list->content);
	}
	return (0);
}
