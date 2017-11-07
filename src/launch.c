/**
**	\file	launch.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
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

int	launch(int argc, char **argv, char *term)
{
	t_select	*struc;

	if (argv && term)
	{
		if (argc)
		{
			if ((struc = new_tselect("salut")))
				ft_putendl("ok");
			del_tselect(&struc);
			if (!struc)
				ft_putendl("ok");
		}
	}
	return (0);
}
