/**
**	\file	struct_is.c
**	\author	Alexis Guérin
**	\date	9 novembre 2017
**
**	\brief	Fonctions de vérification des champs de la structure `t_select`
**
**	Le paramètre `elem` doit être une structure `t_select` (`s_select`).
**
**	Les fonctions renvoient **1** ou **0**.
*/

#include "ft_select.h"

/**
**	\brief	Vérification de l'état du curseur de l'argument.
*/

int		is_oncursor(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		return (select->cursor);
	}
	return (0);
}

/**
**	\brief	Vérification de l'état d'affichage de l'argument.
*/

int		is_printable(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		return (select->print);
	}
	return (0);
}

/**
**	\brief	Vérification de l'état de sélection de l'argument.
*/

int		is_select(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		return (select->selec);
	}
	return (0);
}
