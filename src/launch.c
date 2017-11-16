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

/*
** 	Direction : sens de direction du précédent déplacement.
**	0 : gauche
**	1 : droite
*/

static int	key(char buffer[], t_list *list, int *direction, struct winsize win)
{
	if (!list)
		return (-1);
	if (buffer[0] == 27 && !buffer[1] && !buffer[2])
		return (-1);
	if ((buffer[0] == 127 && !buffer[1] && !buffer[2]) ||
		(buffer[0] == 27 && buffer[1] == 91 && buffer[2] == 51
		 && buffer[3] == 126 && !buffer[4] && !buffer[5]))
	{
		ft_lstiter_if(list, unset_print, is_oncursor);
		*direction ? move_right(list) : move_left(list);
		if (!ft_lstany(list, is_printable))
			return (-1);
	}
	else if (buffer[0] == 27 && buffer[1] == 91)
	{
		if (buffer[2] == 68 || buffer[2] == 90)
			*direction = move_left(list);
		else if (buffer[2] == 67)
			*direction = move_right(list);
		else if (buffer[2] == 65)
			move_up(list, win);
		else if (buffer[2] == 66)
			move_down(list, win);
		else if (buffer[2] == 72)
			move_first(list);
		else if (buffer[2] == 70)
			move_last(list);
	}
	else if (buffer[0] == 9 && !buffer[1] && !buffer[2])
		*direction = move_right(list);
	else if (buffer[0] == 10 && !buffer[1] && !buffer[2])
	{
		ft_putstr_fd(tgetstr("cl", NULL), 0);
		ft_lstiter_if(list, put_select_arg, is_select);
		ft_putendl_fd("", 0);
		return (-1);
	}
	else if (buffer[0] == 32 && !buffer[1] && !buffer[2])
	{
		ft_lstiter_if(list, select_change, is_oncursor);
		if (*direction == 0)
			move_left(list);
		else
			move_right(list);
	}
	else if (buffer[0] == 65 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, select_arg, is_printable);
	else if (buffer[0] == 68 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, unselect_arg, is_printable);
	else if (buffer[0] == 90 && !buffer[1] && !buffer[2])
		ft_lstiter_if(list, select_change, is_printable);
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
	int				direction;
	char			buffer[6];

	if (list)
	{
		direction = 1;
		ft_putstr_fd(tgetstr("cl", NULL), 0);
		ft_putstr_fd(tgoto(tgetstr("cm", NULL),  0, 0), 0);
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
		if (!(list = get_list(argc, argv)))
			return (error_alloc());
		set_cursor((t_select*)list->content);
		ret = ft_select(list, term_t);
		if (list)
			ft_lstdel(&list, delete);
	}
	return (ret);
}
