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
**	get_term() récupère les informations du terminal `term`. S'il n'est pas
**	listé dans la base de données ou que celle-ci n'est pas disponible,
**	un message d'erreur correspondant est affiché (respectivement par
**	error_termdef() ou error_termbase()) et **-1** retourné.
**
**	\param	term -	Nom du terminal à chercher dans la base de données.
**
**	\return	**0** en cas de succès, **-1** en cas d'erreur.
*/

int				get_term(char *term)
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
**	`init` indique à la fonction si celle-ci doit faire appel à [ioctl][]
**	pour initialiser la structure _[winsize][]_ ou si elle doit seulement être
**	retournée.
**
**	\param	init -	**0** pour retourner simplement la structure
**					ou une valeur **non nulle** pour initialiser la structure et
**					la retourner.
**
**	[ioctl]: http://man7.org/linux/man-pages/man2/ioctl.2.html
**	[winsize]: http://www.delorie.com/djgpp/doc/libc/libc_495.html
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
**	_[termios][]_, le met en mode non canonique, désactive l'affichage des
**	touches tappées et l'affichage du curseur.
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
**
**	\param	default_term -	Structure sauvegardée du terminal par défaut,
**							à rétablir
*/

int				reset_term(struct termios default_term)
{
	ft_putstr_fd(tgetstr("te", NULL), 0);
	ft_putstr_fd(tgetstr("ve", NULL), 0);
	if ((tcsetattr(0, TCSADRAIN, &default_term)) == -1)
		return (error_termrestore());
	return (0);
}
