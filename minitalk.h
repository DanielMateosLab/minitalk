/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:43:13 by damateos          #+#    #+#             */
/*   Updated: 2024/07/10 20:56:02 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _GNU_SOURCE

# include "libft/include/libft.h"
# include <unistd.h>
# include <signal.h>

typedef struct s_message
{
	pid_t	sender;
	int		bit;
	int		pending;
}	t_message;

typedef struct s_buffer
{
	char	*ptr;
	int		len;
	int		si;
	int		bi;
}	t_buffer;

typedef struct s_c_state
{
	int		received;
	size_t	si;
	size_t	bi;
}	t_c_state;

int	bit_to_signal(size_t si, size_t bi, char *str);
char	*ft_expand_str(char *str, size_t len, size_t new_len);

#endif
