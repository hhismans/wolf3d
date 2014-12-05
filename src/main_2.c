/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/05 06:25:50 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/05 08:16:37 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "keyboard.h"

int		key_hook(int keycode, t_env *e)
{
	mlx_destroy_image(e->mlx, e->img);
	ft_putstr("Keu :");
	ft_putnbr(keycode);
	if (keycode == KEY_A)
	{
	double oldDirX = e->v.dirx;
			e->v.dirx = e->v.dirx * cos(-0.05) - e->v.diry * sin(-0.05);
			e->v.diry = oldDirX * sin(-0.05) + e->v.diry * cos(-0.05);
			double oldPlaneX = e->v.planx;
			e->v.planx = e->v.planx * cos(-0.05) - e->v.plany * sin(-0.05);
			e->v.plany = oldPlaneX * sin(-0.05) + e->v.plany * cos(-0.05);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->img, 0, 0);
	e->img = mlx_new_image(e->mlx, WX, WY);

}
void	set_vars(t_env *e)
{
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

int main(int argc, char **argv)
{
	int x;
	int i = 0;
	int lineHeight;
	t_env e;
	int nbr_line;
	t_point p1;
	t_point p2;
	e.map = getinfo(&nbr_line, argv[1]);
	e.mlx = mlx_init();
	e.win = mlx_new_window(e.mlx, WX, WY, "wolf");
	e.img = mlx_new_image(e.mlx, WX, WY);
	set_vars(&e);
	x = 0;
	while (i < 1300)
	{
	while (x < WX)
	{
		comput_vars(&e, x);
		define_side_n_step(&e);
		wall_hit(&e);
		define_walldist(&e);
		lineHeight = abs((int)(WY / (e.v.perpwalldist)));
		p1.x = x;
		p2.x = x;
		p1.y = WY / 2 + lineHeight / 2;
		p2.y = WY / 2 - lineHeight / 2;
		ft_drawline_img_c(e.img, p1, p2, rainbow_gen(x));
		//	printf("screen X = %lf\n", screenX);
		x++;
	}
			x = 0;
			double oldDirX = e.v.dirx;
			e.v.dirx = e.v.dirx * cos(-0.05) - e.v.diry * sin(-0.05);
			e.v.diry = oldDirX * sin(-0.05) + e.v.diry * cos(-0.05);
			double oldPlaneX = e.v.planx;
			e.v.planx = e.v.planx * cos(-0.05) - e.v.plany * sin(-0.05);
			e.v.plany = oldPlaneX * sin(-0.05) + e.v.plany * cos(-0.05);
			i++;
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	usleep(100);
	mlx_destroy_image(e.mlx, e.img);
	e.img = mlx_new_image(e.mlx, WX, WY);
	}
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	mlx_key_hook(e.win, key_hook, &e);
	mlx_loop(e.mlx);
}
