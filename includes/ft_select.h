/**
**	\file	ft_select.h
**	\author	Alexis Guérin
**	\date	8 novembre 2017
*/

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft.h"
# include <term.h>
# include <unistd.h>

/*
**	arg	- 		Argument donné à ft_select
**	cursor -	flag indiquant si le curseur est sur l'élément ou non
**	selec -		flag indiquant si l'élément est sélectionné ou non
**	print -		flag indiquant si l'élément doit être affiché ou non
*/

typedef struct	s_select
{
	char	*arg;
	int		cursor;
	int		selec;
	int		print;
}				t_select;

/**
**	error.c
*/

int				error_alloc(void);

/*
**	error_init.c
*/

int				error_usage(void);
int				error_noenv(void);
int				error_termvar(void);

/**
**	error_term.c
*/

int				error_termbase(void);
int				error_termdef(char *term);
int				error_termbehav(void);
int				error_termrestore(void);

/*
**	get_term.c
*/

int				get_term(char *term);
struct termios	set_term(struct termios term);
int				reset_term(struct termios term);

/*
**	launch.c
*/

int				launch(int argc, char **argv, char *term, struct termios save);

/*
**	list.c
*/

t_list			*fill_list(int argc, char **argv);
void			print(t_list *elem);
void			delete(void *elem, size_t size);
void			set_print_list(t_list *elem);
void			unset_print_list(t_list *elem);
void			ft_lstiter_if(t_list *lst, void (*f)(t_select *e),\
					int t(t_select *l));

/*
**	struct.c
*/

void			del_tselect(t_select **struc);
int				put_tselect(t_select *select);

/*
**	struct_is.c
*/

int				is_oncursor(t_select *elem);
int				is_printable(t_select *elem);
int				is_select(t_select *elem);

/*
**	struct_member.c
*/

void			set_print(t_select *elem);
void			unset_print(t_select *elem);
void			set_cursor(t_select *elem);
void			select_arg(t_select *elem);

#endif
