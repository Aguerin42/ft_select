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
**	\brief	Affichage de l'argument contenu dans la structure.
**
**	\param	select -	Structure dont l'argument _arg_ doit être affiché.
**
**	\return	**Nombre** de caractères affichés à l'écran
**			ou **0** si _select_ est NULL (ou que _arg_ est NULL).
*/

int			put_tselect(t_select *select)
{
	int	nb;

	nb = 0;
	if (select && select->print)
	{
		if (select->selec)
			ft_putstr(tgetstr("us", NULL));
		if (select->cursor)
			nb = ft_putstr(tgetstr("mr", NULL));
		ft_putstr(select->arg);
		ft_putstr(tgetstr("me", NULL));
	}
	return (nb);
}
