/**
**	\file	error_term.c
**	\author	Alexis Guérin
**	\date	8 novembre 2017
**
**	\brief	Messages d'erreurs en cas de problèmes avec la gestion
**			des informations du terminal.
**
**	Chacune de ces fonctions renvoie **-1**.
*/

#include "ft_select.h"

/**
**	\brief	Le terminal `term` n'est pas dans la base de données.
*/

int	error_termdef(char *term)
{
	print_message("ft_select: Terminal type ", 2);
	print_message(term, 2);
	print_message(" is not defined. Exit.", 2);
	return (-1);
}

/**
**	\brief	La base de données est introuvable.
*/

int	error_termbase(void)
{
	print_message(
			"ft_select: Could not access the termcap data base. Exit.", 2);
	return (-1);
}

/**
**	\brief	Échec de la modification du comportement du terminal.
*/

int	error_termbehav(void)
{
	print_message("ft_select: Error modifying terminal behavior", 2);
	return (-1);
}

/**
**	\brief	Échec de la restauration du comportement du terminal.
*/

int	error_termrestore(void)
{
	print_message("ft_select: Error restoring initial behavior", 2);
	return (-1);
}
