/**
**	\file	error_init.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Erreurs à afficher lorsque le lancement de *ft_select* est incorrect :
** 			argument manquant, environnement vide, variable TERM manquante, ...
*/

#include "ft_select.h"

/**
**	\brief	Message d'erreur en cas de lancement de *ft_select* sans argument
**
**	\return	-1
*/

int	error_usage(void)
{
	ft_putendl_fd("usage: ft_select argument ...", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur en cas d'environnement vide.
**
**	\return	-1
*/

int	error_noenv(void)
{
	ft_putendl_fd("ft_select: set an environment to continue. Exit.", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur si la variable TERM n'est pas définie
**			ou si elle est vide.
**
**	\return	-1
*/

int	error_termvar(void)
{
	ft_putendl_fd("ft_select: set the TERM variable to continue. Exit.", 2);
	return (-1);
}
