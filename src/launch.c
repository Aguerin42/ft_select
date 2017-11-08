/**
**	\file	launch.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Récupération et vérification des informations du terminal
**			et création de la liste d'arguments donnés à _ft_select_.
*/

#include "ft_select.h"

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
		if ((tcsetattr(0, TCSADRAIN, &term_t)) == -1)
			ret = error_termbehav();
		else
			ret = 0;
		if (list)
			ft_lstdel(&list, delete);
	}
	return (ret);
}
