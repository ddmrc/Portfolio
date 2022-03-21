/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:00:20 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 17:56:41 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	ft_build_map(int line_col[2], char **map, char *file)
{
	int		col;
	int		row;
	int		index;

	index = 0;
	row = 0;
	while (row < line_col[0])
	{
		col = 0;
		while (file[index] && col < line_col[1])
		{
			map[row][col] = file[index];
			col++;
			index++;
		}
		map[row][col] = file[index];
		row++;
		index++;
	}
	return (col);
}

void	ft_print_map(char **map, int line_col[2], char signs[3])
{
	int		row;
	int		col;

	row = 0;
	col = 0;
	if (line_col[0] == 1 && line_col[1] == 1 && map[0][0] == signs[0])
	{
		write(1, &signs[2], 1);
		write(1, "\n", 1);
		return ;
	}
	while (row < line_col[0])
	{
		col = 0;
		while (col < line_col[1])
		{
			write(1, &map[row][col], 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}

void	ft_print_map_ints(int **map, int line_col[2])
{
	int		row;
	int		col;
	int		num;

	row = 0;
	col = 0;
	while (row < line_col[0])
	{
		col = 0;
		while (col < line_col[1])
		{
			num = map[row][col] + '0';
			write(1, &num, 1);
			col++;
		}
		write(1, "\n", 1);
		row++;
	}
}
