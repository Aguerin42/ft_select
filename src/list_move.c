/**
**	\file	list_move.c
**	\author	Alexis Guérin
**	\date	10 novembre 2017
**
**	\brief	Fonctions de gestion de déplacement dans la liste.
*/

#include "ft_select.h"

/*
**	\brief	Renvoie la queue de liste.
**
**	\param	list -	Tête de liste
*/

static t_list	*find_tail(t_list *list)
{
	while (list->next)
		list = list->next;
	return (list);
}

/*
**	\brief	Renvoie la position du curseur.
**
**	\param	list -	Tête de liste
*/

static t_list	*find_cursor(t_list *list)
{
	while (list && !(is_oncursor(list->content)))
		list = list->next;
	return (list);
}

/**
**	\brief	Renvoie le prochain argument affichable.
**
**	\param	list -	Tête de liste
*/

t_list			*find_printable_right(t_list *list)
{
	while (list && !(is_printable(list->content)))
		list = list->next;
	return (list);
}

/*
**	\brief	Renvoie le précédent argument affichable.
**
**	\param	list -	Tête de liste
*/

static t_list		*find_printable_left(t_list *list)
{
	while (list && !is_printable(list->content))
		list = list->prev;
	return (list);
}

/**
**	\brief	Déplace le curseur sur le prochain argument.
**
**	\param	list -	Tête de liste
*/

void			find_next(t_list *list)
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
}

/**
**	\brief	Déplace le curseur sur le précédent argument.
**
**	\param	list -	Tête de liste
*/

void			find_previous(t_list *list)
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
}
