/**
**	\file	main.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Entrée du programme et vérification des paramètres donnés.
*/

#include "ft_select.h"

/**
**	\brief	Obtention du comportement par défaut ou rétablissement de celui-ci
**
**	\param	set_default -	**0** pour obtenir les informations du terminal,
**							ou une valeur **non nulle** pour rétablir
**							le terminal par défaut.
**	\param	ret -			est mis à une valeur **non nulle** en cas d'erreur
**							ou laissé à sa valeur initiale sinon.
*/

struct termios	term_default(int set_default, int *ret)
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

static void		sig(void)
{
	signal(SIGHUP, quit);
	signal(SIGINT, quit);
	signal(SIGQUIT, quit);
	signal(SIGILL, quit);
	signal(SIGTRAP, quit);
	signal(SIGABRT, quit);
	signal(SIGFPE, quit);
	signal(SIGBUS, quit);
	signal(SIGSEGV, quit);
	signal(SIGSYS, quit);
	signal(SIGPIPE, quit);
	signal(SIGALRM, quit);
	signal(SIGTERM, quit);
	signal(SIGTTOU, quit);
	signal(SIGXCPU, quit);
	signal(SIGXFSZ, quit);
	signal(SIGVTALRM, quit);
	signal(SIGPROF, quit);
	signal(SIGUSR1, quit);
	signal(SIGUSR2, quit);
	signal(SIGTSTP, catch_signal);
	signal(SIGWINCH, catch_signal);
	signal(SIGCONT, catch_signal);
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

int				main(int argc, char **argv, char **env)
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
	quit(0);
	return (ret);
}
