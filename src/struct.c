/**
**	\file	struct.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de gestion de la structure `t_select` (`s_select`).
*/

#include "ft_select.h"

/**
**	\brief	Libération de mémoire pour la structure `t_select`.
**
**	del_tselect() libère la mémoire allouée pour la structure `t_select`
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
**	\param	select -	Structure dont l'argument `arg` doit être affiché.
**
**	\return	**Nombre** de caractères affichés à l'écran
**			ou **0** si `select` est NULL (ou que `arg` est NULL).
*/

int			put_tselect(t_select *select)
{
	int	nb;

	nb = 0;
	if (select && select->print)
	{
		if (select->selec)
			ft_putstr_fd(tgetstr("mr", NULL), 0);
		if (select->cursor)
			nb = ft_putstr_fd(tgetstr("us", NULL), 0);
		ft_putstr_fd(select->arg, 0);
		ft_putstr_fd(tgetstr("me", NULL), 0);
	}
	return (nb);
}

/**
**	\brief	Affichage des arguments sans formatage
**
**	Affiche l'argument s'il est sélectionné et affichable, suivi d'un espace.
*/

void		put_select_arg(void *elem)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		if (select->print && select->selec)
		{
			ft_putstr_fd(select->arg, 1);
			ft_putchar_fd(' ', 1);
		}
	}
}
