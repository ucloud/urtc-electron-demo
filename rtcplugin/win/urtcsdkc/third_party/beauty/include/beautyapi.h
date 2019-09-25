#ifndef _UCLOUD_RTC_BEAUTY_API_MOUDLE_H_
#define _UCLOUD_RTC_BEAUTY_API_MOUDLE_H_

#include <stdint.h>

#ifdef _EXPORT
#define _DLL_API_C extern "C" __declspec(dllexport)
#else
#define _DLL_API_C  extern "C" __declspec(dllimport)
#endif

typedef struct 
{
	int mVideoWidth;
	int mVideoHeight;

	void* videownd;
}tBeautyConfig;

_DLL_API_C int InitBeautyMoudle(tBeautyConfig config);

_DLL_API_C int UnInitBeautyMoudle();

_DLL_API_C int SelectBudle(const char* bouldpath);

_DLL_API_C int BeautyFrame(uint8_t* buf, int32_t buflen);

_DLL_API_C int RenderItem(uint8_t* buf, int32_t buflen);

#endif
