#ifndef __PX_TEX_OGL_H__
#define __PX_TEX_OGL_H__

#include "ShaderOGL.h"
#include "GraphicDesc.h"
#include <PhBase/PhBase.h>

namespace ph
{
	GLenum TexFilter2GL( TEX_FILTER filter );
	GLenum TexAddress2GL( TEX_ADDRESS addr );
    struct Image
    {
        uint16_t    nWidth;
        uint16_t    nHeight;
        uint8_t *   pData;
        void Release();
		static Image * ImageWithPNG( IBlob * );
    };

    class TexOGL
    {
	public:
        GLuint 					tex;
		PxTexDesc				desc;
	public:
        static TexOGL * CreateTexFromPNG( const char * _image );
        static TexOGL * CreateTexFromPNG( const Image * _image );
		static TexOGL * CreateTexEmpty( PIXEL_FORMAT _format, PhU16 _width, PhU16 _height );
		static TexOGL * CreateTexAlpha8(PhU16 _width, PhU16 _height);
		static TexOGL * CreateTexDepthStencil(PhU16 _width, PhU16 _height);
		static TexOGL * CreateTexStencil(PhU16 _width, PhU16 _height);
        static TexOGL * CreateWhiteTex();
	public:
		const PxTexDesc * GetDesc();
		void BindToActivedSlot();
        void BufferSubData( int _x, int _y, int _w, int _h, unsigned char * _data );
        void GenMipmap();
        void Release();
    };

	typedef std::shared_ptr<TexOGL> TexOGLRef;
}

#endif // __PX_TEX_H__
