/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons_data.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelage <edelage@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 14:38:00 by edelage           #+#    #+#             */
/*   Updated: 2023/05/06 14:38:00 by edelage          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#ifndef WEAPONS_DATA_H
# define WEAPONS_DATA_H

# define NB_WEAPONS	3

typedef enum e_damage		t_damage;
typedef enum e_rate_fire	t_rate_fire;

enum	e_damage
{
	KNIFE_DAMAGE = 50,
	PISTOL_DAMAGE = 25,
	ASSAULT_RIFFLE_DAMAGE = 35,
};

enum	e_rate_fire
{
	KNIFE_RATE_FIRE = 60,
	PISTOL_RATE_FIRE = 300,
	ASSAULT_RIFFLE_RATE_FIRE = 700,
};

#endif
