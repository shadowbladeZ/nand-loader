#include <stdio.h>
#include <stdlib.h>
#include <ogcsys.h>

#include "video.h"

/* Constants */
#define CONSOLE_XCOORD		20
#define CONSOLE_YCOORD		100
#define CONSOLE_WIDTH		350
#define CONSOLE_HEIGHT		300

#define MSG_XCOORD		180
#define MSG_YCOORD		190


s32 __Gui_DrawPng(void *img, u32 x, u32 y)
{
	IMGCTX   ctx = NULL;
	PNGUPROP imgProp;

	s32 ret;

	/* Select PNG data */
	ctx = PNGU_SelectImageFromBuffer(img);
	if (!ctx) {
		ret = -1;
		goto out;
	}

	/* Get image properties */
	ret = PNGU_GetImageProperties(ctx, &imgProp);
	if (ret != PNGU_OK) {
		ret = -1;
		goto out;
	}

	/* Draw image */
	Video_DrawPng(ctx, imgProp, x, y);

	/* Success */
	ret = 0;

out:
	/* Free memory */
	if (ctx)
		PNGU_ReleaseImageContext(ctx);

	return ret;
}


void Gui_InitConsole(void)
{
	/* Initialize console */
	Con_Init(CONSOLE_XCOORD, CONSOLE_YCOORD, CONSOLE_WIDTH, CONSOLE_HEIGHT);
}

void Gui_DrawBackground(void)
{
	extern char bgData[];

	/* Draw background */
	__Gui_DrawPng(bgData, 0, 0);
}

void Gui_DrawLoading(void)
{
	extern char loadingImg[];

	/* Clear screen */
	Video_Clear(COLOR_BLACK);

	/* Draw loading image */
	__Gui_DrawPng(loadingImg, MSG_XCOORD, MSG_YCOORD);
}

void Gui_DrawError(void)
{
	extern char errorImg[];

	/* Clear screen */
	Video_Clear(COLOR_BLACK);

	/* Draw error image */
	__Gui_DrawPng(errorImg, MSG_XCOORD, MSG_YCOORD);
}
