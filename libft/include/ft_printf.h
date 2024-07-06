/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damateos <damateos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 18:36:39 by damateos          #+#    #+#             */
/*   Updated: 2024/05/17 18:08:53 by damateos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>

int	ft_printf(char const *format_str, ...);
int	pf_putunbr(unsigned int n);
int	pf_puthex(uintptr_t n, int is_upper);
int	pf_putptr(void *ptr);
int	pf_putchar(char c);
int	pf_putstr(char *s);
int	pf_putnbr(int n);
int	check_err(int res, int *err);

#endif
