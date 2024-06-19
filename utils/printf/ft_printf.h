/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kosnakam <kosnakam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:04:27 by kosnakam          #+#    #+#             */
/*   Updated: 2024/04/16 12:15:37 by kosnakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <inttypes.h>

int		ft_hex_len(unsigned	long long num);
int		ft_printf(const char *format, ...);
int		ft_print_str(char *str);
int		ft_print_hex(unsigned long long num, const char format);
int		ft_print_ptr(unsigned long long ptr);
int		ft_print_unsigned(unsigned int n);
int		pt_ft_putchar_fd(char c, int fd);
int		ft_put_nbr(int n);
int		ft_put_str(char *str);
void	ft_put_hex(unsigned long long num, const char format);

#endif
