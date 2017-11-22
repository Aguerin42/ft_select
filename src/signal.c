/**
**	\file	signal.c
**	\author	Alexis Guérin
**	\date	20 novembre 2017
**
**	\brief	Fonctions de gestion des signaux
*/

#include "ft_select.h"

static void				sig_msg(int signal)
{
	if (signal == SIGHUP)
		ft_putendl_fd("hangup ft_select", 2);
	else if (signal == SIGINT)
		ft_putendl_fd("ft_select", 2);
	else if (signal == SIGQUIT)
		ft_putendl_fd("quit ft_select", 2);
	else if (signal == SIGILL)
		ft_putendl_fd("illegal hardware instruction ft_select", 2);
	else if (signal == SIGABRT)
		ft_putendl_fd("abort ft_select", 2);
	else if (signal == SIGFPE)
		ft_putendl_fd("floating point exception ft_select", 2);
	else if (signal == SIGBUS)
		ft_putendl_fd("bus error ft_select", 2);
	else if (signal == SIGSEGV)
		ft_putendl_fd("segmentation violation ft_select", 2);
	else if (signal == SIGSYS)
		ft_putendl_fd("invalid system call ft_select", 2);
	else if (signal == SIGPIPE)
		ft_putendl_fd("ft_select", 2);
	else if (signal == SIGTERM)
		ft_putendl_fd("terminated ft_select", 2);
	else if (signal == SIGUSR1)
		ft_putendl_fd("user-defined signal 1 ft_select", 2);
	else if (signal == SIGUSR2)
		ft_putendl_fd("user-defined signal 2 ft_select", 2);
}

/**
**	\brief	Rétablissement de l'état du terminal après réception d'un signal
**
**	La fonction `quit()` remet le terminal dans son état initial
**	avant d'afficher un message d'erreur correspondant au signal reçu
**	puis de quitter
*/

void				quit(int signal)
{
	t_list	*list;

	term_default(1, NULL);
	list = get_list(0, NULL);
	ft_lstdel(&list, delete);
	sig_msg(signal);
	exit(1);
}

/**
**	\brief	Attrape le signal `SIGTSTP` ou `SIGWINCH`
*/
void				catch_signal(int sig)
{
	struct termios		g_dat = term_default(0, NULL);
	char				cp[2] = {g_dat.c_cc[VSUSP], 0};

	if (sig == SIGTSTP)
	{
		term_default(1, NULL);
		signal(SIGTSTP, SIG_DFL);
		ioctl(0, TIOCSTI, cp);
	}
	else if (sig == SIGCONT)
	{
		g_dat = set_term(term_default(0, NULL));
		set_term(term_default(0, NULL));
		if ((tcsetattr(0, TCSADRAIN, &g_dat)) == -1)
			error_termbehav();
		padding(get_list(0, NULL), window_size(1));
	}
	else if (sig == SIGWINCH)
		padding(get_list(0, NULL), window_size(1));
}
