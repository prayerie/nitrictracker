/*====================================================================
Copyright 2006 Tobias Weyand

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    https://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
======================================================================*/

#include "tobkit/theme.h"

Theme::Theme(void)
{
	// Set default colors
	col_bg                  = RGB15(4,6,15)|BIT(15);
	col_dark_bg             = col_bg;
	col_medium_bg           = RGB15(9,11,17)|BIT(15);
	col_light_bg            = RGB15(16,18,24)|BIT(15);
	col_lighter_bg          = RGB15(23,25,31) | BIT(15);
	col_light_ctrl          = RGB15(31,31,0)|BIT(15); // RGB15(26,26,26)|BIT(15)
	col_dark_ctrl           = RGB15(31,18,0)|BIT(15); // RGB15(31,31,31)|BIT(15)
	col_light_ctrl_disabled = col_light_bg;
	col_dark_ctrl_disabled  = col_medium_bg;
	col_list_highlight1     = RGB15(28,15,0)|BIT(15);
	col_list_highlight2     = RGB15(28,28,0)|BIT(15);
	col_outline             = RGB15(0,0,0)|BIT(15);
	col_sepline             = RGB15(31,31,0)|BIT(15);
	col_icon                = RGB15(0,0,0)|BIT(15);
	col_text                = RGB15(0,0,0)|BIT(15);
	col_signal              = RGB15(31,0,0)|BIT(15);
	// patternview stuff
	cb_col1					= col_bg;
	cb_col2					= col_medium_bg;
	cb_col1_highlight		= col_light_bg;
	cb_col2_highlight		= col_medium_bg;
	col_lines				= col_lighter_bg;
	col_sublines			= col_light_bg;
	col_row_number			= col_light_ctrl;
}

Theme::Theme(int theme) {
	switch (theme) {
	
	case 3:
	{
		col_bg                  = RGB15(9, 4, 15)|BIT(15);
		col_dark_bg             = col_bg;
		col_medium_bg           = RGB15(12, 9, 17)|BIT(15);
		col_light_bg            = RGB15(19, 16, 24)|BIT(15);
		col_lighter_bg          = RGB15(26, 23, 31)|BIT(15);
		col_light_ctrl          = RGB15(9,31,0)|BIT(15); // RGB15(26,26,26)|BIT(15)
		col_dark_ctrl           = RGB15(22,31,0)|BIT(15); // RGB15(31,31,31)|BIT(15)
		col_light_ctrl_disabled = col_light_bg;
		col_dark_ctrl_disabled  = col_medium_bg;
		col_list_highlight1     = RGB15(21, 28, 0)|BIT(15);
		col_list_highlight2     = RGB15(8, 28, 0)|BIT(15);
		col_outline             = RGB15(0,0,0)|BIT(15);
		col_sepline             = RGB15(9, 31, 0)|BIT(15);
		col_icon                = RGB15(0,0,0)|BIT(15);
		col_text                = RGB15(0,0,0)|BIT(15);
		col_signal				= RGB15(31, 21, 0)|BIT(15);

		cb_col1					= col_bg;
		cb_col2					= col_medium_bg;
		cb_col1_highlight		= col_light_bg;
		cb_col2_highlight		= col_medium_bg;
		col_lines				= col_lighter_bg;
		col_sublines			= col_light_bg;
		col_row_number			= col_light_ctrl;
		break;
	}
	case 2:
	{
		col_bg                  = RGB15(0, 0, 0)|BIT(15);
		col_dark_bg             = col_bg;
		col_medium_bg           = RGB15(0, 4, 0)|BIT(15);
		col_light_bg            = RGB15(0, 1, 0)|BIT(15);
		col_lighter_bg          = RGB15(0, 4, 0)|BIT(15);
		col_light_ctrl          = RGB15(0,7,0)|BIT(15); // RGB15(26,26,26)|BIT(15)
		col_dark_ctrl           = RGB15(0,3,0)|BIT(15); // RGB15(31,31,31)|BIT(15)
		col_light_ctrl_disabled = col_light_bg;
		col_dark_ctrl_disabled  = col_medium_bg;
		col_list_highlight1     = RGB15(0,15,0)|BIT(15);
		col_list_highlight2     = RGB15(8,28,8)|BIT(15);
		col_outline             = RGB15(6,13,3)|BIT(15);
		col_sepline             = RGB15(29,31,23)|BIT(15);
		col_icon                = RGB15(6,13,3)|BIT(15);
		col_text                = RGB15(6,13,3)|BIT(15);
		col_signal				= RGB15(31, 0, 0) | BIT(15);
		cb_col1					= col_bg;
		cb_col2					= col_medium_bg;
		cb_col1_highlight		= col_light_bg;
		cb_col2_highlight		= col_medium_bg;
		col_lines				= col_lighter_bg;
		col_sublines			= col_light_bg;
		col_row_number			= col_light_ctrl;
		break;
	}
	case 1: {
		col_bg                  = RGB15(17, 28, 28)|BIT(15);
		col_dark_bg             = col_bg;
		col_medium_bg           = RGB15(24, 27, 27)|BIT(15);
		col_light_bg            = RGB15(28, 31, 31)|BIT(15);
		col_lighter_bg          = RGB15(29, 27, 28)|BIT(15);
		col_light_ctrl          = RGB15(31, 26, 29)|BIT(15); // RGB15(26,26,26)|BIT(15)
		col_dark_ctrl           = RGB15(29, 24, 27)|BIT(15); // RGB15(31,31,31)|BIT(15)
		col_light_ctrl_disabled = col_light_bg;
		col_dark_ctrl_disabled  = col_medium_bg;
		col_list_highlight1     = RGB15(31, 25, 25)|BIT(15);
		col_list_highlight2     = RGB15(31, 31, 25)|BIT(15);
		col_outline             = RGB15(14, 23, 23)|BIT(15);
		col_sepline             = col_light_ctrl;
		col_icon                = RGB15(18, 0, 31)|BIT(15);
		col_text                = RGB15(31, 11, 30)|BIT(15);
		col_signal 				= RGB15(31, 0, 0) | BIT(15);
		cb_col1					= col_bg;
		cb_col2					= col_medium_bg;
		cb_col1_highlight		= col_light_bg;
		cb_col2_highlight		= col_medium_bg;
		col_lines				= col_lighter_bg;
		col_sublines			= col_light_bg;
		col_row_number			= col_light_ctrl;
		break;
	}
	default:
	{
		col_bg                  = RGB15(4,6,15)|BIT(15);
		col_dark_bg             = col_bg;
		col_medium_bg           = RGB15(9,11,17)|BIT(15);
		col_light_bg            = RGB15(16,18,24)|BIT(15);
		col_lighter_bg          = RGB15(23,25,31) | BIT(15);
		col_light_ctrl          = RGB15(31,31,0)|BIT(15); // RGB15(26,26,26)|BIT(15)
		col_dark_ctrl           = RGB15(31,18,0)|BIT(15); // RGB15(31,31,31)|BIT(15)
		col_light_ctrl_disabled = col_light_bg;
		col_dark_ctrl_disabled  = col_medium_bg;
		col_list_highlight1     = RGB15(28,15,0)|BIT(15);
		col_list_highlight2     = RGB15(28,28,0)|BIT(15);
		col_outline             = RGB15(0,0,0)|BIT(15);
		col_sepline             = RGB15(31,31,0)|BIT(15);
		col_icon                = RGB15(0,0,0)|BIT(15);
		col_text                = RGB15(0,0,0)|BIT(15);
		col_signal 				= RGB15(31, 0, 0) | BIT(15);
		cb_col1					= col_bg;
		cb_col2					= col_medium_bg;
		cb_col1_highlight		= col_light_bg;
		cb_col2_highlight		= col_medium_bg;
		col_lines				= col_lighter_bg;
		col_sublines			= col_light_bg;
		col_row_number			= col_light_ctrl;
		break;
	}
	}
}
