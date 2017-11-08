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
**	launch() fait appel aux différentes fonctions de copies des arguments,
**	d'initialisation de la structure *t_select* et de vérification du terminal.
**
**	\param	argc -	Nombre d'argument
**	\param	argv -  Tableau d'arguments (incluant le nom de l'exécutable)
**	\param	term -	Nom du terminal
**
**	\return	**1** en cas d'erreur, **0** sinon
*/

int				launch(int argc, char **argv, char *term)
{
	t_list			*list;

	if (argv && term)
	{
		list = fill_list(argc, argv);
		ft_lstiter(list, print);
		ft_lstdel(&list, delete);
	}
	return (0);
}
