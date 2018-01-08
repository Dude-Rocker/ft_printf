/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prfoper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgladush <vgladush@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/29 16:50:45 by vgladush          #+#    #+#             */
/*   Updated: 2018/01/08 17:46:57 by vgladush         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	strendf(char s, int *i)
{
	if (!s && i[13] != 1 && i[8] != 9)
		*i -= 1;
	else
	{
		if (i[3] == 2)
		{
			if (s)
				i[1] += write(1, &s, 1);
			else
				i[1] += write(1, "\0", 1);
			while ((i[10] -= 1) > 0)
				i[1] += write(1, " ", 1);
		}
		else
		{
			while (i[3] == 1 && (i[10] -= 1) > 0)
				i[1] += write(1, "0", 1);
			while (!i[3] && (i[10] -= 1) > 0)
				i[1] += write(1, " ", 1);
			if (s)
				i[1] += write(1, &s, 1);
			else if (i[8] == 9)
				i[1] += write(1, "\0", 1);
		}
	}
}

static	char	*outstr(char *s, int *i)
{
	char		*res;
	int			j;

	j = -1;
	if (!s && i[8] != 9)
		res = ft_strdup("(null)");
	else if (i[11] == -1 || i[11] > (int)ft_strlen(s))
		res = ft_strdup(s);
	else
	{
		if (!(res = (char *)malloc(sizeof(char) * i[11] + 1)))
			return (0);
		res[i[11]] = '\0';
		while (++j < i[11])
			res[j] = s[j];
	}
	i[10] -= (int)ft_strlen(res) - 1;
	if ((i[3] != 2 && (i[13] = 1)) || i[8] == 9)
		strendf(res[0], i);
	if (res[i[13]] && res[0])
		i[1] += write(1, &res[i[13]], ft_strlen(&res[i[13]]));
	while ((i[10] -= 1) > 0)
		i[1] += write(1, " ", 1);
	free(res);
	return (s);
}

static	void	prfstr(char s, va_list *ar, int *i)
{
	char		*un;
	char		c;

	un = 0;
	if (i[7] || s == 'S' || s == 'C')
	{
		if ((s == 'c' || s == 'C') && (i[8] = 9))
			if (!(un = unicd(va_arg(*ar, int))) && (i[10] -= 1))
				un = ft_strdup("");
		if (s == 's' || s == 'S')
			if (!(un = unistr(va_arg(*ar, wchar_t *))))
				un = ft_strdup("(null)");
		outstr(un, i);
		free(un);
	}
	else
	{
		if (s == 'c' && ((c = va_arg(*ar, int))
			|| (i[8] = 9)))
			strendf(c, i);
		else
			outstr(va_arg(*ar, char *), i);
	}
}

static	void	opersec(char *s, va_list *ar, int *i)
{
	if (s[*i] == 'a' || s[*i] == 'A')
	{
		if (i[5])
			ft_dblhex(va_arg(*ar, long double), i, s[*i]);
		else
			ft_dblhex(va_arg(*ar, double), i, s[*i]);
	}
	else if (s[*i] == 'R' || s[*i] == 'r' || s[*i] == 'B')
	{
		if (s[*i] == 'R')
			i[13] = 16;
		else
			i[13] = (s[*i] == 'r' ? 8 : 2);
		outstr(ft_itoabase(ft_basetoint(va_arg(*ar, char *), i[13]), 0, 0), i);
	}
	else
		ft_prfdbl(s[*i], i, ar);
}

void			ft_prfoper(char *s, va_list *ar, int *i)
{
	char		*st;

	st = NULL;
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
		ft_prfnbr(s[*i], i, ar, st);
	else if (s[*i] == 'c' || s[*i] == 'C' || s[*i] == 's' || s[*i] == 'S')
		prfstr(s[*i], ar, i);
	else if (s[*i] == 'p' && (st = ft_itoabase(va_arg(*ar, uintmax_t), 16, 97)))
	{
		st = outstr(ft_joinfree("0x", st, 2), i);
		free(st);
	}
	else
		opersec(s, ar, i);
}
