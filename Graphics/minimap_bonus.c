/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjazouli@student.1337.ma <yjazouli>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 11:31:18 by yjazouli          #+#    #+#             */
/*   Updated: 2025/08/23 12:24:26 by yjazouli@st      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void put_pixel_minimap(int x, int y, unsigned int color)
{
    t_mlx *mlx;
    char *addr;

    mlx = get_mlx();
    if (!mlx || !mlx->addr)
        return;
    if (x < 0 || y < 0 || x >= mlx->width || y >= mlx->height)
        return;
    addr = mlx->addr + (y * mlx->line + x * (mlx->bpp / 8));
    *(unsigned int *)addr = color;
}

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
            put_pixel_minimap(x + j, y + i, color);
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

static void draw_rect_clipped(int x, int y, int w, int h, unsigned int color,
                              int ix, int iy, int iw, int ih)
{
    int sx = x;
    int sy = y;
    int ex = x + w;
    int ey = y + h;

    if (ex <= ix || ey <= iy || sx >= ix + iw || sy >= iy + ih)
        return;

    if (sx < ix)
        sx = ix;
    if (sy < iy)
        sy = iy;
    if (ex > ix + iw)
        ex = ix + iw;
    if (ey > iy + ih)
        ey = iy + ih;

    for (int yy = sy; yy < ey; ++yy)
        for (int xx = sx; xx < ex; ++xx)
            put_pixel_minimap(xx, yy, color);
}

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
                put_pixel_minimap(x, y, color);
        }
    }
}

static void draw_corner_ring_clipped(int cx, int cy, int r, int t, unsigned int color,
                                     int quadrant, int ix, int iy, int iw, int ih)
{
    if (r <= 0 || t <= 0)
        return;
    int x0 = cx - r;
    int y0 = cy - r;
    int x1 = cx + r;
    int y1 = cy + r;

    if (x1 < ix || y1 < iy || x0 >= ix + iw || y0 >= iy + ih)
        return;

    if (x0 < ix)
        x0 = ix;
    if (y0 < iy)
        y0 = iy;
    if (x1 > ix + iw - 1)
        x1 = ix + iw - 1;
    if (y1 > iy + ih - 1)
        y1 = iy + ih - 1;

    int outer2 = r * r;
    int inner = r - t;
    if (inner < 0)
        inner = 0;
    int inner2 = inner * inner;

    for (int y = y0; y <= y1; ++y)
    {
        for (int x = x0; x <= x1; ++x)
        {
            int dx = x - cx;
            int dy = y - cy;
            int dist2 = dx * dx + dy * dy;
            if (dist2 < inner2 || dist2 > outer2)
                continue;

            if (quadrant == 0 && (dx > 0 || dy > 0))
                continue;
            if (quadrant == 1 && (dx < 0 || dy > 0))
                continue;
            if (quadrant == 2 && (dx > 0 || dy < 0))
                continue;
            if (quadrant == 3 && (dx < 0 || dy < 0))
                continue;

            put_pixel_minimap(x, y, color);
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
                put_pixel_minimap(x, y, mm->col_bg);
            }
        }
    }
}

static int is_wall_at(t_map *map, t_parse *parse, int x, int y)
{
    if (!map || x < 0 || y < 0 || x >= map->width || y >= map->height)
        return (0);
    if (map->grid)
        return (map->grid[y * map->width + x] == 1);
    if (!parse || !parse->map[y])
        return (0);
    if (x >= (int)strlen(parse->map[y]))
        return (0);
    return (parse->map[y][x] == '1');
}

static void draw_wall_border_clipped(t_minimap *mm, t_map *map, t_parse *parse,
                                     int tile_x, int tile_y, int px, int py, int ix, int iy, int iw, int ih)
{
    int top = is_wall_at(map, parse, tile_x, tile_y - 1);
    int bottom = is_wall_at(map, parse, tile_x, tile_y + 1);
    int left = is_wall_at(map, parse, tile_x - 1, tile_y);
    int right = is_wall_at(map, parse, tile_x + 1, tile_y);
    int diag_tl = is_wall_at(map, parse, tile_x - 1, tile_y - 1);
    int diag_tr = is_wall_at(map, parse, tile_x + 1, tile_y - 1);
    int diag_bl = is_wall_at(map, parse, tile_x - 1, tile_y + 1);
    int diag_br = is_wall_at(map, parse, tile_x + 1, tile_y + 1);
    int size = mm->cell_px;
    int t;
    int r;
    int exp;

    if (size <= 0)
        return;

    t = (size >= 12) ? 2 : 1;
    r = size / 6;
    if (r < 1)
        r = 1;
    if (r > (size / 2) - t)
        r = (size / 2) - t;
    if (r < 1)
        r = 1;

    exp = 1;

    int hx = px + r - exp;
    if (hx < px)
        hx = px;
    int hlen = size - 2 * (r - exp);
    if (hlen < 0)
        hlen = 0;

    int vy = py + r - exp;
    if (vy < py)
        vy = py;
    int vlen = size - 2 * (r - exp);
    if (vlen < 0)
        vlen = 0;

    if (!top)
        draw_rect_clipped(hx, py, hlen, t, mm->col_wall, ix, iy, iw, ih);
    if (!bottom)
        draw_rect_clipped(hx, py + size - t, hlen, t, mm->col_wall, ix, iy, iw, ih);
    if (!left)
        draw_rect_clipped(px, vy, t, vlen, mm->col_wall, ix, iy, iw, ih);
    if (!right)
        draw_rect_clipped(px + size - t, vy, t, vlen, mm->col_wall, ix, iy, iw, ih);
    if (!top && !left)
        draw_corner_ring_clipped(px + r, py + r, r, t, mm->col_wall, 0, ix, iy, iw, ih);
    if (!top && !right)
        draw_corner_ring_clipped(px + size - r - 1, py + r, r, t, mm->col_wall, 1, ix, iy, iw, ih);
    if (!bottom && !left)
        draw_corner_ring_clipped(px + r, py + size - r - 1, r, t, mm->col_wall, 2, ix, iy, iw, ih);
    if (!bottom && !right)
        draw_corner_ring_clipped(px + size - r - 1, py + size - r - 1, r, t, mm->col_wall, 3, ix, iy, iw, ih);

    int conn = r / 2;
    if (conn < 1)
        conn = 1;

    if (!diag_tl && (top || left))
        draw_rect_clipped(px, py, conn, conn, mm->col_wall, ix, iy, iw, ih);

    if (!diag_tr && (top || right))
        draw_rect_clipped(px + size - conn, py, conn, conn, mm->col_wall, ix, iy, iw, ih);

    if (!diag_bl && (bottom || left))
        draw_rect_clipped(px, py + size - conn, conn, conn, mm->col_wall, ix, iy, iw, ih);

    if (!diag_br && (bottom || right))
        draw_rect_clipped(px + size - conn, py + size - conn, conn, conn, mm->col_wall, ix, iy, iw, ih);
}

static void draw_seg_clipped(t_minimap *mm, t_seg *s, int ix, int iy, int iw, int ih)
{
    int px, py;
    int w, h;

    if (!s || !mm)
        return;

    /* Convert tile coords -> pixel coords using existing transform */
    world_to_minimap(mm, (double)s->x, (double)s->y, &px, &py);

    if (s->dir == SEG_DIR_HORIZ)
    {
        w = s->len * mm->cell_px;
        h = mm->cell_px;
    }
    else
    {
        w = mm->cell_px;
        h = s->len * mm->cell_px;
    }

    draw_rect_clipped(px, py, w, h, s->color, ix, iy, iw, ih);
}

static void draw_seg_inner_clipped(t_minimap *mm, t_seg *s, int ix, int iy, int iw, int ih)
{
    int px, py;
    int w, h;
    int inset;
    int border_t;
    int r;

    if (!s || !mm)
        return;

    /* compute top-left of tile in pixels (exact) */
    px = mm->content_x + s->x * mm->cell_px;
    py = mm->content_y + s->y * mm->cell_px;

    border_t = (mm->cell_px >= 12) ? 2 : 1;
    r = mm->cell_px / 6;
    if (r < 1) r = 1;
    if (r > (mm->cell_px / 2) - border_t)
        r = (mm->cell_px / 2) - border_t;
    inset = r - 1;
    if (inset < 0) inset = 0;
    /* clamp inset so we never make width/height <= 0 */
    if (inset > mm->cell_px / 2 - 1)
        inset = mm->cell_px / 2 - 1;
    if (inset < 0) inset = 0;

    if (s->dir == SEG_DIR_HORIZ)
    {
        w = s->len * mm->cell_px - 2 * inset;
        h = mm->cell_px - 2 * inset;
        px += inset;
        py += inset;
    }
    else /* vertical */
    {
        w = mm->cell_px - 2 * inset;
        h = s->len * mm->cell_px - 2 * inset;
        px += inset;
        py += inset;
    }

    if (w > 0 && h > 0)
        draw_rect_clipped(px, py, w, h, s->color, ix, iy, iw, ih);
}
/* helper: test border tile using mash.nbr_mask if available */
static int is_border_tile(t_minimap *mm, t_map *map, int x, int y)
{
    int idx;
    uint8_t mask;
    if (!map) return 0;
    if (!is_wall_at(map, get_parse(), x, y)) return 0;
    if (mm && mm->mash.nbr_mask)
    {
        idx = y * map->width + x;
        mask = mm->mash.nbr_mask[idx];
        /* if fully surrounded (all 8 neighbors walls) mask == 0xFF -> not a border */
        /* otherwise it's a border tile that needs border/corner drawing */
        return (mask != 0xFF);
    }
    /* fallback: compute neighbor test (treat out-of-bounds as non-wall -> border) */
    return (!is_wall_at(map, get_parse(), x - 1, y) || !is_wall_at(map, get_parse(), x + 1, y) ||
            !is_wall_at(map, get_parse(), x, y - 1) || !is_wall_at(map, get_parse(), x, y + 1) ||
            !is_wall_at(map, get_parse(), x - 1, y - 1) || !is_wall_at(map, get_parse(), x + 1, y - 1) ||
            !is_wall_at(map, get_parse(), x - 1, y + 1) || !is_wall_at(map, get_parse(), x + 1, y + 1));
}

void minimap_render(void)
{
    t_gameplay *gameplay;
    t_minimap *mm;
    t_map *map;
    t_parse *parse;
    int i;
    int j;
    int px;
    int py;

    gameplay = get_gameplay();
    if (!gameplay)
        return;
    mm = &gameplay->minimap;
    parse = get_parse();
    map = get_map();

    fprintf(stderr, "[minimap] before ensure: dirty=%d seg_count=%d seg_capacity=%d build_stamp=%u\n",
            mm->mash.dirty, mm->mash.seg_count, mm->mash.seg_capacity, mm->build_stamp);

    minimap_ensure_built(mm);

    /* debug: after ensure */
    {
        t_mlx *mlx = get_mlx();
        fprintf(stderr,
                "[minimap] after ensure: dirty=%d seg_count=%d seg_capacity=%d cell_px=%d content=(%d,%d) content_pos=(%d,%d) build_stamp=%u\n",
                mm->mash.dirty, mm->mash.seg_count, mm->mash.seg_capacity,
                mm->cell_px, mm->content_w, mm->content_h, mm->content_x, mm->content_y,
                mm->build_stamp);
        fprintf(stderr, "[minimap] mlx=%p addr=%p bpp=%d line=%d screen=(%d,%d)\n",
                mlx, mlx ? mlx->addr : NULL, mlx ? mlx->bpp : 0, mlx ? mlx->line : 0,
                mlx ? mlx->width : 0, mlx ? mlx->height : 0);
    }

    draw_rect(mm->ox, mm->oy, mm->size_px, mm->size_px, mm->col_border);
    draw_rect(mm->ox + 2, mm->oy + 2, mm->size_px - 4, mm->size_px - 4, mm->col_bg);

    int ix = mm->ox + 2;
    int iy = mm->oy + 2;
    int iw = mm->size_px - 4;
    int ih = mm->size_px - 4;

    // if (mm->mash.segs)
    // {
    //     for (i = 0; i < mm->mash.seg_count; ++i)
    //         draw_seg_inner_clipped(mm, &mm->mash.segs[i], ix, iy, iw, ih);
    // }

    // for (j = 0; j < map->height; ++j)
    // {
    //     for (i = 0; i < map->width; ++i)
    //     {
    //         if (is_border_tile(mm, map, i, j))
    //         {
    //             world_to_minimap(mm, (double)i, (double)j, &px, &py);
    //             draw_wall_border_clipped(mm, map, parse, i, j, px, py, ix, iy, iw, ih);
    //         }
    //     }
    // }

    /* draw pellets (scan parse map or grid) */
    j = 0;
    while (j < map->height)
    {
        i = 0;
        while (i < map->width)
        {
            int is_pellet = 0;
            if (parse && parse->map[j] && i < (int)strlen(parse->map[j]) && parse->map[j][i] == '.')
                is_pellet = 1;
            else if (map && map->grid && map->grid[j * map->width + i] == 2)
                is_pellet = 1;
            if (is_pellet)
            {
                world_to_minimap(mm, (double)i, (double)j, &px, &py);
                draw_rect_clipped(px + mm->cell_px / 3, py + mm->cell_px / 3,
                                  mm->cell_px / 3, mm->cell_px / 3, mm->col_pellet, ix, iy, iw, ih);
            }
            ++i;
        }
        ++j;
    }

    for (i = 0; i < gameplay->entity_count; ++i)
    {
        t_entity *e = &gameplay->entities[i];
        if (!e || e == mm->pacman.ent)
            continue;
        world_to_minimap(mm, e->pos.x, e->pos.y, &px, &py);
        /* compute pixel radius from entity radius (fallback to small dot) */
        int er = (int)((e->radius > 0.0) ? (e->radius * mm->world_to_px) : (mm->cell_px / 4));
        if (er < 1)
            er = 1;
        draw_circle_clipped(px, py, er, mm->col_pellet ^ 0x00FF8080, ix, iy, iw, ih);
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
