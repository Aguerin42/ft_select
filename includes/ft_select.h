/**
**	\file	ft_select.h
**	\author	Alexis Guérin
**	\date	8 novembre 2017
*/

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"

typedef struct	s_select
{
	char	*arg;
	int		cursor;
	int		selec;
	int		print;
}				t_select;

int				error_usage(void);
int				error_noenv(void);
int				error_termvar(void);

#endif
