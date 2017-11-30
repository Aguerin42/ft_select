/**
**	\file	list.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de gestion de la liste `t_list`.
**
**	La liste de la **[Libft][]** est utilisée pour contenir les arguments donnés
**	à _ft_select_. Cette liste est composée de 3 champs :
**	- `void		*content`, qui permet de stocker une donnée
**	- `t_list	*next`, qui pointe vers l'élément suivant de la liste
**	- `t_list	*prev`, qui pointe vers l'élément précédent de la liste
**
**	Pour _ft_select_, `content` devra contenir une structure de type `t_select`
**	(`s_select`).
**
**	[Libft]: https://github.com/Aguerin42/libft
*/

#include "ft_select.h"

/*
**	\brief	Initialisation des champs de la structure `t_select`
*/

static void	set_all_member(t_select *elem)
{
	if (elem)
	{
		elem->cursor = 0;
		elem->selec = 0;
		elem->print = 1;
	}
}

/**
**	\brief	Renvoi des arguments sélectionnés
*/

void		print_select(t_list *list)
{
	t_select	*select;
	int			i;

	i = 0;
	while (list)
	{
		select = (t_select*)list->content;
		if (select && is_select(select))
		{
			(!i) ? i = 1 : ft_putchar(' ');
			ft_putstr_fd(select->arg, 0);
		}
		list = list->next;
	}
	if (i)
		ft_putendl_fd("", 0);
}

/**
**	\brief	Création de la liste d'argument
**
**	Crée une liste composée des arguments données en entrée de _ft_select_
**	La liste est statique, si celle-ci a déjà été créée elle est simplement
**	retournée par la fonction.
**
**	\param	argc -	Nombre d'argument
**	\param	argv -	Tableau d'argument (incluant le nom de l'éxécutable)
**
**	\return	La **liste** d'argument ou **NULL** en cas d'échec.
*/

t_list		*get_list(int argc, char **argv)
{
	static t_list	*list = NULL;
	t_select		*struc;

	if (argv && !list)
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
**	\brief	Fait appel à la fonction de suppression de la structure _t_select_
*/

void		delete(void *elem, size_t size)
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
**	\brief	Obtention de la taille du plus grand argument de la liste.
**
**	La fonction parcourt la liste et retourne la taille du plus grand
**	argument affichable.
*/

int			max_size_arg(t_list *list)
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
