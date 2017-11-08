/**
**	\file	ft_select.h
**	\author	Alexis Guérin
**	\date	8 novembre 2017
*/

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <termios.h>

typedef struct	s_select
{
	char	*arg;
	int		cursor;
	int		selec;
	int		print;
}				t_select;

/*
** error_init.c
*/

int				error_usage(void);
int				error_noenv(void);
int				error_termvar(void);

/*
** launch.c
*/

int				launch(int argc, char **argv, char *term);

/*
** list.c
*/

t_list			*fill_list(int argc, char **argv);
void			print(t_list *elem);
void			delete(void *elem, size_t size);

/*
** struct.c
*/

t_select		*new_tselect(char *arg);
void			del_tselect(t_select **struc);
int				put_tselect(t_select *select);

#endif
