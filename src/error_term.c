/**
**	\file	error_term.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Erreurs à afficher en cas de problèmes avec la gestion
**			des informations du terminal.
**
**	Chacune de ces fonctions renvoie **-1**.
*/

#include "ft_select.h"

/**
**	\brief	Message d'erreur si le terminal _term_
**			n'est pas dans la base de données.
*/

int	error_termdef(char *term)
{
	ft_putstr_fd("ft_select: Terminal type ", 2);
	ft_putstr_fd(term, 2);
	ft_putendl_fd(" is not defined. Exit.", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur si la base de données est introuvable.
*/

int	error_termbase(void)
{
	ft_putendl_fd("ft_select: Could not access the termcap data base. Exit.", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur si la modification du comportement
**			du terminal échoue.
*/

int	error_termbehav(void)
{
	ft_putendl_fd("ft_select: Error modifying terminal behavior", 2);
	return (-1);
}

/**
**	\brief	Message d'erreur si la restauration du comportement
**			du terminal échoue.
*/

int	error_termrestore(void)
{
	ft_putendl_fd("ft_select: Error restoring initial behavior", 2);
	return (-1);
}