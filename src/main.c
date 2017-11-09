/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Entrée du programme et vérification des paramètres donnés.
*/

#include "ft_select.h"

void	term_default(int set_default)
{
	static struct termios	term_default;

	if (!set_default)
		tcgetattr(0, &term_default);
	else
		reset_term(term_default);
}

void	catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		term_default(1);
		exit(1);
	}
	else if (signal == SIGTSTP)
	{
		ft_putendl("Ctrl-z");
		exit(0);
	}
	else if (signal == SIGWINCH)
		ft_putendl("resize");
	ft_putnbrl(signal);
}

void	sig(void)
{
	signal(SIGINT, catch_signal);
	signal(SIGTSTP, catch_signal);
	signal(SIGWINCH, catch_signal);
}


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

int			main(int argc, char **argv, char **env)
{
	int				ret;
	char			*term;
	struct termios	term_save;

	sig();
	if (argc == 1)
		return (error_usage());
	if (!(*env))
		return (error_noenv());
	if (!(term = getenv("TERM")) || !term[0])
		return (error_termvar());
	term_default(0);
	tcgetattr(0, &term_save);
	ret = launch(argc, argv, term, term_save);
	ret += reset_term(term_save);
	return (ret);
}
