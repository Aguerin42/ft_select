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

void				find_first(t_list *list)
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

void				find_last(t_list *list)
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

int					find_up(t_list *list, struct winsize win)
{
	int		column;
	int		last_line;
	t_list	*tail;

	tail = find_tail(list);
	if (list)
	{
		column = nb_column(win, max_size_arg(list));
		last_line = ft_lstcount_if(list, is_printable) % (column ? column : 1);
		list = find_cursor(list);
		set_cursor(list->content);
		if (!list->prev)
			list = tail;
		else
		{
			while (column--)
			{
				if (!(list = find_printable_left(list->prev)))
				{
					list = tail;
					column += 1;
				}
			}
		}
		set_cursor(list->content);
	}
	return (2);
}

/**
**	\brief	Déplace le curseur sur l'élément du dessous
*/

int					find_down(t_list *list, struct winsize win)
{
	int		column;
	int		last_line;
	t_list	*head;

	head = list;
	if (list)
	{
		column = nb_column(win, max_size_arg(list));
		last_line = ft_lstcount_if(list, is_printable) % (column ? column : 1);
		list = find_cursor(list);
		set_cursor(list->content);
		if (!list->next)
			list = head;
		else
		{
			while (column--)
			{
				if (!(list = find_printable_right(list->next)))
				{
					list = head;
					column += 1;
				}
			}
		}
		set_cursor(list->content);
	}
	return (3);
}

/**
**	\brief	Déplace le curseur sur le prochain argument.
**
**	\param	list -	Tête de liste
*/

int				find_next(t_list *list)
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
**
**	\param	list -	Tête de liste
*/

int				find_previous(t_list *list)
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
