/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hp_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 21:05:55 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/22 21:07:02 by yjazouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d_bonus.h"

void	entity_set_hp(t_entity *ent, int max_hp)
{
    if (!ent || max_hp <= 0)
        return ;
    ent->max_hp = max_hp;
    ent->hp = max_hp;
    ent->invuln_duration = 0.5;
    ent->invuln_time = 0.0;
}

int	entity_get_hp(t_entity *ent)
{
    if (!ent)
        return (0);
    return (ent->hp);
}

int	entity_apply_damage(t_entity *ent, int dmg)
{
    if (!ent || dmg <= 0)
        return (0);
    if (ent->hp <= 0)
        return (0);
    if (ent->invuln_time > 0.0)
        return (0);
    ent->hp -= dmg;
    if (ent->hp <= 0)
    {
        entity_kill(ent);
        return (1);
    }
    ent->invuln_time = ent->invuln_duration;
    return (0);
}

int	entity_heal(t_entity *ent, int amount)
{
    if (!ent || amount <= 0)
        return (0);
    if (ent->hp <= 0)
        return (0);
    ent->hp += amount;
    if (ent->hp > ent->max_hp)
        ent->hp = ent->max_hp;
    return (ent->hp);
}

void	entity_kill(t_entity *ent)
{
    if (!ent)
        return ;
    ent->hp = 0;
    ent->vel.x = 0.0;
    ent->vel.y = 0.0;
    ent->radius = 0.0;
}

void	entity_update_timers(t_entity *ent, double dt)
{
    if (!ent || dt <= 0.0)
        return ;
    if (ent->invuln_time > 0.0)
    {
        ent->invuln_time -= dt;
        if (ent->invuln_time < 0.0)
            ent->invuln_time = 0.0;
    }
}

