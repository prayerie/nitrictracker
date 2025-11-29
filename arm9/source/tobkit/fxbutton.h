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

#ifndef FXBUTTON_H
#define FXBUTTON_H

#define GLYPH_3X5_COUNT 40
#define GLYPH_3X5(c) c - 55

#define FX_CATEGORY_NORMAL 0
#define FX_CATEGORY_E 1
#define FX_CATEGORY_FT 2
#define FX_CATEGORY_VOL 3

#include "../../arm9/fonts/font_3x5_raw.h"
#include "tobkit/widget.h"

namespace tobkit {

#define FXBUTTON_WIDTH		13
#define FXBUTTON_HEIGHT		27

class FXButton: public Widget {
	public:
		FXButton(u8 _x, u8 _y, u16 **_vram, bool _visible=true, u8 _category=0);
	
		~FXButton();
		
		// Callback registration
		void registerPushCallback(void (*onPush_)(u8 val));
		
		// Drawing request
		void pleaseDraw(void);
		
		// Event calls
		void penDown(u8 x, u8 y);
		void penUp(u8 x, u8 y);
		void penMove(u8 x, u8 y);
		void buttonPress(u16 button);
		void setCategory(u8 newcat);
		void setValue(u8 newval);

		inline bool isPenDown(void) const { return penIsDown; }
		void setCaption(const char *caption);
		void setSmallCaption(const char *small_caption);
		
	private:
		void (*onPush)(u8 val);
		bool penIsDown;
		
		void draw(u8 down);
		char *caption;
		char *small_caption;
		u8 value, category;

		inline void drawChar(u8 c, u8 cx, u8 cy, u16 col)
		{
			u8 i,j;
			for(j=0;j<5;++j) {
				for(i=0;i<3;++i) {
					u16 pixelidx = 3*GLYPH_3X5_COUNT*j+3*c+i;
					if(font_3x5_raw[pixelidx/8]&BIT(pixelidx%8)) {
						//*(*vram+SCREEN_WIDTH*(2+cy*8+j)+1+cx*4+i) = col;
						*(*vram+SCREEN_WIDTH*(y+cy+j)+x+cx+i) = col;
					}
				}
			}
		}

};

};

#endif
