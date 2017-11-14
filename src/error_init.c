/**
**	\file	error_init.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Erreurs à afficher lorsque le lancement de _ft_select_
**			est incorrect.
**	
**	Message d'erreur lorsque _ft_select_ est lancé sans argument,
ee
**	Chacune de ces fonctions renvoie **-1**.
*/

#include "ft_select.h"

/**
**	\brief	Message d'erreur en cas de lancement de *ft_select* sans argument
*/

int	error_usage(void)
{
	ft_putendl_fd("usage: ft_select argument ...", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur en cas d'environnement vide.
*/

int	error_noenv(void)
{
	ft_putendl_fd("ft_select: set an environment to continue. Exit.", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur si la variable TERM n'est pas définie
**			ou si elle est vide.
*/

int	error_termvar(void)
{
	ft_putendl_fd("ft_select: set the TERM variable to continue. Exit.", 2);
	return (-1);
}
