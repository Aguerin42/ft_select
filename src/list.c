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

/**
**	\brief	Création de la liste d'argument
**
**	Crée une liste composée des arguments données en entrée de _ft_select_
**	La liste est statique, si celle-ci a déjà été créée elle est simplement
**	retournée par la fonction.
**
**	\param	argc -	Nombre d'argument
**	\param	argv -	Tableau d'argument (incluant le nom de l'éxécutable
**
**	\return	La **liste** d'argument ou **NULL** en cas d'échec.
*/

t_list	*get_list(int argc, char **argv)
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
**	\brief	Fait appel à la fonction d'affichage de _arg_ de la structure
**			`t_select` (put_tselect())
*/

void	print(t_list *elem)
{
	if (elem && elem->content)
		put_tselect((t_select*)elem->content);
}

/**
**	\brief	Application de fonction conditionnelle.
**
**	Applique la fonction `t` sur chaque maillon de la liste et,
**	si celle-ci renvoie _vrai_, applique la fonction `f` sur les maillons.
*/

void	ft_lstiter_if(t_list *lst, void (*f)(void*), int (t)(void*))
{
	while (lst)
	{
		if (t(lst->content))
			f(lst->content);
		lst = lst->next;
	}
}
