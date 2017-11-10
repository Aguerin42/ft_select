/**
**	\file	list.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de gestion de la liste _t_list_.
*/

#include "ft_select.h"

/**
**	\brief	Création de la liste d'argument
**
**	Crée une liste composée des arguments données en entrée de _ft_select_
**
**	\param	argc -	Nombre d'argument
**	\param	argv -	Tableau d'argument (incluant le nom de l'éxécutable
**
**	\return	La **liste** d'argument ou **NULL** en cas d'échec.
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
			struc->arg = ft_strdup(argv[argc]);
			(!list) ? list = ft_lstnew(struc, sizeof(struc))
				: ft_lstadd(&list, ft_lstnew(struc, sizeof(struc)));
			list ? set_all_member(list->content) : NULL;
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
	if (size)
	{
	}
}

/**
**	\brief	Obtention de la taille du plus grand argument de la liste.
**
**	La fonction parcours la liste et retourne la taille du plus grand
**	argument affichable.
*/

int		max_size_arg(t_list *list)
{
	int			size;
	int			max;
	t_select	*elem;

	max = 0;
	while (list)
	{
		if ((elem = (t_select*)list->content))
			if (elem->print && ((size = ft_strlen(elem->arg)) > max))
				max = size;
		list = list->next;
	}
	return (max);
}

/**
**	\brief	Fait appel à la fonction d'affichage de _arg_
**			de la structure *t_select* (put_tselect())
*/

void	print(t_list *elem)
{
	if (elem && elem->content)
		put_tselect((t_select*)elem->content);
}

/**
**	\brief	Change l'état de sélection d'un argument
*/

void	change_select_list(t_list *elem)
{
	if (elem && elem->content)
		select_change((t_select*)elem->content);
}

/**
**	\brief	Fait appel à la fonction de modification du flag d'affichage
**			de la structure *t_select* (set_print())
*/

void	set_print_list(t_list *elem)
{
	if (elem && elem->content)
		set_print((t_select*)elem->content);
}

/**
**	\brief	Fait appel à la fonction de modification du flag d'affichage
**			de la structure *t_select* (unset_print())
*/

void	unset_print_list(t_list *elem)
{
	if (elem && elem->content)
		unset_print((t_select*)elem->content);
}

/**
**	\brief	Fait appel à la fonction d'affichage d'un argument sans formatage
*/
void	put_select_arg_list(t_list *elem)
{
	if (elem && elem->content)
		put_select_arg(elem->content);
}

/**
**	\brief	Application de fonction conditionnelle.
**
**	Applique la fonction _t_ sur chaque maillon de la liste et,
**	si celle-ci renvoie _vrai_, applique la fonction _f_ sur les maillons.
*/

void	ft_lstiter_if(t_list *lst, void (*f)(t_select*), int (t)(t_select*))
{
	while (lst)
	{
		if (t((t_select*)lst->content))
			f((t_select*)lst->content);
		lst = lst->next;
	}
}
