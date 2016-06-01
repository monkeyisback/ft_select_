/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard <jgirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/12 22:18:31 by jgirard           #+#    #+#             */
/*   Updated: 2014/01/12 22:56:10 by jgirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	sig_resize_window(int signum)
{
	print_term(ft_get_env(NULL));
}

void	init_signals(t_env *e)
{
	signal(SIGWINCH, &sig_resize_window);
}