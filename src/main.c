/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 17:55:47 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/05 04:25:11 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "keyboard.h"
#include "wolf.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>
#include "fdf.h"
#include <mlx.h>

double	DtR(int degre)
{
	degre = degre * M_PI / 180;
}

/*
 * Set the variable that i need to begin the game
 */
void	set_variable(t_player *player)
{
	player->pos.x = PLAYER_X;
	player->pos.y = PLAYER_Y;
	player->dir.x = DIR_X;
	player->dir.y = DIR_Y;
	player->plane.y = 0.66;//tan(DtR(FOV / 2)) * DIR_X;
	printf("plnne y  =  %lf \n", player->plane.y);
	player->plane.x = 0;
}

int main (int argc, char **argv)
{
	t_point p1;
	t_point p2;
	t_vector	map;
	t_player	player;
	t_ray		ray;
	int			**map_info;
	int			i;
	double		screenX;
	t_vector	delta;
	t_vector	side;
	t_vector	step;
	int			touch;
	int			side_face;
	int			map_info_nbrline;
	t_env e;
	e.mlx = mlx_init();
	e.img = mlx_new_image(e.mlx, WINDOW_X, WINDOW_Y);
	e.win = mlx_new_window(e.mlx, WINDOW_X, WINDOW_Y, "Wolf 3d");
	i = 0;
	set_variable(&player);
	map_info = getinfo(&map_info_nbrline, argv[1]);
	ft_putnbr(map_info_nbrline);
	ft_putnbr(map_info[3][15]);
	while (i <= WINDOW_X)
	{
		screenX = 2 * (double)i / WINDOW_X - 1;
		ray.pos.x = player.pos.x;
		ray.pos.y = player.pos.y;
		ray.dir.x = player.dir.x + player.plane.x * screenX;
		ray.dir.y = player.dir.y + player.plane.y * screenX;

		map.x = (int)(player.pos.x / BLOCK_SIZE);
		map.y = (int)(player.pos.y / BLOCK_SIZE);
		delta.x = sqrt(BLOCK_SIZE * BLOCK_SIZE + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
		delta.y = sqrt(BLOCK_SIZE * BLOCK_SIZE + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
		if (ray.dir.x < 0)
		{
			step.x = -1;
			side.x = (ray.pos.x - map.x * 64) * delta.x / 64;
		}
		else
		{
			step.x = 1;
			side.x = delta.x * (64 * (map.x +1) - ray.pos.x) / 64;
		}
		if (ray.dir.y < 0)
		{
			step.y = -1;
			side.y = (ray.pos.y - map.x * 64) * delta.y / 64;
		}
		else
		{
			step.y = 1;
			side.y = delta.y * (64 * (map.y + 1) - ray.pos.y) / 64;
		}
		touch = 0;
		while (touch == 0)
		{
			if (side.x < side.y)
			{
				side.x += delta.x;
				map.x += step.x;
				side_face = 0;
			}
			else
			{
				side.y += delta.y;
				map.y += step.y;
				side_face = 1;
			}
			if (map_info[(int)map.y][(int)map.x + 1])
				touch = 1;
		}
		int perpWallDist;
//		if (side_face == 0)
			perpWallDist = fabs((sqrt(side.x * side.x + side.y * side.y)));//(map.x * 64 - ray.pos.x + (1 - step.x) * 32) / ray.dir.x);
//		else
//			perpWallDist = fabs((sqrt(side.y * side.));//(map.y * 64 - ray.pos.y + (1 - step.y) * 32) / ray.dir.y);

		int lineHeight = abs((int)(WINDOW_Y / (perpWallDist)));
		ft_putstr("lineHeight = ");
		ft_putnbr(lineHeight);
		p1.x = i;
		p2.x = i;
		p1.y = WINDOW_Y / 2 + lineHeight / 2;
		p2.y = WINDOW_Y / 2 - lineHeight / 2;
		ft_drawline_img_c(e.img, p1, p2, RED);
		//	printf("screen X = %lf\n", screenX);
			ft_putstr("\nmap.x = ");
			ft_putnbr((int)map.x);
			ft_putstr("\nmap.y = ");
			ft_putnbr((int)map.y);
			ft_putendl("");
		i++;
	}
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	mlx_loop(e.mlx);
}
