/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/08 08:22:48 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/08 08:35:35 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "keyboard.h"

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
	ft_putendl("raycasting BEGIN");
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
	ft_putendl("raycasting END");
	if (lineHeight > WY)
		return (WY);
	return (lineHeight);
}

