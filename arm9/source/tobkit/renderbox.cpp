#include "renderbox.h"

#include <nds.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "../tools.h"
#include "ntxm/instrument.h"
#include "ntxm/fifocommand.h"
#include "ntxm/ntxmtools.h"

using namespace tobkit;

RenderBox::RenderBox(u16 **_vram, void (*_onOk)(void), void (*_onBufferSwap)(void), void (*_playSong)(void), void (*_onStart)(void), void (*_onCancel)(void), Sample *_sample, Instrument *_instrument,
			   u8 _smpidx, u32 _render_ms, bool ptnn)
	:Widget((SCREEN_WIDTH-RENDERBOX_WIDTH)/2, (SCREEN_HEIGHT-RENDERBOX_HEIGHT)/2,
		RENDERBOX_WIDTH, RENDERBOX_HEIGHT, _vram, true),
  	recording(false), btndown(false), startbtndown(false), onOk(_onOk), onBufferSwap(_onBufferSwap), playSong(_playSong), onCancel(_onCancel), sample(_sample),
	instrument(_instrument), smpidx(_smpidx), sound_data(NULL), render_ms(_render_ms)
{
	title = "render to sample";
	soundSetFreq(1, RENDERBOX_SAMPLING_FREQ);
	//soundSetFreq(3, RENDERBOX_SAMPLING_FREQ);
	const char *msg = "press a";
	u8 msgwidth = getStringWidth(msg);
	labelmsg = new Label(x+(RENDERBOX_WIDTH-msgwidth)/2, y+18, msgwidth+5, 12, _vram, false);
	labelmsg->setCaption(msg);
	
	if (ptnn)
	{
		msg = "to render pattern";
		msgwidth = getStringWidth(msg);
		labelmsg2 = new Label(x+(RENDERBOX_WIDTH-msgwidth)/2, y+30, msgwidth+5, 12, _vram, false);
		labelmsg2->setCaption(msg);
	}
	else
	{
		msg = "to render selection";
		msgwidth = getStringWidth(msg);
		labelmsg2 = new Label(x+(RENDERBOX_WIDTH-msgwidth)/2, y+30, msgwidth+5, 12, _vram, false);
		labelmsg2->setCaption(msg);
	}
	
	msg = "capturing!";
	msgwidth = getStringWidth(msg);
	labelrec = new Label(x+(RENDERBOX_WIDTH-msgwidth)/2, y+33, msgwidth+5, 12, _vram, false, false, true);
	labelrec->setCaption(msg);
	labelrec->hide();
	
	buttoncancel = new Button(x+(RENDERBOX_WIDTH-50)/2 + 30, y+44, 50, 14, _vram);
	buttoncancel->setCaption("cancel");
	buttoncancel->registerPushCallback(_onCancel);

	buttonstart = new Button(x+(RENDERBOX_WIDTH-50)/2 - 30, y+44, 50, 14, _vram);
	buttonstart->setCaption("start");
	buttonstart->registerPushCallback(_onStart);

	buttonpattern = new Button(x+(RENDERBOX_WIDTH-50)/2, y+44, 50, 14, _vram);
	buttonpattern->setCaption("  ptn  ");

	stop = false;
}

RenderBox::~RenderBox(void)
{
	if(sound_data)
		{
			ntxm_free(sound_data);
			sound_data = 0;
		}

	delete labelmsg;
	delete labelmsg2;
	delete labelrec;
	delete buttoncancel;
	delete buttonstart;
	delete buttonpattern;
}

void RenderBox::pleaseDraw(void)
{
	draw();
}

void RenderBox::penDown(u8 px, u8 py)
{
	u8 bx, by, bw, bh;
	u8 bx2, by2, bw2, bh2;
	u8 bx3, by3, bw3, bh3;
	
	buttoncancel->getPos(&bx, &by, &bw, &bh);
	buttonstart->getPos(&bx2, &by2, &bw2, &bh2);
	// buttonpattern->getPos(&bx3, &by3, &bw3, &bh3);
	if((px >= bx)&&(px <= bx+bw)&&(py >= by)&&(py <= by+bh))
	{
		buttoncancel->penDown(px, py);
		btndown = true;
	}
	if((px >= bx2)&&(px <= bx2+bw2)&&(py >= by2)&&(py <= by2+bh2))
	{
		buttonstart->penDown(px, py);
		startbtndown = true;
	}
	// if((px >= bx3)&&(px <= bx3+bw3)&&(py >= by3)&&(py <= by3+bh3))
	// {
	// 	buttonpattern->penDown(px, py);
	// 	ptnbuttondown = true;
	// }
}

void RenderBox::penUp(u8 px, u8 py)
{
	if(btndown == true)
	{
		btndown = false;
		buttoncancel->penUp(px, py);
	}
	if(startbtndown == true)
	{
		startbtndown = false;
		buttonstart->penUp(px, py);
	}
	// if(ptnbuttondown == true)
	// {
	// 	ptnbuttondown = false;
	// 	buttonpattern->penUp(px, py);
	// }
}

void RenderBox::buttonPress(u16 button)
{
	if(button & KEY_A)
		startRecording();
}

void RenderBox::buttonRelease(u16 button)
{

}

Sample *RenderBox::getSample(void)
{
	return sample;
}

void RenderBox::setTheme(Theme *theme_, u16 bgcolor_)
{
	theme = theme_;
	bgcolor=bgcolor_;
	labelmsg->setTheme(theme, theme->col_light_bg);
	labelmsg2->setTheme(theme, theme->col_light_bg);
	labelrec->setTheme(theme, theme->col_light_bg);
	buttoncancel->setTheme(theme, theme->col_light_bg);
	buttonstart->setTheme(theme, theme->col_light_bg);
	//buttonpattern->setTheme(theme, theme->col_light_bg);
	labelmsg->reveal();
	labelmsg2->reveal();
	labelrec->reveal();
	buttoncancel->reveal();
	buttonstart->reveal();
	//buttonpattern->reveal();
}

void RenderBox::draw(void)
{
	drawGradient(theme->col_dark_ctrl, theme->col_light_ctrl, 1, 1, width - 2, 15);
	drawHLine(1, 16, width - 2, theme->col_outline);
	if(recording==true)
	{
		drawFullBox(1, 17, width - 2, RENDERBOX_HEIGHT-18, RGB15(20, 10, 31) | BIT(15));
		labelmsg->setTheme(theme, RGB15(10, 0, 31) | BIT(15));
		labelmsg2->setTheme(theme, RGB15(10, 0, 31) | BIT(15));
		buttoncancel->setTheme(theme, RGB15(10, 0, 31) | BIT(15));
		labelrec->show();
		labelmsg->hide();
		labelmsg2->hide();
		buttoncancel->hide();
		buttonstart->hide();
	}
	else
	{
		drawFullBox(1, 17, width - 2, RENDERBOX_HEIGHT-18, theme->col_light_bg);
		labelrec->hide();
		labelmsg->show();
		labelmsg2->show();
		buttoncancel->show();
		buttonstart->show();
		buttonpattern->show();
		buttoncancel->pleaseDraw();
		buttonstart->pleaseDraw();
		//buttonpattern->pleaseDraw();
	}
	drawBorder(theme->col_outline);
	
	u8 titlewidth = getStringWidth(title)+5;
	drawString(title, (RENDERBOX_WIDTH-titlewidth)/2, 2, theme->col_text, titlewidth+5);
	
	labelmsg->pleaseDraw();
	labelmsg2->pleaseDraw();
	labelrec->pleaseDraw();
}



void RenderBox::startRecording(void)
{
	u32 ms = render_ms;
    if(!recording)
    {
        if(sample != NULL)
            instrument->setSample(smpidx, NULL);

        if(sound_data)
            ntxm_free(sound_data);
        
        u32 n_samples = ((RENDERBOX_SAMPLING_FREQ) * render_ms) / 1000;
        
        u32 *capture_buffer = (u32*)ntxm_cmalloc(n_samples * sizeof(s16));
        if(!capture_buffer)
            return;
        
        sound_data = (s16*)ntxm_cmalloc(n_samples * sizeof(s16));
        if(!sound_data)
        {
            ntxm_free(capture_buffer);
            return;
        }

        recording = true;

        playSong();
        
        soundCaptureStart(capture_buffer, n_samples / 2, 0, false, true, false,
                          SoundCaptureFormat_16Bit);
        // 
        for (u32 i = 0; i < (ms * 60) / 1000; ++i)
        {
			if (stop)
			{
				stopRecording(capture_buffer, n_samples);
				return;
			} else {
				draw();
				onBufferSwap();
			}
            
			
        }
        
        stopRecording(capture_buffer, n_samples);
    }
}

void RenderBox::stopRecording(u32 *buf, u32 n_s)
{	
	soundCaptureStop(0);
	DC_FlushAll();

	s16 *wave_buf = (s16*)memUncached(buf);
	s16 *dest = (s16*)sound_data;
	
	for (u32 i = 0; i < sizeof(s16) * n_s; i++)
	{
		dest[i] = wave_buf[i];
	}
	
	ntxm_free(buf);
	
	recording = false;
	DC_FlushAll();
	
	sample = new Sample((void*)sound_data, n_s / 2, RENDERBOX_SAMPLING_FREQ, true);
	//sound_data = NULL;

	sample->setName("rendered");
	
	DC_FlushAll();
	
	onOk();
}