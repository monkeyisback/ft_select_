/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:18:48 by jgirard           #+#    #+#             */
/*   Updated: 2014/01/12 22:53:55 by jgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT
# define FT_SELECT
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <term.h>
# include <sys/ioctl.h>

typedef struct	s_env t_env;
typedef struct	s_arg t_arg;
typedef struct	termios t_term;

struct	s_env
{
	t_arg		*args_pivot;
	t_arg		*cursor_pos;
	char		*term_name;

	int			current_lines;
};

struct	s_arg
{
	char			*str;
	struct s_arg	*prev;
	struct s_arg	*next;

	int				screen_y;
	int				is_selected;

};

/*
** main.c
*/
void	print_term(t_env *e);

/*
** text.c
*/

size_t	ft_strlen(const char *str);
void	ft_putstr(const char *str);
void	ft_putstr_err(const char *str);
void	ft_error_exit(const char *str);
char	*ft_strdup(const char *str);

/*
** list.c
*/

int		get_elm_index(t_arg *pivot, t_arg *elm);
void	init_list(t_env *e);
void	add_node(t_env *e, char *str);
void	print_args(t_env *e);
int		sum_elements(t_arg *pivot);

/*
** singleton.c
*/

t_env	*ft_get_env(t_env *e);

/*
** signals.c
*/

void	sig_resize_window(int signum);
void	init_signals(t_env *e);

#endif /* !FT_SELECT */
