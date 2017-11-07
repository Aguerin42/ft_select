/**
**	\file	struct.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de gestion de la structure *t_select*.
*/

#include "ft_select.h"

/**
**	\brief	Libération de mémoire pour la structure *t_select*.
**
**	del_tselect() libère la mémoire allouée pour la structure *t_select*
**	et met son pointeur à NULL.
**
**	\param	struc - Structure dont la mémoire doit être libérée.
*/

void		del_tselect(t_select **struc)
{
	t_select	*del;

	if (struc)
	{
		del = *struc;
		ft_strdel(del->arg ? &del->arg : NULL);
		ft_memdel((void**)struc);
	}
}

/**
**	\brief	Allocation de la mémoire nécessaire à la structure *t_select*.
**
**	\param	arg -	Argument à copier dans la structure.
**
**	\return	**Structure** allouée et initialisée.
*/

t_select	*new_tselect(char *arg)
{
	t_select	*struc;

	if ((struc = (t_select*)ft_memalloc(sizeof(t_select))))
	{
		struc->arg = arg ? ft_strdup(arg) : NULL;
		struc->selec = 0;
		struc->cursor = 0;
		struc->print = 1;
	}
	return (struc);
}

/**
**	\brief	Affichage de l'argument contenu dans la structure.
**
**	\param	select -	Structure dont l'argument _arg_ doit être affiché.
**
**	\return	**Nombre** de caractères affichés à l'écran ou **0** si _select_ est NULL
**			(ou que _arg_ est NULL).
*/

int			put_tselect(t_select *select)
{
	return (select ? ft_putstrs(select->arg) : 0);
}
