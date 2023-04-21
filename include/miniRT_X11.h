/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_X11.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 10:45:39 by vfries            #+#    #+#             */
/*   Updated: 2023/04/15 10:46:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_X11_H
# define MINIRT_X11_H

// X11 masks
# define NO_EVENT_MASK				0L
# define KEY_PRESS_MASK				(1L << 0)
# define KEY_RELEASE_MASK			(1L << 1)
# define BUTTON_PRESS_MASK			(1L << 2)
# define BUTTON_RELEASE_MASK		(1L << 3)
# define ENTER_WINDOW_MASK			(1L << 4)
# define LEAVE_WINDOW_MASK			(1L << 5)
# define POINTER_MOTION_MASK		(1L << 6)
# define POINTER_MOTION_HINT_MASK	(1L << 7)
# define BUTTON_1_MOTION_MASK		(1L << 8)
# define BUTTON_2_MOTION_MASK		(1L << 9)
# define BUTTON_3_MOTION_MASK		(1L << 10)
# define BUTTON_4_MOTION_MASK		(1L << 11)
# define BUTTON_5_MOTION_MASK		(1L << 12)
# define BUTTON_MOTION_MASK			(1L << 13)
# define KEY_MAP_STATE_MASK			(1L << 14)
# define EXPOSURE_MASK				(1L << 15)
# define VISIBILITY_CHANGE_MASK		(1L << 16)
# define STRUCTURE_NOTIFY_MASK		(1L << 17)
# define RESIZE_REDIRECT_MASK		(1L << 18)
# define SUBSTRUCTURE_NOTIFY_MASK	(1L << 19)
# define SUBSTRUCTURE_REDIRECT_MASK	(1L << 20)
# define FOCUS_CHANGE_MASK			(1L << 21)
# define PROPERTY_CHANGE_MASK		(1L << 22)
# define COLOR_MAP_CHANGE_MASK		(1L << 23)
# define OWNER_GRAB_BUTTON_MASK		(1L << 24)

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

# ifdef __APPLE__

enum e_mouse_buttons
{
	BUTTON_LEFT = 1,
	BUTTON_RIGHT = 2,
};
# endif //__APPLE__

# ifdef __APPLE__

enum e_key_codes
{
	KEY_ESC = 53,
	KEY_W = 13,
	KEY_A = 0,
	KEY_S = 1,
	KEY_D = 2,
	KEY_E = 14,
	KEY_Q = 12,
	KEY_H = 4,
	KEY_SPACE = 49,
	KEY_SLASH = 44,
	KEY_L_SHIFT = 257,
	KEY_R_SHIFT = 258,
	KEY_R_CTRL = 269,
	KEY_UP = 126,
	KEY_DOWN = 125,
	KEY_LEFT = 123,
	KEY_RIGHT = 124,
	KEY_P = 35,
	KEY_V = 9,
	KEY_C = 8,
	KEY_DOT = 47,
	KEY_S_QUOTE = 39,
	KEY_SEMI_COLON = 41,
};
# endif //__APPLE__

#endif //MINIRT_X11_H
