/**
**	\file	key.c
**	\author	Alexis Guérin
**	\date	24 novembre 2017
**
**	\brief	Reconnaissance des touches
*/

#include "ft_select.h"

/*
**	\brief	Sélection par partie
**
**	Sélectionne tous les arguments situés entre le curseur et le précédent
**	argument déjà sélectionné (ou le début de la liste s'il n'y en a pas)
*/

static void	select_part(t_list *list)
{
	while (list && !is_oncursor(list->content))
		list = list->next;
	if (list)
	{
		select_arg((t_select*)list->content);
		list = list->prev;
	}
	while (list && !is_select(list->content))
	{
		select_arg((t_select*)list->content);
		list = list->prev;
	}
}

/*
**	Flèches, tabulation gauche et touches spéciales `home` et `end`.
*/

static void	arr(char buffer[], t_list *list, int *direction, struct winsize win)
{
	if (buffer[2] == 68 || buffer[2] == 90)
		*direction = move_left(list);
	else if (buffer[2] == 67)
		*direction = move_right(list);
	else if (buffer[2] == 65)
		*direction = move_up(list, win);
	else if (buffer[2] == 66)
		*direction = move_down(list, win);
	else if (buffer[2] == 72)
		move_first(list);
	else if (buffer[2] == 70)
		move_last(list);
}

/*
** Touche echap, espace ou `shift+A`, `shift+D`, `shift+S` et `shift+Z`
*/

static int	key2(char buffer[], t_list *list, int *direction)
{
	if (buffer[0] == 10 && !buffer[1] && !buffer[2])
	{
		term_default(1, NULL);
		ft_lstiter_if(list, put_select_arg, is_select);
		ft_putendl_fd("", 0);
		return (-1);
	}
	else if (buffer[0] == 32 && !buffer[1] && !buffer[2])
	{
		ft_lstiter_if(list, select_change, is_oncursor);
		if (*direction == 0)
			move_left(list);
		else if (*direction == 1)
			move_right(list);
	}
	else if (buffer[0] == 65 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, select_arg, is_printable);
	else if (buffer[0] == 68 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, unselect_arg, is_printable);
	else if (buffer[0] == 83 && !buffer[1] && !buffer[2])
		select_part(list);
	else if (buffer[0] == 90 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, select_change, is_printable);
	return (0);
}

/**
**	\brief Action à réaliser à l'appuie d'une touche
**
** 	Direction : sens de direction du précédent déplacement.
**	- 0 : gauche
**	- 1 : droite
*/

int			key(char buffer[], t_list *list, int *direction, struct winsize win)
{
	if (!list || (buffer[0] == 27 && !buffer[1] && !buffer[2]))
	{
		term_default(1, NULL);
		return (-1);
	}
	if ((buffer[0] == 127 && !buffer[1] && !buffer[2]) ||
		(buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51 &&
			buffer[3] == 126 && !buffer[4] && !buffer[5]))
	{
		ft_lstiter_if(list, unset_print, is_oncursor);
		move_right(list);
		if (!ft_lstany(list, is_printable))
		{
			term_default(1, NULL);
			return (-1);
		}
	}
	else if (buffer[0] == 27 && buffer[1] == 91)
		arr(buffer, list, direction, win);
	else if (buffer[0] == 9 && !buffer[1] && !buffer[2])
		*direction = move_right(list);
	return (key2(buffer, list, direction));
}
