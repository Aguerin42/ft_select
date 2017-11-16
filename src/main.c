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

void	msg(int t)
{
	if (t)
		;
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
	ft_putendl("TRUC");
}

static void				catch_signal(int signal)
{
	t_list				*list;
	struct sigaction	action;
	
	if (signal == SIGINT)
	{
		term_default(1, NULL);
		list = get_list(0, NULL);
		ft_lstdel(&list, delete);
		exit(1);
	}
	else if (signal == SIGTSTP)
	{
		action.sa_handler = msg;
		action.sa_flags = 0;
		term_default(1, NULL);
		sigaction(SIGTSTP, &action, NULL);
	}
	else if (signal == SIGWINCH)
	{
		list = get_list(0, NULL);
		padding(list, window_size(1));
	}
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
