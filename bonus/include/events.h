/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:39 by vfries            #+#    #+#             */
/*   Updated: 2023/09/18 04:41:36 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

// X11 masks
# define NO_EVENT_MASK				0
# define KEY_PRESS_MASK				1
# define KEY_RELEASE_MASK			2
# define BUTTON_PRESS_MASK			4
# define BUTTON_RELEASE_MASK		8
# define ENTER_WINDOW_MASK			16
# define LEAVE_WINDOW_MASK			32
# define POINTER_MOTION_MASK		64
# define POINTER_MOTION_HINT_MASK	128
# define BUTTON_1_MOTION_MASK		256
# define BUTTON_2_MOTION_MASK		512
# define BUTTON_3_MOTION_MASK		1024
# define BUTTON_4_MOTION_MASK		2048
# define BUTTON_5_MOTION_MASK		4096
# define BUTTON_MOTION_MASK			8192
# define KEY_MAP_STATE_MASK			16384
# define EXPOSURE_MASK				32768
# define VISIBILITY_CHANGE_MASK		65536
# define STRUCTURE_NOTIFY_MASK		131072
# define RESIZE_REDIRECT_MASK		262144
# define SUBSTRUCTURE_NOTIFY_MASK	524288
# define SUBSTRUCTURE_REDIRECT_MASK	1048576
# define FOCUS_CHANGE_MASK			2097152
# define PROPERTY_CHANGE_MASK		4194304
# define COLOR_MAP_CHANGE_MASK		8388608
# define OWNER_GRAB_BUTTON_MASK		16777216

// X11 events
# define KEY_PRESS			2
# define KEY_RELEASE		3
# define BUTTON_PRESS		4
# define BUTTON_RELEASE		5
# define MOTION_NOTIFY		6
# define ENTER_NOTIFY		7
# define LEAVE_NOTIFY		8
# define FOCUS_IN			9
# define FOCUS_OUT			10
# define KEY_MAP_NOTIFY		11
# define EXPOSE				12
# define GRAPHICS_EXPOSE	13
# define NO_EXPOSE			14
# define VISIBILITY_NOTIFY	15
# define CREATE_NOTIFY		16
# define DESTROY_NOTIFY		17
# define UNMAP_NOTIFY		18
# define MAP_NOTIFY			19
# define MAP_REQUEST		20
# define REPARENT_NOTIFY	21
# define CONFIGURE_NOTIFY	22
# define CONFIGURE_REQUEST	23
# define GRAVITY_NOTIFY		24
# define RESIZE_REQUEST		25
# define CIRCULATE_NOTIFY	26
# define CIRCULATE_REQUEST	27
# define PROPERTY_NOTIFY	28
# define SELECTION_CLEAR	29
# define SELECTION_REQUEST	30
# define SELECTION_NOTIFY	31
# define COLOR_MAP_NOTIFY	32
# define CLIENT_MESSAGE		33
# define MAPPING_NOTIFY		34
# define GENERIC_EVENT		35
# define LAST_EVENT			36

# if defined(__APPLE__)

enum e_mouse_buttons
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 2,
	SCROLL_DOWN = 4,
	SCROLL_UP = 5,
};
# elif defined(__linux__)

enum e_mouse_buttons
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 3,
	SCROLL_DOWN = 5,
	SCROLL_UP = 4,
};
# else
#  error "Unsuported OS"
# endif

# if defined(__APPLE__)

enum e_key_codes
{
	KEY_A = 0,
	KEY_B = 11,
	KEY_C = 8,
	KEY_D = 2,
	KEY_E = 14,
	KEY_F = 3,
	KEY_G = 5,
	KEY_H = 4,
	KEY_I = 34,
	KEY_J = 38,
	KEY_K = 40,
	KEY_L = 37,
	KEY_M = 46,
	KEY_N = 45,
	KEY_O = 31,
	KEY_P = 35,
	KEY_Q = 12,
	KEY_R = 15,
	KEY_S = 1,
	KEY_T = 17,
	KEY_U = 32,
	KEY_V = 9,
	KEY_W = 13,
	KEY_X = 7,
	KEY_Y = 16,
	KEY_Z = 6,
	KEY_ESC = 53,
	KEY_SPACE = 49,
	KEY_SLASH = 44,
	KEY_L_SHIFT = 257,
	KEY_R_SHIFT = 258,
	KEY_R_CTRL = 269,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_DOT = 47,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 41,
	KEY_COMMAND = 259,
	KEY_BACKSPACE = 51,
};
# elif defined(__linux__)

enum e_key_codes
{
	KEY_A = 97,
	KEY_B = 98,
	KEY_C = 99,
	KEY_D = 100,
	KEY_E = 101,
	KEY_F = 102,
	KEY_G = 103,
	KEY_H = 104,
	KEY_I = 105,
	KEY_J = 106,
	KEY_K = 107,
	KEY_L = 108,
	KEY_M = 109,
	KEY_N = 110,
	KEY_O = 111,
	KEY_P = 112,
	KEY_Q = 113,
	KEY_R = 114,
	KEY_S = 115,
	KEY_T = 116,
	KEY_U = 117,
	KEY_V = 118,
	KEY_W = 119,
	KEY_X = 120,
	KEY_Y = 121,
	KEY_Z = 122,
	KEY_ESC = 65307,
	KEY_SPACE = 32,
	KEY_SLASH = 47,
	KEY_L_SHIFT = 65505,
	KEY_R_SHIFT = 65506,
	KEY_R_CTRL = 65508,
	KEY_UP = 65362,
	KEY_DOWN = 65364,
	KEY_LEFT = 65361,
	KEY_RIGHT = 65363,
	KEY_DOT = 46,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 59,
	KEY_COMMAND = 65507,
	KEY_BACKSPACE = 65288,
};
# else
#  error "Unsuported OS"
# endif

#endif