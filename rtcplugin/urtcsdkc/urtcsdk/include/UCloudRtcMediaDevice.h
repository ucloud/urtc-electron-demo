#ifndef _UCLOUD_RTC_MEDIA_DEVICE_CPP_H_
#define _UCLOUD_RTC_MEDIA_DEVICE_CPP_H_
#include "UCloudRTCComDefine.h"

class  _EXPORT_API UCloudRtcAudioLevelListener
{
public:
	virtual void onMicAudioLevel(int volume) {}
};

class _EXPORT_API UCloudRtcMediaDevice {
public:
	static UCloudRtcMediaDevice *sharedInstance();
	static void destory();

	virtual int InitAudioMoudle() =0;
	virtual int UnInitAudioMoudle() = 0;
	virtual int InitVideoMoudle() = 0;
	virtual int UnInitVideoMoudle() = 0;

	virtual int getCamNums() = 0;
	virtual int getRecordDevNums() = 0;
	virtual int getPlayoutDevNums() = 0;

	virtual int getVideoDevInfo(int index, tUCloudRtcDeviceInfo* info) = 0;
	virtual int getRecordDevInfo(int index, tUCloudRtcDeviceInfo* info) = 0;
	virtual int getPlayoutDevInfo(int index, tUCloudRtcDeviceInfo* info) = 0;

	virtual int getCurCamDev(tUCloudRtcDeviceInfo* info) = 0;
	virtual int getCurRecordDev(tUCloudRtcDeviceInfo* info) = 0;
	virtual int getCurPlayoutDev(tUCloudRtcDeviceInfo* info) = 0;

	virtual int setVideoDevice(tUCloudRtcDeviceInfo* info) = 0;
	virtual int setRecordDevice(tUCloudRtcDeviceInfo* info) = 0;
	virtual int setPlayoutDevice(tUCloudRtcDeviceInfo* info) = 0;

	virtual int getPlaybackDeviceVolume(int *volume) = 0;
	virtual int setPlaybackDeviceVolume(int volume) = 0;

	virtual int getRecordingDeviceVolume(int *volume) = 0;
	virtual int setRecordingDeviceVolume(int volume) = 0;

	virtual int startCamTest(const char deviceId[MAX_DEVICE_ID_LENGTH], eUCloudRtcVideoProfile profile, void* hwnd) = 0;
	virtual int stopCamTest() = 0;

	virtual int startRecordingDeviceTest(const char deviceId[MAX_DEVICE_ID_LENGTH], UCloudRtcAudioLevelListener* audiolevel) = 0;
	virtual int stopRecordingDeviceTest() = 0;

	virtual int startPlaybackDeviceTest(const char deviceId[MAX_DEVICE_ID_LENGTH], const char* testAudioFilePath) = 0;
	virtual int stopPlaybackDeviceTest() = 0;

	virtual int startCaptureFrame(eUCloudRtcVideoProfile profile,UCloudRtcVideoFrameObserver* observer) = 0;
	virtual int stopCaptureFrame() = 0;

protected:
	UCloudRtcMediaDevice() { }
	virtual ~UCloudRtcMediaDevice() {}
};

#endif







