/**
**	\file	launch.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Récupération et vérification des informations du terminal
**			et création de la liste d'arguments donnés à _ft_select_.
*/

#include "ft_select.h"

static void	fill_char_tab(char tabl[], size_t size, char val)
{
	size_t	i;

	i = 0;
	while (i < size)
		tabl[i++] = val;
}

static int	touch(char buffer[])
{
	if (buffer[0] == 27 && !buffer[1] && !buffer[2])
		return (-1);
	return (0);
}

/**
**	\brief	Application des modifications du comportement
**
**	ft_select() applique les modifications du comportement au terminal
**	et attend l'entrée utilisateur.
*/

static int	ft_select(t_list *list, struct termios term)
{
	char	buffer[6];

	if (list)
	{
		if ((tcsetattr(0, TCSADRAIN, &term)) == -1)
			return (error_termbehav());
		while (touch(buffer) >= 0)
		{
			fill_char_tab(buffer, 6, 0);
			read(0, buffer, 6);
			ft_lstiter(list, print);
		}
		return (0);
	}
	return (-1);
}

/**
**	\brief	Lancement de *ft_select*
**
**	launch() est appelée depuis le main()
**	et fait appel aux différentes fonctions de copies des arguments,
**	d'initialisation de la structure *t_select* et de vérification du terminal.
**
**	\param	argc -	Nombre d'argument
**	\param	argv -  Tableau d'arguments (incluant le nom de l'exécutable)
**	\param	term -	Nom du terminal
**	\param	save -	Informations sur le terminal
**
**	\return	**1** en cas d'erreur, **0** sinon.
*/

int	launch(int argc, char **argv, char *term, struct termios save)
{
	int				ret;
	t_list			*list;
	struct termios	term_t;

	ret = -1;
	if (argv && term)
	{
		if (get_term(term))
			return (-1);
		term_t = set_term(save);
		if (!(list = fill_list(argc, argv)))
			return (error_alloc());
		ft_lstiter(list, set_print_list);
		set_cursor((t_select*)list->content);
		ret = ft_select(list, term_t);
		if (list)
			ft_lstdel(&list, delete);
	}
	return (ret);
}
