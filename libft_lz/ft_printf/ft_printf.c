/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzito <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:58:58 by lzito             #+#    #+#             */
/*   Updated: 2022/12/03 18:25:51 by lzito            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_check_conversion(const char *format, int *count, int i, va_list args)
{
	if (format[i] == 'c')
		*count += ft_putchar((char)va_arg(args, int));
	else if (format[i] == 's')
		*count += ft_putstr(va_arg(args, char *));
	else if (format[i] == 'p')
	{
		*count += ft_putstr("0x");
		*count += ft_put_p(va_arg(args, uintptr_t));
	}
	else if (format[i] == 'd' || format[i] == 'i')
		*count += ft_putnbr(va_arg(args, int));
	else if (format[i] == 'u')
		*count += ft_putnbr_u(va_arg(args, unsigned int));
	else if (format[i] == 'x')
		*count += ft_putnbr_16(va_arg(args, unsigned int), format[i]);
	else if (format[i] == 'X')
		*count += ft_putnbr_16(va_arg(args, unsigned int), format[i]);
	else if (format[i] == '%')
		*count += write(1, "%", 1);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		i;
	va_list	args;

	count = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			ft_check_conversion(format, &count, i + 1, args);
			i++;
		}	
		else
			count += write(1, &format[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
