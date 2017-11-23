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
**	\brief	Erreur d'allocation.
*/

int	error_alloc(void)
{
	print_message("ft_select: allocation error. Exit", 2);
	return (-1);
}

/**
**	\brief	Échec de récupération des dimensions de la fenêtre.
*/

int	error_winsize(void)
{
	print_message("ft_select: failed to get window size. Exit", 2);
	return (-1);
}
