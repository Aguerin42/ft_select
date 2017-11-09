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

void	unset_print(t_select *elem)
{
	if (elem)
		elem->print = 0;
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

void	select_change(t_select *elem)
{
	if (elem)
		elem->selec = !elem->selec;
}

void	select_arg(t_select *elem)
{
	if (elem)
		elem->selec = 1;
}

void	unselect_arg(t_select *elem)
{
	if (elem)
		elem->selec = 0;
}

void	set_all_member(t_select *elem)
{
	if (elem)
	{
		elem->cursor = 0;
		elem->selec = 0;
		elem->print = 1;
	}
}
