#pragma once
#include "Graphics.h"

namespace SENG
{
	class PickingTexture
	{
	public:
		PickingTexture() {}
		~PickingTexture();

		void Init(unsigned int wndW, unsigned int wndH);
		void EnableWriting();
		void DisableWriting();
		
		struct PixelNFO {
			uint32_t ObjectID = 0;
			uint32_t DrawID = 0;
			uint32_t PrimID = 0;
		};

		PixelNFO ReadPixel(uint32_t x, uint32_t y);

	private:
		GLuint m_fbo = 0;
		GLuint m_pickingTex = 0;
		GLuint m_depthTex = 0;
	};
}