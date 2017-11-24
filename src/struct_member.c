/**
**	\file	struct_member.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de modification des champs de la structure `t_select`.
**
**	Le paramètre `elem` doit être une structure `t_select` (`s_select`).
*/

#include "ft_select.h"

/**
**	\brief	Masquer un argument
**
**	Modifie le flag de l'élément pour que l'argument ne puisse pas être affiché.
*/

void	unset_print(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		select->print = 0;
	}
}

/**
**	\brief	Modifier l'état du curseur
**
**	Active ou désactive le curseur sur l'argument donné.
*/

void	set_cursor(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		select->cursor = !select->cursor;
	}
}

/**
**	\brief	Modifier l'état de sélection d'un élément
*/

void	select_change(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		select->selec = !select->selec;
	}
}

/**
**	\brief	Sélectionner un argument
*/

void	select_arg(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		select->selec = 1;
	}
}

/**
**	\brief	Désélectionner un argument
*/

void	unselect_arg(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		select->selec = 0;
	}
}
