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
**	\brief	Message d'erreur en cas de problème d'allocation.
*/

int	error_alloc(void)
{
	ft_putendl_fd("ft_select: allocation error. Exit", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur en cas de problème de récupération
**			de la taille de la fenêtre.
*/

int	error_winsize(void)
{
	ft_putendl_fd("ft_select: failed to get window size. Exit", 2);
	return (-1);
}
