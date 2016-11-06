#ifndef CHECKHEADER_SLIB_RENDER_CANVAS
#define CHECKHEADER_SLIB_RENDER_CANVAS

#include "definition.h"

#include "engine.h"

#include "../graphics/canvas.h"
#include "../core/queue.h"
#include "../math/matrix3.h"

SLIB_RENDER_NAMESPACE_BEGIN

class RenderCanvasState;
class RenderCanvasProgram;
class RenderCanvasProgramParam;

class SLIB_EXPORT RenderCanvas : public Canvas
{
	SLIB_DECLARE_OBJECT
	
protected:
	RenderCanvas();
	
public:
	static Ref<RenderCanvas> create(const Ref<RenderEngine>& engine, sl_real width, sl_real height);
	
public:
	// override
	void save();
	
	// override
	void restore();
	
	// override
	Rectangle getClipBounds();
	
	// override
	void clipToRectangle(const Rectangle& rect);
	
	// override
	void clipToPath(const Ref<GraphicsPath>& path);
	
	// override
	void clipToRoundRect(const Rectangle& rect, const Size& radius);
	
	// override
	void clipToEllipse(const Rectangle& rect);
	
	// override
	void concatMatrix(const Matrix3& matrix);
	
	// override
	void drawText16(const String16& text, sl_real x, sl_real y, const Ref<Font>& font, const Color& color);
	
	// override
	void drawLine(const Point& pt1, const Point& pt2, const Ref<Pen>& pen);
	
	// override
	void drawLines(const Point* points, sl_uint32 countPoints, const Ref<Pen>& pen);
	
	// override
	void drawArc(const Rectangle& rect, sl_real startDegrees, sl_real sweepDegrees, const Ref<Pen>& pen);
	
	// override
	void drawRectangle(const Rectangle& rect, const Ref<Pen>& pen, const Ref<Brush>& brush);
	
	// override
	void drawRoundRect(const Rectangle& rect, const Size& radius, const Ref<Pen>& pen, const Ref<Brush>& brush);
	
	// override
	void drawEllipse(const Rectangle& rect, const Ref<Pen>& pen, const Ref<Brush>& brush);
	
	// override
	void drawPolygon(const Point* points, sl_uint32 countPoints, const Ref<Pen>& pen, const Ref<Brush>& brush, FillMode fillMode = FillMode::Alternate);
	
	// override
	void drawPie(const Rectangle& rect, sl_real startDegrees, sl_real sweepDegrees, const Ref<Pen>& pen, const Ref<Brush>& brush);
	
	// override
	void drawPath(const Ref<GraphicsPath>& path, const Ref<Pen>& pen, const Ref<Brush>& brush);
	
	
	void drawTexture(const Matrix3& transform, const Ref<Texture>& texture, const Rectangle& rectSrc, const DrawParam& param, const Color4f& color);
	
	void drawTexture(const Matrix3& transform, const Ref<Texture>& texture, const Rectangle& rectSrc, const DrawParam& param);
	
	void drawTexture(const Matrix3& transform, const Ref<Texture>& texture, const Rectangle& rectSrc, sl_real alpha = 1);
	
	void drawTexture(const Matrix3& transform, const Ref<Texture>& texture, const DrawParam& param, const Color4f& color);
	
	void drawTexture(const Matrix3& transform, const Ref<Texture>& texture, const DrawParam& param);
	
	void drawTexture(const Matrix3& transform, const Ref<Texture>& texture, sl_real alpha = 1);
	
	void drawTexture(const Rectangle& rectDst, const Ref<Texture>& texture, const Rectangle& rectSrc, const DrawParam& param, const Color4f& color);

	void drawTexture(const Rectangle& rectDst, const Ref<Texture>& texture, const Rectangle& rectSrc, const DrawParam& param);
	
	void drawTexture(const Rectangle& rectDst, const Ref<Texture>& texture, const Rectangle& rectSrc, sl_real alpha = 1);
	
	void drawTexture(const Rectangle& rectDst, const Ref<Texture>& texture, const DrawParam& param, const Color4f& color);
	
	void drawTexture(const Rectangle& rectDst, const Ref<Texture>& texture, const DrawParam& param);
	
	void drawTexture(const Rectangle& rectDst, const Ref<Texture>& texture, sl_real alpha = 1);
	
protected:
	// override
	void onDraw(const Rectangle& rectDst, const Ref<Drawable>& src, const Rectangle& rectSrc, const DrawParam& param);
	
	// override
	void onDrawAll(const Rectangle& rectDst, const Ref<Drawable>& src, const DrawParam& param);
	
protected:
	// override
	void _setAlpha(sl_real alpha);
	
	// override
	void _setAntiAlias(sl_bool flag);
	
	void _drawBitmap(const Rectangle& rectDst, Bitmap* src, const Rectangle& rectSrc, const DrawParam& param);
	
protected:
	Ref<RenderEngine> m_engine;
	sl_real m_width;
	sl_real m_height;
	Matrix3 m_matViewport;
	Ref<RenderCanvasState> m_state;
	Stack< Ref<RenderCanvasState> > m_stackStates;
	
};

SLIB_RENDER_NAMESPACE_END

#endif
