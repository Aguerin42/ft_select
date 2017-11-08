/**
**	\file	list.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de gestion de la liste _t_list_.
*/

#include "ft_select.h"

/**
**	\brief	Création de la liste d'arguments
**
**	Crée une liste composée des arguments données en entrée de _ft_select_
**
**	\param	argc -	Nombre d'argument
**	\param	argv -	Tableau d'arguments (incluant le nom de l'éxécutable)
**
**	\return	La **liste** d'arguments ou **NULL** en cas d'échec.
*/

t_list	*fill_list(int argc, char **argv)
{
	t_select	*struc;
	t_list		*list;

	list = NULL;
	if (argv)
	{
		struc = (t_select*)ft_memalloc(sizeof(t_select));
		while (--argc > 0)
		{
			if (!(struc->arg = ft_strdup(argv[argc])))
				ft_putendl_fd("ft_select: allocation error.", 2);
			(!list) ? list = ft_lstnew(struc, sizeof(struc)) :
							ft_lstadd(&list, ft_lstnew(struc, sizeof(struc)));
		}
		struc ? ft_memdel((void**)&struc) : NULL;
	}
	return (list);
}

/**
**	\brief	Fait appel à la fonction de suppression
**			de la structure _t_select_
*/

void	delete(void *elem, size_t size)
{
	t_select	*select;

	if (elem)
	{
		select = (t_select*)elem;
		del_tselect(&select);
	}
	(void)size;
}

/**
** \brief	Fait appel à la fonction d'affichage de _arg_
**			de la structure *t_select*
*/

void	print(t_list *elem)
{
	if (elem && elem->content)
		put_tselect((t_select*)elem->content);
}
