/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 06:25:50 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/07 03:32:31 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "keyboard.h"

void	set_vars(t_env *e, char *file)
{
	int nbr_line;

	e->map = getinfo(&nbr_line, file);
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, WX, WY, "wolf");
	e->img = mlx_new_image(e->mlx, WX, WY);
	e->v.posx = 5;
	e->v.posy = 5;
	e->v.dirx = -1;
	e->v.diry = 0;
	e->v.planx = 0;
	e->v.plany = 0.66;
}

static void		define_walldist(t_env *e)
{
	if (!e->v.side)
		e->v.perpwalldist = fabs((e->v.mapx - e->v.rayx + (1 - e->v.stepx) / 2)
								/ e->v.raydirx);
	else
		e->v.perpwalldist = fabs((e->v.mapy - e->v.rayy + (1 - e->v.stepy) / 2)
								/ e->v.raydiry);
	if (e->v.perpwalldist < 0.05)
		e->v.perpwalldist = 0.05;
}

static void		wall_hit(t_env *e)
{
	int			wall;

	wall = 0;
	while (!wall)
	{
		if (e->v.sidedistx < e->v.sidedisty)
		{
			e->v.sidedistx += e->v.ddistx;
			e->v.mapx += e->v.stepx;
			e->v.side = 0;
		}
		else
		{
			e->v.sidedisty += e->v.ddisty;
			e->v.mapy += e->v.stepy;
			e->v.side = 1;
		}
		if (e->map[e->v.mapy][e->v.mapx + 1] > 0)
			wall = 1;
	}
}

static void	comput_vars(t_env *e, int x)
{
	e->v.camx = ((2 * x) / (double)WX) - 1;
	e->v.rayx = e->v.posx;
	e->v.rayy = e->v.posy;
	e->v.raydirx = e->v.dirx + e->v.planx * e->v.camx;
	e->v.raydiry = e->v.diry + e->v.plany * e->v.camx;
	e->v.mapx = (int)e->v.rayx;
	e->v.mapy = (int)e->v.rayy;
	e->v.ddistx = sqrt(1 + (e->v.raydiry * e->v.raydiry)
						/ (e->v.raydirx * e->v.raydirx));
	e->v.ddisty = sqrt(1 + (e->v.raydirx * e->v.raydirx)
						/ (e->v.raydiry * e->v.raydiry));
}

static void		define_side_n_step(t_env *e)
{
	if (e->v.raydirx < 0)
	{
		e->v.stepx = -1;
		e->v.sidedistx = (e->v.rayx - e->v.mapx) * e->v.ddistx;
	}
	else
	{
		e->v.stepx = 1;
		e->v.sidedistx = (e->v.mapx + 1.0 - e->v.rayx) * e->v.ddistx;
	}
	if (e->v.raydiry < 0)
	{
		e->v.stepy = -1;
		e->v.sidedisty = (e->v.rayy - e->v.mapy) * e->v.ddisty;
	}
	else
	{
		e->v.stepy = 1;
		e->v.sidedisty = (e->v.mapy + 1.0 - e->v.rayy) * e->v.ddisty;
	}
}

int raycaster(t_env *e, int x)
{
	int i = 0;
	int lineHeight;
	int nbr_line;
	comput_vars(e, x);
	define_side_n_step(e);
	wall_hit(e);
	define_walldist(e);
	lineHeight = abs((int)(WY / (e->v.perpwalldist)));
	//	printf("screen X = %lf\n", screenX);
		x++;
	return (lineHeight);
}

void update_fram(t_env *e)
{
	int x;
	int lineHeight;
	t_point p1;
	t_point p2;

	x = 0;
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WX, WY);
	while (x < WX)
	{
		lineHeight = raycaster(e, x);
		p1.x = x;
		p2.x = x;
		p1.y = WY / 2 + lineHeight / 2;
		p2.y = WY / 2 - lineHeight / 2;
		if (e->v.side)
			ft_drawline_img_c(e->img, p1, p2, BLUE);//rainbow_gen(x));
		else
			ft_drawline_img_c(e->img, p1, p2, BLUE + 0x003300);//rainbow_gen(x));
		x++;
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
}

void rot_cam(t_env *e, double angle)
{
	double oldDirX;
	double oldPlaneX;
   
	oldPlaneX= e->v.planx;
	oldDirX = e->v.dirx;
	e->v.dirx = e->v.dirx * cos(angle) - e->v.diry * sin(angle);
	e->v.diry = oldDirX * sin(angle) + e->v.diry * cos(angle);
	e->v.planx = e->v.planx * cos(angle) - e->v.plany * sin(angle);
	e->v.plany = oldPlaneX * sin(angle) + e->v.plany * cos(angle);
}

int main(int argc, char **argv)
{
	t_env e;
	set_vars(&e, argv[1]);
	update_fram(&e);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
}
