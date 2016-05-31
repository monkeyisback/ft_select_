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

typedef struct	s_env t_env;
typedef struct	s_arg t_arg;
typedef struct	termios t_term;

struct	s_env
{
	t_arg		*args_pivot;
	char		*term_name;
	t_term		term;
	t_term		term_save;

	int			term_size_c;
	int			term_size_l;
};

struct	s_arg
{
	char			*str;
	struct s_arg	*prev;
	struct s_arg	*next;
	int				pos_word_l;
	int				pos_word_begin_c;
	int				pos_word_end_c;
};

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

void	init_list(t_env *e);
void	add_node(t_env *e, char *str);
void	print_args(t_env *e);

#endif /* !FT_SELECT */
