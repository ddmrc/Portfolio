/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:20:25 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 17:46:56 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power > 1)
		return (nb * ft_power(nb, power - 1));
	return (nb);
}

int	ft_sqrt(int nb)
{
	int		index;

	index = 0;
	if (nb <= 0)
		return (0);
	while (index * index < nb && index <= 46340)
		index++;
	if (index * index == nb)
		return (index);
	return (0);
}

char	**ft_allocat_map(int line_col[2])
{
	char		**map;
	int		index;

	map = malloc(sizeof(map) * (line_col[0] + 1));
	index = 0;
	while (index < line_col[0])
	{
		map[index] = malloc(sizeof(map) * (line_col[1] + 1));
		index++;
	}
	return (map);
}

int	**ft_allocat_int_map(int line_col[2])
{
	int		**map;
	int		index;

	map = malloc(sizeof(map) * (line_col[0] + 1));
	index = 0;
	while (index < line_col[0])
	{
		map[index] = malloc(sizeof(map) * (line_col[1] + 1));
		index++;
	}
	return (map);
}
