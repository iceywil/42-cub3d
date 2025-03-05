/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:54:51 by kimnguye          #+#    #+#             */
/*   Updated: 2025/03/05 23:43:23 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEF_H
# define CUB3D_DEF_H

# define _USE_MATH_DEFINES

// PI
# define PI 3.14159265359

//WINDOW
# define WIDTH 1000
# define HEIGHT 750
# define WALL_SIZ 32
# define MARGIN 2
# define MARGIN_DOOR 7

//MINI MAP
# define BLOCK 16
# define MAP_WIDTH 160
# define MAP_HEIGHT 120

//number of BLOCK to fill one line of minimap
# define MAX_BLOCK_W 10
//number of BLOCK to fill one column of minimap
# define MAX_BLOCK_H 7.5
# define FIX_MAP_X 80
# define FIX_MAP_Y 80

//PLAYER
# define SPEED 4
# define ROT_SPEED 0.1
# define PLAYER_SIZ 3

//CAMERA
# define FOV 1.047197551
# define DEFAULT_COLOR YELLOW
# define STEP 0.02

/*
//MINI MAP
# define BLOCK 16
# define MAP_WIDTH WIDTH / 5
# define MAP_HEIGHT HEIGHT / 5
//number of BLOCK to fill one line of minimap
# define MAX_BLOCK_W (MAP_WIDTH / BLOCK)
//number of BLOCK to fill one column of minimap
# define MAX_BLOCK_H (MAP_HEIGHT / BLOCK)
# define FIX_MAP_X (MAX_BLOCK_W * BLOCK / 2)
# define FIX_MAP_Y (MAX_BLOCK_H * BLOCK / 2)

//PLAYER
# define SPEED 0.05 * BLOCK
# define ROT_SPEED (PI / 120)
# define PLAYER_SIZ (BLOCK / 5)

//CAMERA
# define FOV (M_PI / 3)
# define DEFAULT_COLOR YELLOW
*/

//CODE CALCULATION
# define ROT_CODE 3
# define BASE_HEXA "0123456789ABCDEF"

//masks and events
# define KEYPRESS_EVENT 2
# define BUTTONPRESS_EVENT 4

//closing code
# define CLOSE_ALL 100

//colors
# define YELLOW 0xF8C436
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define LIGHT_BLUE 0x3BB2FA
# define MAGENTA 0xFF00FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define GREY 0x7F878B

//keyboard
# define W 119
# define A 97
# define S 115
# define D 100
# define M 109
# define O 111
# define Q 113
# define T 116
# define ESC 65307
# define SPACE 32
# define KEY_Q_MAC 16781520
# define ENTER 65293
# define NUM_7 65429
# define NUM_4 65430
# define NUM_8 65431
# define NUM_6 65432
# define NUM_2 65433
# define NUM_9 65434
# define NUM_3 65435
# define NUM_1 65436

//keyboard direction
# define LEFT 65361
# define TOP 65362
# define RIGHT 65363
# define BOTTOM 65364
# define PAGE_UP 65365
# define PAGE_DOWN 65366

//mouse
# define LEFT_CLICK 1
# define SCROLL_CLICK 2
# define RIGHT_CLICK 3
# define SCROLL_UP 4
# define SCROLL_DOWN 5

#endif
