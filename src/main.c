/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Entrée du programme et vérification des paramètres donnés.
*/

#include "ft_select.h"

/*
**	Obtention du comportement par défaut ou rétablissement de celui-ci
*/

static struct termios	term_default(int set_default, int *ret)
{
	static struct termios	term_default;

	if (!set_default)
	{
		if (tcgetattr(0, &term_default) == -1)
		{
			error_termbehav();
			ret ? ret += -1 : ret;
		}
	}
	else
		reset_term(term_default);
	return (term_default);
}

static void				catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		term_default(1, NULL);
		exit(1);
	}
	else if (signal == SIGTSTP)
	{
		ft_putendl_fd("Ctrl-z", 0);
		exit(0);
	}
	else if (signal == SIGWINCH)
		window_size(1);
	ft_putnbrl(signal);
}

static void				sig(void)
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

int						main(int argc, char **argv, char **env)
{
	int				ret;
	char			*term;

	ret = 0;
	sig();
	if (argc == 1)
		return (error_usage());
	if (!(*env))
		return (error_noenv());
	if (!(term = getenv("TERM")) || !term[0])
		return (error_termvar());
	ret += launch(argc, argv, term, term_default(0, &ret));
	term_default(1, &ret);
	return (ret);
}
