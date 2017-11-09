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
**			que le la base données est introuvable ou que le terminal
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
**	\brief	Modification de la structure termios.
**
**	set_term() copie les informations du terminal dans une nouvelle structure
**	_termios_, le met en mode non canonique, désactive l'affichage des touches
**	tappées et l'affichage du curseur.
**
**	\param	term -	Structure du terminal de référence.
**
**	\return	Structure du terminal modifiée.
*/

struct termios	set_term(struct termios term)
{
	struct termios	new;

	new = term;
	new.c_lflag &= ~(ICANON);
	new.c_lflag &= ~(ECHO);
	new.c_cc[VMIN] = 1;
	new.c_cc[VTIME] = 0;
	ft_putstr(tgetstr("vi", NULL));
	ft_putstr(tgetstr("ti", NULL));
	return (new);
}

/**
**	\brief	Restauration du terminal par défaut.
*/

int	reset_term(struct termios term)
{
	ft_putstr(tgetstr("vs", NULL));
	if ((tcsetattr(0, TCSADRAIN, &term)) == -1)
		return (error_termrestore());
	return (0);
}
