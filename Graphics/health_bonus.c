/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   health_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 16:29:36 by yjazouli@st       #+#    #+#             */
/*   Updated: 2025/08/31 19:59:50 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void draw_rect(int x, int y, int w, int h, unsigned int color)
{
    int i;
    int j;

    i = 0;
    while (i < h)
    {
        j = 0;
        while (j < w)
        {
            pixel_put(x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void draw_health_bar(int x, int y, int width, int height, int current_hp, int max_hp)
{
    int health_width;
    unsigned int bg_color;
    unsigned int health_color;
    unsigned int border_color;

    if (max_hp <= 0)
        return;

    bg_color = 0x333333;       
    health_color = 0xFF0000;   
    border_color = 0xFFFFFF;   

    draw_rect(x - 2, y - 2, width + 4, height + 4, border_color);
    
    draw_rect(x, y, width, height, bg_color);
    
    if (current_hp < 0)
        current_hp = 0;
    if (current_hp > max_hp)
        current_hp = max_hp;
    
    health_width = (width * current_hp) / max_hp;
    
    if (health_width > 0)
        draw_rect(x, y, health_width, height, health_color);
}

void render_health_ui(void)
{
    t_gameplay *gameplay;
    t_entity *player_ent;
    int bar_x;
    int bar_y;
    int bar_width;
    int bar_height;

    gameplay = get_gameplay();
    if (!gameplay)
        return;
    
    player_ent = gameplay->player.ent;
    if (!player_ent)
        return;

    bar_x = 20;
    bar_y = 20;
    bar_width = 200;
    bar_height = 20;

    draw_health_bar(bar_x, bar_y, bar_width, bar_height, 
                    player_ent->hp, player_ent->max_hp);
}
