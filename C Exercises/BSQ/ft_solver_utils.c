/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:27:54 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 17:51:11 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct_map.h"
#include <stdlib.h>

int	ft_fill_copy_condition(t_b_maps *b_maps, int *col, int *row, int _max)
{
	int	max;
	int	min;

	max = _max;
	min = 1000;
	if (b_maps->copy_binary_map[*row - 1][*col] < min)
		min = b_maps->copy_binary_map[*row - 1][*col];
	if (b_maps->copy_binary_map[*row][*col - 1] < min)
		min = b_maps->copy_binary_map[*row][*col - 1];
	if (b_maps->copy_binary_map[*row - 1][*col - 1] < min)
		min = b_maps->copy_binary_map[*row - 1][*col - 1];
	b_maps->copy_binary_map[*row][*col] = min + 1;
	if (b_maps->copy_binary_map[*row][*col] > max)
		max = b_maps->copy_binary_map[*row][*col];
	return (max);
}

int	ft_fill_copy(int line_col[2], t_b_maps *b_maps)
{
	int	max;
	int	row;
	int	col;

	max = 0;
	row = 1;
	while (row < line_col[0])
	{
		col = 1;
		while (col < line_col[1])
		{
			if (b_maps->binary_map[row][col] == 1)
			{
				max = ft_fill_copy_condition(b_maps, &col, &row, max);
			}
			else
				b_maps->copy_binary_map[row][col] = 0;
			col++;
		}
		row++;
	}
	return (max);
}

int	*ft_find_max_hor_address(int line_col[2], t_b_maps *b_maps, int max)
{
	int	row;
	int	col;
	int	*max_address_hor;

	row = 0;
	col = 0;
	max_address_hor = malloc(sizeof(max_address_hor) * 2);
	while (row < line_col[0])
	{
		col = 0;
		while (col < line_col[1])
		{
			if (b_maps->copy_binary_map[row][col] == max)
				break ;
			col++;
		}
		if (b_maps->copy_binary_map[row][col] == max)
			break ;
		row++;
	}
	max_address_hor[0] = row;
	max_address_hor[1] = col;
	return (max_address_hor);
}

int	*ft_find_max_vert_address(int line_col[2], t_b_maps *b_maps, int max)
{
	int	row;
	int	col;
	int	*max_address_vert;

	row = 1;
	col = 1;
	max_address_vert = malloc(sizeof(max_address_vert) * 2);
	while (col < line_col[1])
	{
		row = 0;
		while (row < line_col[0] - 1)
		{
			if (b_maps->copy_binary_map[row][col] == max)
				break ;
			row++;
		}
		if (b_maps->copy_binary_map[row][col] == max)
			break ;
		col++;
	}
	max_address_vert[0] = row;
	max_address_vert[1] = col;
	return (max_address_vert);
}
