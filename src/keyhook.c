/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyhook.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/07 02:18:32 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/07 04:54:20 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"
#include <math.h>
#include <mlx.h>
#include "fdf.h"
#include "keyboard.h"
#include "stdlib.h"

int		key_hook(int keycode, t_env *e)
{
	int i;
	int lineHeight;
	mlx_destroy_image(e->mlx, e->img);
	e->img = mlx_new_image(e->mlx, WX, WY);
	ft_putstr("Keu :");
	ft_putnbr(keycode);
	if (keycode == KEY_W)
	{
		i = 0;
		while(i < 10)
		{
			e->v.posx += e->v.dirx * 0.1;
			e->v.posy += e->v.diry * 0.1;
			update_fram(e);
			i++;
		}
	}
	if (keycode == KEY_S)
	{
		i = 0;
		while (i < 10)
		{
			e->v.posx -= e->v.dirx * 0.1;
			e->v.posy -= e->v.diry * 0.1;
			update_fram(e);
			i++;
		}
	}
	if (keycode == KEY_A)
	{
		i = 0;
		while (i<10)
		{
			rot_cam(e, 0.05);
			update_fram(e);
			i++;
		}
	}
	if (keycode == KEY_D)
	{
		i = 0;
		while (i<10)
		{
			rot_cam(e, -0.05);
			update_fram(e);
			i++;
		}
	}
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
}

