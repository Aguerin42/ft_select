/**
**	\file	launch.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Récupération et vérification des informations du terminal
**			et création de la liste d'arguments donnés à _ft_select_.
*/

#include "ft_select.h"

/*
**	\brief	Initialisation des cases d'un tableau
*/

static void	fill_char_tab(char tabl[], size_t size, char val)
{
	size_t	i;

	i = 0;
	while (i < size)
		tabl[i++] = val;
}

/**
**	\brief	Application des modifications du comportement
**
**	ft_select() applique les modifications du comportement au terminal
**	et attend l'entrée utilisateur.
*/

static int	ft_select(t_list *list, struct termios term)
{
	int				direction;
	char			buffer[6];

	if (list)
	{
		direction = 1;
		ft_putstr_fd(tgetstr("ti", NULL), 0);
		ft_putstr_fd(tgoto(tgetstr("cm", NULL), 0, 0), 0);
		if ((tcsetattr(0, TCSADRAIN, &term)) == -1)
			return (error_termbehav());
		window_size(1);
		fill_char_tab(buffer, 6, 0);
		while (key(buffer, list, &direction, window_size(0)) >= 0)
		{
			padding(list, window_size(0));
			fill_char_tab(buffer, 6, 0);
			read(0, buffer, 6);
		}
		return (0);
	}
	return (-1);
}

/**
**	\brief	Lancement de *ft_select*
**
**	launch() est appelée depuis le main()
**	et fait appel aux différentes fonctions de copie des arguments,
**	d'initialisation de la structure `t_select` et de vérification du terminal.
**
**	\param	argc -	Nombre d'argument
**	\param	argv -  Tableau d'arguments (incluant le nom de l'exécutable)
**	\param	term -	Nom du terminal
**	\param	save -	Informations sur le terminal
**
**	\return	**1** en cas d'erreur, **0** sinon.
*/

int			launch(int argc, char **argv, char *term, struct termios save)
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
		if (!(list = get_list(argc, argv)))
			return (error_alloc());
		set_cursor(list->content);
		ret = ft_select(list, term_t);
	}
	return (ret);
}
