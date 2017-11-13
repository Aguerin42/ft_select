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

static int	key(char buffer[], t_list *list)
{
	if (!list)
		return (-1);
	if (buffer[0] == 27 && !buffer[1] && !buffer[2])
		return (-1);
	if (buffer[0] == 127 && !buffer[1] && !buffer[2])
	{
		ft_lstiter_if(list, unset_print, is_oncursor);
		if (!ft_lstany(list, is_printable))
			return (-1);
	}
	else if (buffer[0] == 27 && buffer[1] == 91)
	{
		if (buffer[2] == 68)
			find_previous(list);
		else if (buffer[2] == 67)
			find_next(list);
		else if (buffer[2] == 65)
			ft_putstr_fd("haut", 0);
		else if (buffer[2] == 66)
			ft_putstr_fd("bas", 0);
	}		
	else if (buffer[0] == 10 && !buffer[1] && !buffer[2])
	{
		ft_lstiter(list, put_select_arg_list);
		return (-1);
	}
	else if (buffer[0] == 32 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, select_change, is_oncursor);
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
	int				max_size;
	char			buffer[6];
	struct winsize	size;

	if (list)
	{
		ft_putstr_fd(tgoto(tgetstr("cm", NULL),  0, 0), 0);
		if ((tcsetattr(0, TCSADRAIN, &term)) == -1)
			return (error_termbehav());
		size = window_size(1);
		while (key(buffer, list) >= 0)
		{
			ft_putstr_fd(tgetstr("ti", NULL), 0);
			ft_putstr_fd(tgoto(tgetstr("cm", NULL),  0, 0), 0);
			ft_lstiter(list, print);
			size = window_size(0);
			max_size = max_size_arg(list);
			if (max_size > size.ws_col)
				ft_putendl_fd("small window...", 2);
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
		set_cursor((t_select*)list->content);
		ret = ft_select(list, term_t);
		if (list)
			ft_lstdel(&list, delete);
	}
	return (ret);
}
