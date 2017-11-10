/**
**	\file	get_term.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Fonctions de récupération et de vérification des informations
**			du terminal.
*/

#include "ft_select.h"

/**
**	\brief	Récupération des informations du terminal.
**
**	get_term() récupère les informations du terminal _term_. S'il n'est pas
**	listé dans la base de données ou que celle-ci n'est pas disponible,
**	un message d'erreur correspondant (respectivement par error_termdef()
**	ou error_termbase()) est affiché et **-1** retourné.
**
**	\param	term -	Nom du terminal à chercher dans la base de données.
**
**	\return	**0** en cas de succès, **-1** si la variable _term_ est NULL,
**			que la base données est introuvable ou que le terminal
**			n'y est pas listé.
*/

int	get_term(char *term)
{
	int		ret;

	if (term)
	{
		ret = tgetent(NULL, term);
		if (!ret)
			return (error_termdef(term));
		if (ret < 0)
			return (error_termbase());
	}
	return (term ? 0 : -1);
}

/**
**	\brief	Obtention des dimensions de la fenêtre.
**
**	window_size() récupère les dimensions de la fenêtre.
**
**	_init_ indique à la fonction si celle-ci doit faire appelle à [ioctl][]
**	pour initialiser la structure _winsize_ ou si elle doit seulement être retournée.
**
**	\param	init -	**0** pour retourner simplement la structure
**					ou **non nul** pour initialiser la structure et la retourner.
**
**	[ioctl]: http://man7.org/linux/man-pages/man2/ioctl.2.html
*/

struct winsize	window_size(int init)
{
	static struct winsize	size;

	if (init)
		if (ioctl(0, TIOCGWINSZ, &size) == -1)
			error_winsize();
	return (size);
}

/**
**	\brief	Modification de la structure _termios_.
**
**	set_term() copie les informations du terminal dans une nouvelle structure
**	_[termios][]_, le met en mode non canonique, désactive l'affichage des touches
**	tappées et l'affichage du curseur.
**
**	\param	term -	Structure du terminal de référence.
**
**	\return	Structure du terminal modifiée.
**
**	[termios]: https://linux.die.net/man/3/termios
*/

struct termios	set_term(struct termios term)
{
	struct termios	new;

	new = term;
	new.c_lflag &= ~(ICANON);
	new.c_lflag &= ~(ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	ft_putstr_fd(tgetstr("vi", NULL), 0);
	return (new);
}

/**
**	\brief	Restauration du terminal par défaut.
*/

int	reset_term(struct termios default_term)
{
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	if ((tcsetattr(0, TCSADRAIN, &default_term)) == -1)
		return (error_termrestore());
	return (0);
}
