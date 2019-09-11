#ifndef _UCLOUD_RTC_SDKENGINE_COMMONDEFINE_H_
#define _UCLOUD_RTC_SDKENGINE_COMMONDEFINE_H_

#ifdef _EXPORT
#define _EXPORT_API __declspec(dllexport)
#define _EXPORT_API_C extern "C" __declspec(dllexport)
#else
#define _EXPORT_API __declspec(dllimport)
#define _EXPORT_API_C  extern "C" __declspec(dllimport)
#endif

#define  C_API extern "C"
#define MAX_DEVICE_ID_LENGTH 128 
#define MAX_WINDOWS_TILE_LEN 256 

typedef struct {
	char mDeviceName[MAX_DEVICE_ID_LENGTH];
	char mDeviceId[MAX_DEVICE_ID_LENGTH];
}tUCloudRtcDeviceInfo;

typedef struct {
	bool mVideoEnable;
	bool mAudioEnable;
}tUCloudRtcMediaConfig;

typedef struct
{
	long mScreenindex;
	int  mXpos;
	int mYpos;
	int mWidth;
	int mHeight;
}tUCloudRtcScreenPargram;

typedef enum {
	UCLOUD_RTC_TRACKTYPE_AUDIO = 0,
	UCLOUD_RTC_TRACKTYPE_VIDEO = 1
}eUCloudRtcTrackType;

typedef enum {
	UCLOUD_RTC_MEDIATYPE_NONE = 0,
	UCLOUD_RTC_MEDIATYPE_VIDEO = 1,
	UCLOUD_RTC_MEDIATYPE_SCREEN = 2
}eUCloudRtcMeidaType;

typedef struct {
	const char* mUserId;
	const char* mStreamId;
	bool mEnableVideo;
	bool mEnableAudio;
	bool mEnableData;
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcStreamInfo;

typedef struct {
	const char* mUserId;
	const char* mStreamId;
	bool mMute;
	eUCloudRtcMeidaType mStreamMtype;
}tUCloudRtcMuteSt;

typedef enum {
	UCLOUD_RTC_RECORDPROFILE_SD = 1, //标清 640*360
	UCLOUD_RTC_RECORDPROFILE_HD, // 高清  1280*720
	UCLOUD_RTC_RECORDPROFILE_HDPLUS, //超清 1920*1080
}eUCloudRtcRecordProfile;

typedef enum {
	UCLOUD_RTC_RECORDTYPE_AUDIOONLY = 1, 
	UCLOUD_RTC_RECORDTYPE_AUDIOVIDEO
}eUCloudRtcRecordType;

typedef enum {
	UCLOUD_RTC_WATERMARKPOS_LEFTTOP = 1,
	UCLOUD_RTC_WATERMARKPOS_LEFTBOTTOM,
	UCLOUD_RTC_WATERMARKPOS_RIGHTTOP,
	UCLOUD_RTC_WATERMARKPOS_RIGHTBOTTOM
}eUCloudRtcWaterMarkPos;

typedef struct {
	const char* mMainviewuid;
	const char* mBucket;
	const char* mBucketRegion;
	eUCloudRtcRecordProfile mProfile;
	eUCloudRtcRecordType mRecordType;
	eUCloudRtcWaterMarkPos mWatermarkPos;
	eUCloudRtcMeidaType mMainviewmediatype;
}tUCloudRtcRecordConfig;

//render type
typedef enum {
	UCLOUD_RTC_RENDER_MODE_DEFAULT = 0, //default full
	UCLOUD_RTC_RENDER_MODE_FIT = 1, 
	UCLOUD_RTC_RENDER_MODE_FILL = 2 
} eUCloudRtcRenderMode;

/**
*  log level
*/
typedef enum {
	UCLOUD_RTC_LOG_LEVEL_DEBUG,
	UCLOUD_RTC_LOG_LEVEL_INFO,
	UCLOUD_RTC_LOG_LEVEL_WARN,
	UCLOUD_RTC_LOG_LEVEL_ERROR,
	UCLOUD_RTC_LOG_LEVEL_NONE,
} eUCloudRtcLogLevel;

//video profile
typedef enum {
	UCLOUD_RTC_VIDEO_PROFILE_NONE = -1,
	UCLOUD_RTC_VIDEO_PROFILE_320_180 = 1,
	UCLOUD_RTC_VIDEO_PROFILE_320_240 = 2,
	UCLOUD_RTC_VIDEO_PROFILE_640_360 = 3,
	UCLOUD_RTC_VIDEO_PROFILE_640_480 = 4,
	UCLOUD_RTC_VIDEO_PROFILE_1280_720 = 5,
	UCLOUD_RTC_VIDEO_PROFILE_1920_1080 = 6
} eUCloudRtcVideoProfile;

typedef enum {
	UCLOUD_RTC_SCREEN_PROFILE_LOW = 1,
	UCLOUD_RTC_SCREEN_PROFILE_MIDDLE = 2,
	UCLOUD_RTC_SCREEN_PROFILE_HIGH = 3
} eUCloudRtcScreenProfile;

//roomtype
typedef enum {
	UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION
}eUCloudRtcChannelType;

//stream role 
typedef enum {
	UCLOUD_RTC_USER_STREAM_ROLE_PUB, // up
	UCLOUD_RTC_USER_STREAM_ROLE_SUB,// down
	UCLOUD_RTC_USER_STREAM_ROLE_BOTH //both
} eUCloudRtcUserStreamRole;

//sdk mode
typedef enum {
	UCLOUD_RTC_SDK_MODE_NORMAL, // 正常模式 需要生成token
	UCLOUD_RTC_SDK_MODE_TRIVAL, // 有期限限制测试
} eUCloudRtcSdkMode;

// render view
typedef struct
{
	int mVideoView;
	const char* mUserId;
	const char* mStreamId;
	eUCloudRtcMeidaType mStreamMtype;
	eUCloudRtcRenderMode mRenderMode;
}tUCloudRtcVideoCanvas;


typedef struct
{
	const char* mAppId;
	const char* mRoomId;
	const char* mUserId;
	const char* mUserToken;
}tUCloudRtcAuth;

typedef struct {
	const char* mUserId;
	const char* mStreamId;
	int mStreamMtype;
	int mTracktype; // 1 audio 2 video
	int mAudioBitrate = 0;     // audio bitrate,unit:bps
	int mVideoBitrate = 0;
	int mVideoWidth = 0;     // video width
	int mVideoHeight = 0;     // video height
	int mVideoFrameRate = 0;     // video frames per secon
	float mPacketLostRate = 0.0f;
}tUCloudRtcStreamStats;


typedef struct {
	const char* mUserId;
	const char* mStreamId;
	void* mAudioData;
	int mBytePerSimple;
	int mSimpleRate;
	int mChannels;
	int mNumSimples;
}tUCloudRtcAudioFrame;

typedef struct {
	unsigned char* mYbuf;
	unsigned char* mUbuf;
	unsigned char* mVbuf;
	int mWidth;
	int mHeight;
}tUCloudRtcI420VideoFrame;

class  _EXPORT_API UCloudRtcAudioFrameCallback
{
public:
	virtual void onLocalAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
	virtual void onRemoteMixAudioFrame(tUCloudRtcAudioFrame* audioframe) {}
};
class  _EXPORT_API UCloudRtcExtendVideoCaptureSource
{
public:
	virtual  bool doCaptureFrame(tUCloudRtcI420VideoFrame* videoframe) = 0;
};

class _EXPORT_API UCloudRtcVideoFrameObserver 
{
public:
	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen) = 0;
};

#endif

