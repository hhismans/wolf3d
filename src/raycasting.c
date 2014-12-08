/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 08:22:48 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/08 22:26:20 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "keyboard.h"
#include <stdio.h>
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

static void		define_wallx(t_env *e)
{
	if (e->v.side == 1)
		e->v.wallx = e->v.rayx + ((e->v.mapy - e->v.rayy + (1 - e->v.stepy) / 2) / e->v.raydiry) * e->v.raydirx;
	else
		e->v.wallx = e->v.rayy + ((e->v.mapx - e->v.rayx + (1 - e->v.stepx) / 2) / e->v.raydirx) * e->v.raydiry;
	e->v.wallx -= (int)(e->v.wallx);
	e->v.txx = (int)(e->v.wallx * e->tx_hitler.w);
	if((e->v.side == 0 && e->v.raydirx > 0) || (e->v.side == 1 && e->v.raydiry))
		e->v.txx = e->tx_hitler.w - e->v.txx - 1;
	printf("wall x = %lf txx = %d txhitlerW = %d\n", e->v.wallx, e->v.txx, e->tx_hitler.w);
}

static void		draw_txt(t_env *e, int lineHeight, int x)
{
	int y;
	int d;
	char *data_img;
	char *data_txt;
	int bbp;
	int sizeline_img;
	int sizeline_txt;
	int endian;
	data_img = mlx_get_data_addr(e->img, &bbp, &sizeline_img, &endian);
	data_txt = mlx_get_data_addr(e->tx_hitler.img, &bbp, &sizeline_txt, &endian);

	y = WY / 2 - lineHeight / 2;
	while (y < WY / 2 + lineHeight / 2)
	{
		d = y * 2 - WY + lineHeight;
		e->v.txy = ((d * e->tx_hitler.h) / lineHeight) / 2;
		//printf("txy = %d, txx = %d, lineHeight = %d\n", e->v.txy, e->v.txx, lineHeight);
		y++;
		if (e->v.side == 1)
		{
			data_img[x * bbp / 8 + y * sizeline_img] = data_txt[e->v.txx * bbp / 8 + e->v.txy * sizeline_txt];
			data_img[x * bbp / 8 + y * sizeline_img + 1] = data_txt[e->v.txx * bbp / 8 + e->v.txy * sizeline_txt + 1];
			data_img[x * bbp / 8 + y * sizeline_img + 2] = data_txt[e->v.txx * bbp / 8 + e->v.txy * sizeline_txt + 2];
		}
		else
		{
			data_img[x * bbp / 8 + y * sizeline_img] = data_txt[e->v.txx * bbp / 8 + e->v.txy * sizeline_txt] / 2;
			data_img[x * bbp / 8 + y * sizeline_img + 1] = data_txt[e->v.txx * bbp / 8 + e->v.txy * sizeline_txt + 1] / 2;
			data_img[x * bbp / 8 + y * sizeline_img + 2] = data_txt[e->v.txx * bbp / 8 + e->v.txy * sizeline_txt + 2] / 2;
		}
	}
	/*double i;
	double step_in_tx;

	i = 0;
	step_in_tx = (double)lineHeight / e->tx_hitler.h;
	//	printf("step_in_x = %lf, txx = %d, lineHeight = %d\n", step_in_tx, e->v.txx, lineHeight);
	while (i < lineHeight)
	{
		mlx_pixel_put_img(e->img, x, WY/2 - lineHeight/2, ((int *)(e->tx_hitler.img))[e->v.txx + 64 * (int)i]);
	//	printf("step_in_x = %lf, txx = %d, i = %d", step_in_tx, e->v.txx, (int)i);
		char *data;
		char *data2;
		int bbp;
		int sizeline;
		int endian;
		data = mlx_get_data_addr(e->img, &bbp, &sizeline, &endian);
		data2 = mlx_get_data_addr(e->tx_hitler.img, &bbp, &sizeline, &endian);
		i = x * bbp / 8 + (int)i * sizeline;
		i2 = x * bbp / 8 
		data[i] = data
		i += step_in_tx;
	}*/
}
int raycaster(t_env *e, int x)
{
	ft_putendl("raycasting BEGIN");
	int i = 0;
	int lineHeight;
	int nbr_line;
	comput_vars(e, x);
	define_side_n_step(e);
	wall_hit(e);
	define_walldist(e);
	define_wallx(e);
	lineHeight = abs((int)(WY / (e->v.perpwalldist)));
	if (lineHeight > WY)
		lineHeight = WY;
	draw_txt(e, lineHeight, x);
	//	printf("screen X = %lf\n", screenX);
		x++;
	ft_putendl("raycasting END");
	if (lineHeight > WY)
		return (WY);
	return (lineHeight);
}

