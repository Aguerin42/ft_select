/**
**	\file	struct_member.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de modification des champs de la structure _t_select_.
*/

#include "ft_select.h"

/**
**	\brief	Argument affichable
**
**	Modifie le flag de l'élément pour que l'argument puisse être affiché.
*/

void	set_print(t_select *elem)
{
	if (elem)
		elem->print = 1;
}

/**
**	\brief	Argument masqué
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
**	\brief	Modification de l'état du curseur
**
**	Active ou désactive le curseur sur l'argument donné.
*/

void	set_cursor(t_select *elem)
{
	if (elem)
		elem->cursor = !elem->cursor;
}

/**
**	\brief	Modification de l'état de sélection d'un élément
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
**	\brief	Sélection d'un argument
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
**	\brief	Désélection d'un argument
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

/**
**	\brief	Initialisation des champs de la structure _t_select_
*/

void	set_all_member(t_select *elem)
{
	if (elem)
	{
		elem->cursor = 0;
		elem->selec = 0;
		elem->print = 1;
	}
}
