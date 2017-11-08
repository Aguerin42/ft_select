/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
*/

#include "ft_select.h"
#include <stdlib.h>

/**
**	\brief	Entrée du programme
**
**	main() vérifie que *ft_select* reçoit bien au moins un argument
**	à son lancement, que l'environnement qui lui est donné n'est pas vide
**	et que celui-ci contient bien une variable TERM initialisée.
*/

int	main(int argc, char **argv, char **env)
{
	char	*term;

	if (argc == 1)
		return (error_usage());
	if (!(*env))
		return (error_noenv());
	if (!(term = getenv("TERM")) || !term[0])
		return (error_termvar());
	launch(argc, argv, term);
	return (0);
}
