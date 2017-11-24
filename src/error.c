/**
**	\file	error.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Messages d'erreur généraux.
**
**	Chacune de ces fonctions renvoie **-1**.
*/

#include "ft_select.h"

/**
**	Affichage de message après effacement de l'écran
**
**	Affiche le message `msg` sur la sortie `fd`, après que le curseur ait été
**	positionné en haut à gauche de la fenêtre et que celle-ci ait été effacée.
*/

void	print_message(char *msg, int fd)
{
	ft_putstr_fd(tgetstr("cl", NULL), 0);
	ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), 0);
	ft_putendl_fd(msg, fd);
}

/**
**	\brief	Erreur d'allocation.
*/

int		error_alloc(void)
{
	print_message("ft_select: allocation error. Exit", 2);
	return (-1);
}

/**
**	\brief	Échec de récupération des dimensions de la fenêtre.
*/

int		error_winsize(void)
{
	print_message("ft_select: failed to get window size. Exit", 2);
	return (-1);
}
