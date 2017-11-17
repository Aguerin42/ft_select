/**
**	\file	window.c
**	\author	Alexis Guérin
**	\date	13 novembre 2017
**
**	\brief	Fonctions pour l'affichage
*/

#include "ft_select.h"

static int	nb_line(void *elem, int size)
{
	int			nb;
	t_select	*select;
	
	if (elem)
	{
		select = (t_select*)elem;
		if (select && select->arg && size > 0)
			if ((nb = ft_strlen(select->arg)) > 0 && (nb > size))
				return (nb/size + 1);
	}
	return (1);
}

/**
**	\brief	Calcul du nombre de lignes nécessaires à l'affichage
**
**	La fonction calcule, en fonction des arguments affichables et de la taille
**	de la fenêtre, le nombre de lignes nécessaires pour pouvoir afficher tous
**	les arguments.
**
**	\param	list -		liste d'arguments
**	\param	win_size -	taille de la fenêtre en colonnes
**
**	\return	**0** si `list` est `NULL`
**			ou un **nombre strictement positif** sinon
*/

int			nb_line_tot(t_list *list, int win_size)
{
	int	i;

	i = 0;
	while (list && list->content)
	{
		i += nb_line(list->content, win_size);
		list = list->next;
	}
	return (i);
}


/**
**	\brief	Nombre de colonnes possibles dans la fenêtre
**
**	Renvoie le nombre de colonnes qu'il est possible d'afficher dans la fenêtre
**	en fonction de sa taille et de celle du plus grand argument.
*/

int			nb_column(struct winsize window, int max_size)
{
	return (max_size ? (window.ws_col / (max_size + 1)) : 0);
}

/**
**	\brief	Affichage des arguments en fonction de la taille de la fenêtre
**
**	\param	list -		liste des arguments
**	\param	window -	structure contenant les informations sur les dimensions
**						de la fenêtre
*/

void		padding(t_list *list, struct winsize window)
{
	int	line;
	int	column;
	int	max_size;

	line = 0;
	column = 0;
	max_size = max_size_arg(list);
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	if (max_size > window.ws_col &&
			nb_line_tot(list, window.ws_col) > window.ws_row - 1)
		print_message("The window is too small...", 2);
	else
	{
		while ((list = find_printable_right(list)))
		{
			ft_putstr_fd(tgoto(tgetstr("cm", NULL), column, line), 0);
			put_tselect((t_select*)list->content);
			if (max_size >= window.ws_col)
				line += nb_line((t_select*)list->content, window.ws_col);
			else
			{
				column += max_size + 1;
				if (column + max_size >= window.ws_col)
				{
					column = 0;
					line++;
				}
			}
			list = list->next;
		}
		ft_putendl("");
	}
}

/**
**	Affichage de message après effacement de l'écran
**
**	Affiche le message `msg` sur la sortie `fd`, après que le curseur ait été
**	positionné en haut à gauche de la fenêtre et que celle-ci ait été effacée.
*/

void		print_message(char *msg, int fd)
{
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL),  0, 0), 0);
	ft_putendl_fd(msg, fd);
}
