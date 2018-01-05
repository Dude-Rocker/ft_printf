/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prfoper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 19:32:34 by vgladush          #+#    #+#             */
/*   Updated: 2018/01/05 11:32:05 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	strendf(char s, int *i)
{
	if (!s && i[13] != 1)
		*i -= 1;
	else if ((i[1] += 1))
	{
		if (i[3] == 2)
		{
			write(1, &s, 1);
			while ((i[10] -= 1) > 0)
				i[1] += write(1, " ", 1);
		}
		else if (i[3] == 1)
		{
			while ((i[10] -= 1) > 0)
				i[1] += write(1, "0", 1);
			write(1, &s, 1);
		}
		else
		{
			while ((i[10] -= 1) > 0)
				i[1] += write(1, " ", 1);
			if (s || (i[1] -= 1) == -2)
				write(1, &s, 1);
		}
	}
}

static	void	outstr(char *s, int *i)
{
	char		*res;
	int			j;

	j = -1;
	if (i[11] == -1 || i[11] > (int)ft_strlen(s))
		res = ft_strdup(s);
	else
	{
		if (!(res = (char *)malloc(sizeof(char) * i[11] + 1)))
			return ;
		res[i[11]] = '\0';
		while (++j < i[11])
			res[j] = s[j];
	}
	i[10] -= (int)ft_strlen(res) - 1;
	if (i[3] != 2 && (i[13] = 1))
		strendf(res[0], i);
	if (res[i[13]])
		i[1] += write(1, &res[i[13]], ft_strlen(&res[i[13]]));
	while ((i[10] -= 1) > 0)
		i[1] += write(1, " ", 1);
	free(res);
}

static	void	prfstr(char s, va_list *ar, int *i)
{
	char		*un;
	char		c;

	un = 0;
	if (i[7] || s == 'S')
	{
		if (s == 'c' || s == 'C')
			if (!(un = unicd(va_arg(*ar, int))))
				un = ft_strdup("");
		if (s == 's' || s == 'S')
			if (!(un = unistr(va_arg(*ar, wchar_t *))))
				un = ft_strdup("(null)");
		outstr(un, i);
		free(un);
	}
	else
	{
		if ((s == 'c' || s == 'C') && (c = va_arg(*ar, int)))
			strendf(c, i);
		else
			outstr(va_arg(*ar, char *), i);
	}
}

void			ft_prfoper(char *s, va_list *ar, int *i)
{
	char		*str;

	str = NULL;
	if (OPER(s[*i]) && OPE2(s[*i]) && OPE3(s[*i]))
		strendf(s[*i], i);
	else if (s[*i] == 'n')
	{
		if (i[8] != 2 && i[8] != 1)
			*va_arg(*ar, unsigned int *) = i[1];
		else if (i[8] == 2)
			*va_arg(*ar, int *) = (unsigned short int)i[1];
		else if (i[8] == 1)
			*va_arg(*ar, int *) = (unsigned char)i[1];
	}
	else if (DEVAL(s[*i]) || DEVA2(s[*i]))
		ft_prfnbr(s[*i], i, ar, str);
	else if (s[*i] == 'c' || s[*i] == 'C' || s[*i] == 's' || s[*i] == 'S')
		prfstr(s[*i], ar, i);
	else
		ft_prfdbl(s[*i], i, ar);
}
