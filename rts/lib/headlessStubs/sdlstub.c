/* This file is part of the Spring engine (GPL v2 or later), see LICENSE.html */

/*
 * documentation for the functions in this file can be found at:
 * http://www.libsdl.org/docs/html/
 */

#include <SDL3/SDL.h>


#ifdef __cplusplus
extern "C" {
#endif

// sdlstub.c — SDL3 headless stubs with 100% signature compatibility
// All comments in English as requested.

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_audio.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_version.h>

static const char* g_stub_error = "SDL3 headless stub: operation not supported";

// --------------------
// Error handling
// --------------------
SDL_DECLSPEC const char* SDLCALL SDL_GetError(void)
{
    // Return a static message; real SDL would maintain per-thread error strings.
    return g_stub_error;
}

SDL_DECLSPEC void SDLCALL SDL_ClearError(void)
{
    // No-op in the stub.
}

// --------------------
// Version information
// --------------------
SDL_DECLSPEC int SDLCALL SDL_GetVersion(void)
{
    // Return a plausible linked version; here we mirror the headers' compile-time version.
    return SDL_VERSION; // equals SDL_VERSIONNUM(SDL_MAJOR_VERSION, SDL_MINOR_VERSION, SDL_MICRO_VERSION)
}

// --------------------
// Initialization / shutdown
// --------------------
SDL_DECLSPEC bool SDLCALL SDL_Init(Uint32 flags)
{
    (void)flags;
    // Pretend initialization succeeded.
    return true;
}

SDL_DECLSPEC void SDLCALL SDL_Quit(void)
{
    // No-op.
}

// --------------------
// Displays & display modes
// --------------------
SDL_DECLSPEC SDL_DisplayID* SDLCALL SDL_GetDisplays(int* count)
{
    // Headless: no real displays available.
    if (count) *count = 0;
    return NULL;
}

SDL_DECLSPEC SDL_DisplayID SDLCALL SDL_GetPrimaryDisplay(void)
{
    // Headless: return 0 as "no display".
    return 0;
}

SDL_DECLSPEC SDL_DisplayID SDLCALL SDL_GetDisplayForWindow(SDL_Window* window)
{
    // Headless: no real window/display mapping.
    (void)window;
    return 0;
}

SDL_DECLSPEC const SDL_DisplayMode* SDLCALL SDL_GetDesktopDisplayMode(SDL_DisplayID displayID)
{
    (void)displayID;

    // Provide a stable static mode; adjust to your needs.
    static SDL_DisplayMode mode;
    mode.w            = 640;
    mode.h            = 480;
    mode.refresh_rate = 100.0f;                 // SDL3 uses float for Hz
    mode.format       = SDL_PIXELFORMAT_RGB24;  // or SDL_PIXELFORMAT_XRGB8888
    return &mode;
}

SDL_DECLSPEC const SDL_DisplayMode* SDLCALL SDL_GetWindowFullscreenMode(SDL_Window* window)
{
    // No fullscreen mode in headless; return NULL so callers can branch.
    (void)window;
    return NULL;
}

SDL_DECLSPEC bool SDLCALL SDL_SetWindowFullscreenMode(SDL_Window* window, const SDL_DisplayMode* mode)
{
    // No-op; pretend success to keep higher-level logic simple.
    (void)window; (void)mode;
    return true;
}

// --------------------
// Window lifecycle & state
// --------------------
SDL_Window* SDLCALL SDL_CreateWindow(const char* title, int w, int h, Uint32 flags)
{
    (void)title; (void)w; (void)h; (void)flags;
    // Headless: do not create a real window; return NULL so engine can skip window paths.
    return NULL;
}

DECLSPEC void SDLCALL SDL_DestroyWindow(SDL_Window* window)
{
    (void)window;
}

DECLSPEC void SDLCALL SDL_SetWindowPosition(SDL_Window* window, int x, int y)
{
    (void)window; (void)x; (void)y;
}

DECLSPEC bool SDLCALL SDL_SetWindowFullscreen(SDL_Window* window, bool fullscreen)
{
    (void)window; (void)fullscreen;
    // Pretend success for both enabling and disabling fullscreen.
    return true;
}

DECLSPEC bool SDLCALL SDL_SetWindowBordered(SDL_Window* window, bool bordered)
{
    (void)window; (void)bordered;
    // Pretend success; border changes are meaningless in headless mode.
    return true;
}

// --------------------
// Input grabbing (mouse/keyboard)
// --------------------
DECLSPEC bool SDLCALL SDL_GetWindowMouseGrab(SDL_Window* window)
{
    (void)window;
    return false;
}

DECLSPEC bool SDLCALL SDL_SetWindowMouseGrab(SDL_Window* window, bool grabbed)
{
    (void)window; (void)grabbed;
    return true;
}

DECLSPEC bool SDLCALL SDL_GetWindowKeyboardGrab(SDL_Window* window)
{
    (void)window;
    return false;
}

DECLSPEC bool SDLCALL SDL_SetWindowKeyboardGrab(SDL_Window* window, bool grabbed)
{
    (void)window; (void)grabbed;
    return true;
}

// --------------------
// OpenGL context
// --------------------
DECLSPEC SDL_GLContext* SDLCALL SDL_GL_CreateContext(SDL_Window* window)
{
    (void)window;
    // No GL in headless; return NULL so callers skip GL code paths.
    return NULL;
}

DECLSPEC void SDLCALL SDL_GL_DestroyContext(SDL_GLContext* context)
{
    (void)context;
}

DECLSPEC bool SDLCALL SDL_GL_GetSwapInterval(int* interval)
{
    if (interval) *interval = 0; // immediate (no vsync)
    return true;                 // pretend the query succeeded
}

// If you also call SDL_GL_MakeCurrent / SDL_GL_SwapWindow in headless,
// you can add no-op stubs here with matching signatures as needed.

// --------------------
// Optional: minimal hints (often used in setup code)
// --------------------
DECLSPEC bool SDLCALL SDL_SetHint(const char* name, const char* value)
{
    (void)name; (void)value;
    return true;
}

DECLSPEC const char* SDLCALL SDL_GetHint(const char* name)
{
    (void)name;
    return NULL;
}


#ifdef __cplusplus
} // extern "C"
#endif
