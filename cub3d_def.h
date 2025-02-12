/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_def.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kimnguye <kimnguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:54:51 by kimnguye          #+#    #+#             */
/*   Updated: 2025/02/12 13:50:57 by kimnguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_DEF_H
# define CUB3D_DEF_H

# define _USE_MATH_DEFINES

//default values
# define UNSET_DOUBLE 9999

//WINDOW
# define WIDTH 800 //1920  
# define HEIGHT 600 //1080
# define MARGIN 5

//MINI MAP
# define MAP_WIDTH WIDTH / 5
# define MAP_HEIGHT HEIGHT / 5 
# define MAP_M 1 //margin

//PIXEL
# define PIXEL (20 * WIDTH / 1920)
#define  PLAYER_SIZ (PIXEL * 2 / 3)

//CAMERA
# define ANGLE_VIEW (M_PI / 2)
# define ANGLE_ROT (M_PI / 16)
# define ZOOM_PLUS 1.10
# define ZOOM_MINUS 0.95
# define TRANS (PIXEL / 2)
# define DEFAULT_COLOR YELLOW

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
# define MAGENTA 0xFF00FF
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define LIGHT_KAKI 0xA9C994

//keyboard
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define ESC 65307
# define SPACE 32
# define KEY_Q 113
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
