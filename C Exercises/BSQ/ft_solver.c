/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solver.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:20:25 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 17:52:55 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> 
#include <stdlib.h>
#include "struct_map.h"

int		ft_power(int nb, int power);
int		ft_sqrt(int nb);
void	ft_print_map(char **map, int line_col[2], char signs[3]);
void	ft_print_map_ints(int **map, int line_col[2]);
int		**ft_allocat_int_map(int line_col[2]);
int		ft_fill_copy(int line_col[2], t_b_maps *b_maps);
int		*ft_find_max_hor_address(int line_col[2], t_b_maps *b_maps, int max);
int		*ft_find_max_vert_address(int line_col[2], t_b_maps *b_maps, int max);

void	ft_c_maps(char **map, int line_col[2], char signs[3], t_b_maps *b_maps)
{
	int	row;
	int	col;

	row = 0;
	col = 0;
	while (row < line_col[0])
	{
		col = 0;
		while (col < line_col[1])
		{
			if (map[row][col] == signs[0])
			{
				b_maps->binary_map[row][col] = 1;
				b_maps->copy_binary_map[row][col] = 1;
			}
			else if (map[row][col] == signs[1])
			{
				b_maps->binary_map[row][col] = 0;
				b_maps->copy_binary_map[row][col] = 0;
			}
			col++;
		}
		row++;
	}
}

int	*ft_find_chosen_square_condition(int *max_hor, int *max_vert)
{
	int	*chosen_add;

	chosen_add = malloc(sizeof(chosen_add) * 2);
	if (max_hor[0] < max_vert[0])
	{
		chosen_add[0] = max_hor[0];
		chosen_add[1] = max_hor[1];
	}
	else
	{
		chosen_add[0] = max_vert[0];
		chosen_add[1] = max_vert[1];
	}
	return (chosen_add);
}

int	*ft_find_chosen_square(int *max_hor, int *max_vert)
{
	int	*chosen_add;
	int	mod_hor;
	int	mod_ver;

	chosen_add = malloc(sizeof(chosen_add) * 2);
	mod_hor = ft_sqrt(ft_power(max_hor[0], 2) + ft_power(max_hor[1], 2));
	mod_ver = ft_sqrt(ft_power(max_vert[0], 2) + ft_power(max_vert[1], 2));
	if (mod_hor == mod_ver)
	{
		chosen_add = ft_find_chosen_square_condition(max_hor, max_vert);
	}
	else if (mod_hor < mod_ver)
	{
		chosen_add[0] = max_hor[0];
		chosen_add[1] = max_hor[1];
	}
	else
	{
		chosen_add[0] = max_vert[0];
		chosen_add[1] = max_vert[1];
	}
	return (chosen_add);
}

void	ft_write_result(char **map, char signs[3], int *chosen_add, int max)
{
	int	row;
	int	col;

	row = chosen_add[0] - max + 1;
	while (row <= chosen_add[0])
	{
		col = chosen_add[1] - max + 1;
		while (col <= chosen_add[1])
		{
			map[row][col] = signs[2];
			col++;
		}
		row++;
	}
}

void	ft_algorithm(char **map, int line_col[2], char signs[3])
{
	t_b_maps	b_maps;
	int			max;
	int			*max_address_hor;
	int			*max_address_vert;
	int			*chosen_add;

	b_maps.binary_map = ft_allocat_int_map(line_col);
	b_maps.copy_binary_map = ft_allocat_int_map(line_col);
	ft_c_maps(map, line_col, signs, &b_maps);
	max = ft_fill_copy(line_col, &b_maps);
	max_address_hor = ft_find_max_hor_address(line_col, &b_maps, max);
	max_address_vert = ft_find_max_vert_address(line_col, &b_maps, max);
	chosen_add = ft_find_chosen_square(max_address_hor, max_address_vert);
	ft_write_result(map, signs, chosen_add, max);
	ft_print_map(map, line_col, signs);
	free(b_maps.binary_map);
	free(b_maps.copy_binary_map);
	free(max_address_hor);
	free(max_address_vert);
	free(chosen_add);
}
