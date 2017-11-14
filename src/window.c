/**
**	\file	window.c
**	\author	Alexis Guérin
**	\date	13 novembre 2017
**
**	\brief	Fonctions pour l'affichage
*/

#include "ft_select.h"

/**
**	\brief	Affichage des arguments en fonction de la taille de la fenêtre
**
**	\param	list -		liste des arguments
**	\param	window -	structure contenant les informations sur les dimensions
**						de la fenêtre
**	\param	size_max -	taille du plus grand argument
*/

void	padding(t_list *list, struct winsize window, int size_max)
{
	int	line;
	int	column;

	line = 0;
	column = 0;
	ft_putstr_fd(tgetstr("ti", NULL), 0);
	while (list)
	{
		if ((list = find_printable_right(list)))
		{
			if (size_max < window.ws_col &&
				((column + size_max + 1) > window.ws_col))
			{
				line += 1;
				column = 0;
			}
			else
			{
				ft_putstr_fd(tgoto(tgetstr("cm", NULL), column, line), 0);
				put_tselect((t_select*)list->content);
				column += size_max + 1;
				if (size_max > window.ws_col)
					line += 1;
				list = list->next;
			}
		}
	}
	ft_putendl_fd("", 0);
}

/**
**	Affichage de message après effaçage de l'écran
**
**	Affiche le message `msg` sur la sortie `fd`, après que le curseur ait été
**	positionné en haut à gauche de la fenêtre et que celle-ci ait été effacée.
*/

void	print_message(char *msg, int fd)
{
	ft_putstr_fd(tgetstr("ti", NULL), 0);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL),  0, 0), 0);
	ft_putendl_fd(msg, fd);
}
