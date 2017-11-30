/**
**	\file	window.c
**	\author	Alexis Guérin
**	\date	13 novembre 2017
**
**	\brief	Fonctions pour l'affichage
*/

#include "ft_select.h"

/*
**	Nombre de lignes nécessaires à l'affichage d'un argument
*/

static int	nb_line(void *elem, int size)
{
	int			nb;
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		if (select && select->arg && size > 0)
			if ((nb = ft_strlen(select->arg)) > 0 && (nb > size))
				return (nb / size + 1);
	}
	return (1);
}

/**
**	\brief	Nombre de colonnes possibles dans la fenêtre
**
**	Renvoie le nombre de colonnes qu'il est possible d'afficher dans la fenêtre
**	en fonction de sa taille et de celle du plus grand argument.
*/

int			nb_column(struct winsize window, int max_size)
{
	int	res;

	res = max_size ? (window.ws_col / (max_size + 1)) : 1;
	return (res ? res : 1);
}

static void	padding2(t_list *list, struct winsize win, int max_size)
{
	int	line;
	int	column;

	line = 0;
	column = 0;
	if (list)
		while ((list = ft_lstfind(list, is_printable)))
		{
			ft_putstr_fd(tgoto(tgetstr("cm", NULL), column, line), 0);
			put_tselect((t_select*)list->content);
			if (max_size >= win.ws_col)
				line += nb_line((t_select*)list->content, win.ws_col);
			else
			{
				column += max_size + 1;
				if (column + max_size >= win.ws_col)
				{
					column = 0;
					line++;
				}
			}
			list = list->next;
		}
	ft_putendl("");
}

/**
**	\brief	Affichage des arguments en fonction de la taille de la fenêtre
**
**	\param	list -		liste des arguments
**	\param	win -		structure contenant les informations sur les dimensions
**						de la fenêtre
*/

void		padding(t_list *list, struct winsize win)
{
	int	max_size;
	int	column;
	int	nb_print;

	max_size = max_size_arg(list);
	column = nb_column(win, max_size);
	nb_print = ft_lstcount_if(list, is_printable);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	if (((column <= 1 && nb_print > win.ws_row - 1)
		|| ((max_size + 1) * nb_print) > (win.ws_row - 1) * (win.ws_col - 2)))
	{
		ft_putstr_fd(tgetstr("cl", NULL), 0);
		ft_putstr_fd("The window is too small...", 2);
	}
	else if (list)
		padding2(list, win, max_size);
}
