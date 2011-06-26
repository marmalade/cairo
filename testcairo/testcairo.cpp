#include <stdio.h>
#include <time.h>
#include "s3e.h"
#include "cairo.h"

void fillScreen(uint8 r, uint8 g, uint8 b)
{
	uint64 t = s3eTimerGetMs();
	//s3eSurfaceSetup(S3E_SURFACE_PIXEL_TYPE_BGRX888,0,0,S3E_SURFACE_BLIT_DIR_NATIVE);
    uint32* screen = (uint32*)s3eSurfacePtr();
    //uint32 colour = s3eSurfaceConvertRGB(r, g, b);

	int32 width = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
    int32 height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);
    int32 pitch = s3eSurfaceGetInt(S3E_SURFACE_PITCH);

	cairo_surface_t *srcsf = cairo_image_surface_create_from_png("634.png");
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create_for_data ((unsigned char *)screen, CAIRO_FORMAT_RGB24, width, height, pitch);
	cr = cairo_create (surface);

    //for (int y = 0; y < height; y++)
    //    for (int x = 0; x < width; x++)
    //        screen[y * pitch / 4 + x] = colour;

	cairo_set_source_rgba (cr, r*1.0/256., g*1.0/256., b*1.0/256., 1.0);
    cairo_paint (cr);
	cairo_set_source_surface(cr,srcsf,0,0);
    cairo_paint (cr);
	cairo_set_source_rgba (cr, 0, 0, 0, 0.8);
	cairo_set_line_width (cr, 0.02);
	//cairo_rectangle (cr, 0.25, 0.25, 0.5, 0.5);
	cairo_scale(cr,width,height);
	cairo_rectangle (cr, 0.25, 0.25, 0.5, 0.5);
	//cairo_fill (cr);
	cairo_stroke (cr);
	//cairo_set_source_rgba (cr, 0, 0, 0, 1.0);

	cairo_destroy (cr);
	cairo_surface_destroy (surface);
	cairo_surface_destroy (srcsf);
	t -= s3eTimerGetMs();
    s3eDebugPrintf(0, 10, false, "%ld", -(int64)t);
	s3eSurfaceShow();
}


int main()
{
    s3eDebugTraceLine("in main");
#ifdef FLOAT_WORDS_BIGENDIAN
    s3eDebugTraceLine("BIG");
#else
    s3eDebugTraceLine("NOT BIG");
#endif

	int32 width = s3eSurfaceGetInt(S3E_SURFACE_WIDTH);
    int32 height = s3eSurfaceGetInt(S3E_SURFACE_HEIGHT);

	uint32 *screen_rgb = new uint32[width * height];
	s3eSurfaceSetup(S3E_SURFACE_PIXEL_TYPE_RGB888,sizeof(uint32)*width,screen_rgb,S3E_SURFACE_BLIT_DIR_NATIVE);
	uint64 i = 0;
    while (!s3eDeviceCheckQuitRequest())
    {
		if (i % 300 == 100) {
            fillScreen(255, 0, 0);
		} else if (i % 300 == 200) {
            fillScreen(0, 255, 0);
		} else if (i % 300 == 0) {
            fillScreen(0, 0, 255);
		}
		i++;

        s3eSurfaceShow();
        s3eDeviceYield(1);
        s3eKeyboardUpdate();
        s3ePointerUpdate();

        if (s3eKeyboardAnyKey())
            break;
        if (s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) & S3E_POINTER_STATE_PRESSED)
            break;
    }
    return 0;
}
