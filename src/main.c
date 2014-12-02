/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhismans <hhismans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/02 17:55:47 by hhismans          #+#    #+#             */
/*   Updated: 2014/12/02 21:44:50 by hhismans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "keyboard.h"
#include "wolf.h"

void	set_variable(int *dist_ecran, int *angle_inter)
{
	*dist_ecran = PLAN_WEIGTH / 2 / tan(30 * M_PI / 180);
}
int main (int argc, char **argv)
{
	int dist_ecran;
	int angle_iter;
	int **map;
	set_variable(&dist_ecran, &angle_inter);
	map = getinfo(argv[1]);
}
