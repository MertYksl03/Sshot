#include "take_ss_x.h"

XImage* take_screenshot(int *out_w, int *out_h) {
    Display *display = XOpenDisplay(NULL);
    Window root = DefaultRootWindow(display);

    XWindowAttributes attrs;
    XGetWindowAttributes(display, root, &attrs);
    *out_w = attrs.width;
    *out_h = attrs.height;

    XImage *img = XGetImage(display, root, 0, 0, attrs.width, attrs.height,
                            AllPlanes, ZPixmap);
    XCloseDisplay(display);
    return img; // pixels are in img->data
}

SDL_Surface* take_ss_x11() {
    int width, height;
    XImage *ximage = take_screenshot(&width, &height);
    if (!ximage) return NULL;

    // Map X11 color masks to the closest SDL3 pixel format.
    SDL_PixelFormat fmt;

    if (ximage->bits_per_pixel == 32) {
        if (ximage->red_mask == 0x00FF0000)
            fmt = SDL_PIXELFORMAT_XRGB8888;  // common on little-endian (BGRx wire)
        else if (ximage->red_mask == 0x000000FF)
            fmt = SDL_PIXELFORMAT_XBGR8888;
        else
            fmt = SDL_PIXELFORMAT_XRGB8888;  // fallback
    } else if (ximage->bits_per_pixel == 24) {
        fmt = (ximage->red_mask == 0xFF0000)
            ? SDL_PIXELFORMAT_RGB24
            : SDL_PIXELFORMAT_BGR24;
    } else {
        SDL_Log("XImage_to_SDL_Surface: unsupported bpp %d", ximage->bits_per_pixel);
        return NULL;
    }

    SDL_Surface *surface = SDL_CreateSurface(width, height, fmt);
    if (!surface) {
        SDL_Log("SDL_CreateSurface failed: %s", SDL_GetError());
        return NULL;
    }

    if (!SDL_LockSurface(surface)) {
        SDL_Log("SDL_LockSurface failed: %s", SDL_GetError());
        SDL_DestroySurface(surface);
        return NULL;
    }

    int src_stride = ximage->bytes_per_line;
    int dst_stride = surface->pitch;
    int row_bytes  = (ximage->bits_per_pixel / 8) * width;

    for (int y = 0; y < height; y++) {
        const Uint8 *src = (const Uint8 *)ximage->data + y * src_stride;
        Uint8       *dst = (Uint8 *)surface->pixels    + y * dst_stride;
        memcpy(dst, src, row_bytes);
    }

    SDL_UnlockSurface(surface);
    return surface;
}

