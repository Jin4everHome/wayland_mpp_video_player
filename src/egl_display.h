#ifndef __EGL_DISPLAY_OUTPUT_H__
#define __EGL_DISPLAY_OUTPUT_H__

#include <assert.h> // TODO;

#include <wayland-client.h>
#include <wayland-egl.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include "xdg-shell-client-protocol.h"


#include <rockchip/rk_mpi.h>

namespace {

#define MAX_BUFFER_COUNT 24

#define EGL_CALL(func_call)              \
  do {                                   \
    func_call;                           \
    assert(eglGetError() == EGL_SUCCESS);\
  } while(0)

#define GL_CALL(func_call)               \
  do {                                   \
    func_call;                           \
    assert(glGetError() == GL_NO_ERROR);\
  } while(0)

} // namespace

struct Geometry {
    int width, height;
};


class EGLDisplayOut
{
public:
	EGLDisplayOut();
	EGLDisplayOut(int num_buffer);
	~EGLDisplayOut();

	int initDisplay(int width, int height, int numOfBuffer = 0);
	int Render(MppFrame frame);
	int deinitDisplay();

	struct wl_compositor *GetCompositor() const {return mWLCompositor;}
	struct wl_shell *GetShell() const {return mWLShell;}

	void SetCompositor(struct wl_compositor * compositor);
	void SetShell(struct wl_shell * compositor);
	void SetGeomertyWindowSize(int width, int height);
	void SetWMBase(struct xdg_wm_base *wm_base) { mWMBase = wm_base; }
	void SetSeat(struct wl_seat *seat) { mWLSeat = seat; }

	void WaitConfigureDone() { mWaitForConfigure = false; }

	struct wl_egl_window *GetWLEGLWindow() const { return mWLEGLWindow; }
	struct xdg_wm_base *GetWMBase() const {return mWMBase; }
	struct wl_seat *GetSeat( ) const {return mWLSeat; }

	Geometry& GetGeoMetry() {return mGeometry; }
	int mRunning = false;
	struct xdg_wm_base *mWMBase = nullptr; // wm_base;

	bool mIsFullScreenMode = false;
	bool mIsMaximizeMode = false;
	Geometry mGeometry, mWindowSize;

private:
	bool mWaitForConfigure = false;
	bool mGLInitDone = false;

	int mBufferCnt;
	int mBufferSize;

	struct GL {
	        GLuint program;
	        unsigned int vbo;
	        unsigned int vbo_valid;
	        unsigned int mvp_transform_uniform;
	        unsigned int texcoord_scale_translate_uniforms;
	        unsigned int texture_uniforms;
	};

	GL mGL;

	struct wl_display *mWLDisplay;
	struct wl_registry *mWLRegistry;
	struct wl_compositor *mWLCompositor;
	struct wl_shell *mWLShell; // deprecated...
	struct wl_seat *mWLSeat;
	struct wl_keyboard *mWLKeyboard;

	struct xdg_surface *mXDGSurface; // xdg_surface;
	struct xdg_toplevel *mXDGToplevel; // xdg_toplevel;

	PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC mSwapBuffersWithDamage; //swap_buffers_with_damage;

	struct wl_surface *mWLSurface;
	struct wl_shell_surface *mWLShellSurface;
	struct wl_egl_window *mWLEGLWindow;

	EGLDisplay mEGLDisplay;
	EGLContext mEGLContext;
	EGLSurface mEGLSurface;
	EGLConfig mEGLConfig;

	GLuint       mTextureID[MAX_BUFFER_COUNT];
	EGLImageKHR  mEGLImage[MAX_BUFFER_COUNT];
	GLuint       gl_fbo_[MAX_BUFFER_COUNT];
	GLuint       gl_rbo_[MAX_BUFFER_COUNT];
	uint32_t last_resolution_[MAX_BUFFER_COUNT];

	int RenderInternal(MppFrame frame);
	int DrawFrame(int index);

	int deinitDisplayInternal();

	int initEGL();
	int deinitEGL();

	int deinitWL();

	int initGL();
	int deinitGL();

	int createShellSurface();

	uint32_t getVBO();
	GLuint createShader(const char *source, GLenum shader_type);

	float mColor = 1.0f;
	void drawTest();

	/* Debug only */
	int64_t debug_time_ = 0LL;
	int64_t debug_totoal_duration_ = 0LL;
	int64_t debug_average_duration_ = 0LL;
	int debug_test_count_ = 0;
};

#endif

