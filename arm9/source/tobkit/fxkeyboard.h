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

#ifndef FXKEYBOARD_H
#define FXKEYBOARD_H

#include "tobkit/widget.h"
#include "fxbutton.h"
#include "tobkit/gui.h"
#include "tobkit/button.h"

#define FXKEYBOARD_WIDTH			13 * 16 + 16 // extra space to occlude the piano
#define FXKEYBOARD_HEIGHT			31 		+ 9

#define FXKEYBOARD_LMARGIN			8
#define FXKEYBOARD_YMARGIN			12

#define NUM_FXKEYS					15

namespace tobkit {

	
class FXKeyboard: public Widget {
	public:
		FXKeyboard(u8 _x, u8 _y, u16 **_vram, bool _visible=true);
	
		~FXKeyboard();

		
		// Drawing request
		void pleaseDraw(void);
		static void dummy(void) { };
		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
		void penMove(u8 x, u8 y);
		void buttonPress(u16 button);
		
		void setCaption(const char *caption);
		void setCategory(u8 newcat);
		void setTheme(Theme *theme_, u16 bgcolor_);
		// void reveal(void);
		// void show(void);
		void hide(void);
	private:
		FXButton *fx0, *fx1, *fx2, *fx3, *fx4, *fx5, *fx6, *fx7, *fx8, *fx9, *fxa, *fxb, *fxc, *fxd, *fxf;
		std::vector<FXButton*> fxbuttons = { fx0, fx1, fx2, fx3, fx4, fx5, fx6, fx7, fx8, fx9, fxa, fxb, fxc, fxd, fxf };
		std::vector<const char*> fxlabels = { "00G+", "11H-", "22KD", "33LL", "44PM", "55RP", "66TR", "77XS", "88 U", "99 V", "aa ", "bb ", "cc ", "dd ", "ff ",};
		void draw(void);
		char *caption;
		GUI gui;
};

};

#endif
