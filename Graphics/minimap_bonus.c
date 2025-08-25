/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli <yjazouli@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:31:18 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/24 12:02:43 by yjazouli         ###   ########.fr       */
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

static void world_to_minimap(t_minimap *mm, double wx, double wy, int *px, int *py)
{
    double map_x;
    double map_y;

    if (!mm || !px || !py)
        return;
    map_x = (wx - mm->world_offset_x) * mm->world_to_px;
    map_y = (wy - mm->world_offset_y) * mm->world_to_px;
    *px = mm->content_x + (int)map_x;
    *py = mm->content_y + (int)map_y;
}

// static void draw_rect_clipped(int x, int y, int w, int h, unsigned int color,
//                               int ix, int iy, int iw, int ih)
// {
//     int sx = x;
//     int sy = y;
//     int ex = x + w;
//     int ey = y + h;

//     if (ex <= ix || ey <= iy || sx >= ix + iw || sy >= iy + ih)
//         return;

//     if (sx < ix)
//         sx = ix;
//     if (sy < iy)
//         sy = iy;
//     if (ex > ix + iw)
//         ex = ix + iw;
//     if (ey > iy + ih)
//         ey = iy + ih;

//     for (int yy = sy; yy < ey; ++yy)
//         for (int xx = sx; xx < ex; ++xx)
//             pixel_put(xx, yy, color);
// }

static void draw_circle_clipped(int cx, int cy, int r, unsigned int color,
                                int ix, int iy, int iw, int ih)
{
    if (r <= 0)
        return;
    int minx = cx - r;
    int miny = cy - r;
    int maxx = cx + r;
    int maxy = cy + r;

    if (maxx <= ix || maxy <= iy || minx >= ix + iw || miny >= iy + ih)
        return;

    if (minx < ix)
        minx = ix;
    if (miny < iy)
        miny = iy;
    if (maxx > ix + iw)
        maxx = ix + iw;
    if (maxy > iy + ih)
        maxy = iy + ih;

    for (int y = miny; y <= maxy; ++y)
    {
        for (int x = minx; x <= maxx; ++x)
        {
            int dx = x - cx;
            int dy = y - cy;
            if (dx * dx + dy * dy <= r * r)
                pixel_put(x, y, color);
        }
    }
}

static void draw_pacman_clipped(t_minimap *mm,
                                double wx, double wy, double dirx, double diry,
                                int ix, int iy, int iw, int ih)
{
    int cx, cy;
    int r;
    int x0, y0, x1, y1;
    double facing;
    double mouth_angle;
    double dx, dy, ang, diff;

    if (!mm)
        return;
    world_to_minimap(mm, wx, wy, &cx, &cy);

    r = (int)(mm->cell_px * mm->pacman.scale * 0.45);
    if (r < 2)
        r = 2;

    draw_circle_clipped(cx, cy, r, mm->col_pacman, ix, iy, iw, ih);

    if (dirx == 0.0 && diry == 0.0)
        facing = 0.0;
    else
        facing = atan2(diry, dirx);

    mouth_angle = mm->pacman.mouth_open * (M_PI * 0.6);

    x0 = cx - r;
    if (x0 < ix)
        x0 = ix;
    y0 = cy - r;
    if (y0 < iy)
        y0 = iy;
    x1 = cx + r;
    if (x1 > ix + iw - 1)
        x1 = ix + iw - 1;
    y1 = cy + r;
    if (y1 > iy + ih - 1)
        y1 = iy + ih - 1;

    for (int y = y0; y <= y1; ++y)
    {
        for (int x = x0; x <= x1; ++x)
        {
            dx = (double)(x - cx);
            dy = (double)(y - cy);
            if (dx * dx + dy * dy > (double)r * (double)r)
                continue;
            ang = atan2(dy, dx);
            diff = ang - facing;
            while (diff <= -M_PI)
                diff += 2.0 * M_PI;
            while (diff > M_PI)
                diff -= 2.0 * M_PI;
            if (fabs(diff) < mouth_angle * 0.5)
            {
                pixel_put(x, y, mm->col_bg);
            }
        }
    }
}

static void draw_line_clipped(int x0, int y0, int x1, int y1,
                              unsigned int color, int ix, int iy, int iw, int ih)
{
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;
    int e2;
    int x_min = ix;
    int y_min = iy;
    int x_max = ix + iw - 1;
    int y_max = iy + ih - 1;

    while (1)
    {
        if (x0 >= x_min && x0 <= x_max && y0 >= y_min && y0 <= y_max)
            pixel_put(x0, y0, color);
        if (x0 == x1 && y0 == y1)
            break;
        e2 = 2 * err;
        if (e2 >= dy)
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

static void draw_segs_clipped(t_minimap *mm, int ix, int iy, int iw, int ih)
{
    if (!mm || !mm->mash.segs || mm->mash.seg_count <= 0)
        return ;

    for (int si = 0; si < mm->mash.seg_count; ++si)
    {
        t_seg *s = &mm->mash.segs[si];
        if (!s)
            continue ;

        int px0, py0, px1, py1;
        unsigned int col = s->color ? s->color : mm->col_wall;

        world_to_minimap(mm, (double)s->x, (double)s->y, &px0, &py0);
        if (s->dir == 0)
            world_to_minimap(mm, (double)(s->x + s->len), (double)s->y, &px1, &py1);
        else
            world_to_minimap(mm, (double)s->x, (double)(s->y + s->len), &px1, &py1);

        if (px1 < ix || px0 > ix + iw - 1 || py1 < iy || py0 > iy + ih - 1)
            continue ;

        draw_line_clipped(px0, py0, px1, py1, col, ix, iy, iw, ih);
    }
}

void minimap_render(void)
{
    t_gameplay *gameplay;
    t_minimap *mm;
    int px;
    int py;

    gameplay = get_gameplay();
    if (!gameplay)
        return;
    mm = &gameplay->minimap;

    draw_rect(mm->ox, mm->oy, mm->size_px, mm->size_px, mm->col_border);
    draw_rect(mm->ox + 2, mm->oy + 2, mm->size_px - 4, mm->size_px - 4, mm->col_bg);

    int ix = mm->ox + 2;
    int iy = mm->oy + 2;
    int iw = mm->size_px - 4;
    int ih = mm->size_px - 4;

    draw_segs_clipped(mm, ix, iy, iw, ih);

    if (gameplay && gameplay->pellet_count > 0 && gameplay->pellets)
    {
        for (int pi = 0; pi < gameplay->pellet_count; ++pi)
        {
            t_entity *pent = gameplay->pellets[pi].ent;
            if (!pent)
                continue;
            if (pent->gone || pent->type != ENTITY_PELLET)
                continue;
            world_to_minimap(mm, pent->pos.x, pent->pos.y, &px, &py);
            int pr = (int)((pent->radius > 0.0) ? (pent->radius * mm->world_to_px)
                                                 : (mm->cell_px / 3));
            if (pr < 1) pr = 1;
            draw_circle_clipped(px, py, pr, mm->col_pellet, ix, iy, iw, ih);
        }
    }

    if (mm->pacman.ent)
    {
        world_to_minimap(mm, mm->pacman.ent->pos.x, mm->pacman.ent->pos.y, &px, &py);
        draw_pacman_clipped(mm,
                            mm->pacman.ent->pos.x, mm->pacman.ent->pos.y,
                            mm->pacman.ent->dir.x, mm->pacman.ent->dir.y,
                            ix, iy, iw, ih);
    }
}
