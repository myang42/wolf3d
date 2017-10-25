/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 18:49:00 by myang             #+#    #+#             */
/*   Updated: 2017/10/24 17:11:31 by myang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include "./keys.h"
# include "./pxl_color.h"
# include <math.h>
# define TRUE 1
# define FALSE 0
# define WIN_L 640
# define WIN_OH 480
# define WIN_H 380

typedef struct		s_inv
{
	struct s_inv	*tokken;
	struct s_inv	*pv;
	struct s_inv	*weapon;
	struct s_inv	*ammo;
	int				nbr;
}					t_inv;

typedef struct		s_key
{
	int				mvmnt_f;
	int				mvmnt_b;
	int				mvmnt_r;
	int				mvmnt_l;
	int				rott_r;
	int				rott_l;
}					t_key;

typedef struct		s_ray
{
	double			floorval[2];
	int				floor_text[2];
	double			dist[2];
	int				step[2];
	double			sidedist[2];
	double			raydir[2];
	double			raypos[2];
	int				height_l;
	double			perps;
	double			wally;
	double			wallx;
}					t_ray;

typedef struct		s_img
{
	void			*i_img;
	char			*bts;
	int				bpp;
	int				endian;
	int				size_line;
	int				textx;
	int				texty;
	double			cfx;
	double			cfy;
	int				xy[2];
}					t_img;

typedef struct		s_mmmapdisplay
{
	int				pxx;
	int				pxy;
	int				wall;
}					t_mmapdisplay;

typedef	struct		s_map
{
	int				**tabmap;
	int				minimap[10][10];
	int				s_x;
	int				s_y;
	int				cury;
	int				curx;
	int				pxx;
	int				pxy;
	int				arrival[2];
}					t_map;

typedef struct		s_cam
{
	double			poscam[2];
	double			dircam[2];
	double			dirwin[2];
	t_map			posmap;
	int				correct;
	int				spewall;
	double			varx;
	double			vary;
	double			vit;
}					t_cam;

typedef struct		s_xpm
{
	t_img			*skybox;
	t_img			*xpm_t0;
	t_img			*xpm_t1;
	t_img			*xpm_t2;
	t_img			*xpm_t3;
	t_img			*xpm_t4;
	t_img			*xpm_t5;
	t_img			*xpm_t6;
	t_img			*xpm_t7;
	t_img			*window_1;
	t_img			*minimap;
	t_img			*xpm_pv1;
	t_img			*xpm_pv2;
	t_img			*xpm_pv3;
	t_img			*xpm_weapon;
	t_img			*xpm_wicon;
	t_img			*gameover;
	t_img			*arrival;
}					t_xpm;

typedef struct		s_text
{
	int				color_or_text;
	int				walltextt;
	int				floortextt;
	t_xpm			*xpm;
}					t_text;

typedef struct		s_music
{
	int				selected;
}					t_music;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	char			*bts;
	t_key			*key;
	t_map			*map;
	t_img			*img;
	t_cam			*cam;
	t_ray			*ray;
	t_inv			*inv;
	t_mmapdisplay	*mmapdisplay;
	int				impact;
	int				color;
	int				dmg;
	t_text			*text;
	t_music			*music;
	int				merror;
}					t_env;

t_img				*select_xpm(t_env *e, int walltextt);

int					main(int ar, char **ac);
int					keyfonc(int key, t_env *e);
int					start_pos(t_env *e, t_map *map);
int					map_error(t_env *e, t_map *map);
int					mvmnt_camrott(t_env *e);
int					mvmnt_camdir(t_env *e, t_cam *cam, int x, int y);
int					txt_error(char *tmp);
int					red_cross(int key, t_env *e);

unsigned int		sleep(unsigned int time);

double				wallx_val(t_env *e);

void				farrival(t_env *e);
void				init_xpm_text(t_env *e);
void				walltexturing(t_env *e, int wallnbr, t_img *xpmt);
void				cf_text_color(t_env *e, int y);
void				clear_all(t_env *e, int call);
void				clear_struct_displayed(t_env *e, int call);
void				clear_struct_init(t_env *e);
void				creat_dint(char *line, int nbr_y, t_env *e, t_map *map);
void				creat_win(t_env *e);
void				draw_colo(t_env *e, int x, double perps);
void				draw_mmap(t_cam *cam, t_env *e, t_map *map);
void				draw_pxl_mmap(t_img *mmap, int y, int x, int color);
void				init_bag(t_inv *inv, t_env *e);
void				init_cam(t_env *e);
void				init_struct(t_env *e);
void				init_struct_displayed(t_env *e);
void				init_var_map(t_key *key);
void				interface(t_env *e);
void				interface_mmap(t_env *e);
void				interface_txt(t_env *e, t_xpm *xpm);
void				pix_put_cf(t_env *e, int y, int x, int color);
void				pix_put_img(t_env *e, int y, int x, int color);
void				raycast_win_l(t_env *e, t_ray *ray);
void				readfile(t_env *e, char *ac);
void				select_file(char *line, t_env *e, t_map *map);
void				sy_size(char *line, t_env *e);
void				text_to_bts(t_env *e, t_img *xpmt, int x, int y);
void				verif(char *line, t_env *e, int y, int *i);
void				text_put_img(t_env *e, int y, int cfw);
void				basiccolor_or_text(t_env *e, int x, int y);
void				tokken_case(t_map *map, t_inv *bag, t_cam cam);
void				val_floor_ceilling(t_env *e, int y);
void				wall_or_cf(t_env *e, int y, int cfw);
void				floor_val(t_env *e, int curx, int cury, double wallx);
void				music_select(t_music *bgm);
void				music_bgm(t_env *e);
void				val_mmap(t_cam *cam);
void				xpmt_secur(t_env *e);
void				def_playermmaap(t_env *e);
void				dmg_anim(t_env *e, double lastx, double lasty, t_cam *cam);
void				secur_init(t_env *e);
void				xpmt_secur(t_env *e);
void				sprite_data(t_img *xpm_selected, char *xpm_name, t_env *e);
void				skybox(t_env *e);
void				msg_error(void);
void				quit_exe(t_env *e, int call);
void				quit_error(t_env *e);
void				key_pressed(t_env *e, int key);

#endif
