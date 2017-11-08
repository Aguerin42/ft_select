/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Entrée du programme et vérification des paramètres donnés.
*/

#include "ft_select.h"
#include <stdlib.h>

/**
**	\brief	Entrée du programme
**
**	main() vérifie que *ft_select* reçoit bien au moins un argument
**	à son lancement, que l'environnement qui lui est donné n'est pas vide
**	et que celui-ci contient bien une variable TERM initialisée.
**	
**	Si aucune erreur n'est rencontrée, les informations du terminal
**	sont récupérées et stockées dans une structure _termios_.
**	
**	Sinon le programme quitte en affichant un message d'erreur (respectivement
**	error_usage(), error_noenv() ou error_termvar()).
*/

int	main(int argc, char **argv, char **env)
{
	int				ret;
	char			*term;
	struct termios	term_save;

	if (argc == 1)
		return (error_usage());
	if (!(*env))
		return (error_noenv());
	if (!(term = getenv("TERM")) || !term[0])
		return (error_termvar());
	tcgetattr(0, &term_save);
	ret = launch(argc, argv, term, term_save);
	if ((tcsetattr(0, TCSADRAIN, &term_save)) == -1)
		return (error_termrestore());
	return (ret);
}
