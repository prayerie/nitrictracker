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
	col_bg                  = RGB15(25, 6, 16)|BIT(15);
	col_dark_bg             = col_bg;
	col_medium_bg           = RGB15(19, 10, 19)|BIT(15);
	col_light_bg            = RGB15(25, 16, 21)|BIT(15);
	col_lighter_bg          = RGB15(25, 16, 23)|BIT(15);
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
}
