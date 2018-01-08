/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 18:37:09 by vgladush          #+#    #+#             */
/*   Updated: 2018/01/08 17:27:54 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
// #include <stdio.h>
#include "libft.h"
#include <locale.h>
#include <limits.h>

int main()
{
	setlocale(LC_ALL, "");
	int j = 500;
	char c = j;

	// int i;
	// long long j;
	
	// j = 8745;
	// i = -14;

	printf("{%05p}\n", 0);
	ft_printf("{%05p}", 0);
	// printf("%0#*.*f\n", 10, 5, 3.1455555528);
	// ft_printf("%0#*.*f\n", 10, 5, 3.1455555528);
	// printf("coun or == %d\n", printf("%5%orig == %e\n", 9108461.505275574));
	// printf("coun my == %d\n", ft_printf("%5%mine == %e\n", 9108461.505275574));
	return (0);
}
