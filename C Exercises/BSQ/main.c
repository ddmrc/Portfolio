/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddemarco <ddemarco@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 16:23:42 by ddemarco          #+#    #+#             */
/*   Updated: 2022/03/03 17:46:05 by ddemarco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

char	*ft_read_file(char *path, int *lines, int *columns, char signs[3]);
int		ft_build_map(int line_col[2], char **map, char *file);
void	ft_print_map(char **map, int line_col[2]);
void	ft_algorithm(char **map, int line_col[2], char signs[3]);
char	**ft_allocat_map(int line_col[2]);
int		ft_validate(char *path);

void	ft_solve_bsq(char *path)
{
	char	*str;
	int		*line_col;
	char	signs[3];
	char	**map;

	line_col = malloc(sizeof(line_col) * 2);
	line_col[0] = 0;
	line_col[1] = 0;
	str = ft_read_file(path, &line_col[0], &line_col[1], signs);
	if (line_col[1] == 0)
		line_col[1] = 1;
	map = ft_allocat_map(line_col);
	ft_build_map(line_col, map, str);
	free(str);
	ft_algorithm(map, line_col, signs);
	free(line_col);
	free(map);
}

int	main(int argc, char **argv)
{
	int	index;

	index = 1;
	if (argc == 1)
	{
		if (ft_validate("0") > 0)
			ft_solve_bsq("0");
		else
			write(2, "map error", 9);
		write(1, "\n", 1);
		return (0);
	}
	while (index < argc)
	{
		if (ft_validate(argv[index]) > 0)
			ft_solve_bsq(argv[index]);
		else
			write(2, "map error", 9);
		write(1, "\n", 1);
		index++;
	}
	return (0);
}
