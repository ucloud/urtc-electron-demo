// interfalce desc
#ifndef _UCLOUD_RTC_ENGINE_SDK_H_
#define _UCLOUD_RTC_ENGINE_SDK_H_

#include "UCloudRtcComDefine.h"

class  _EXPORT_API UCloudRtcEventListener
{
public:
	virtual void onServerDisconnect() {}
	//rtc engine
	virtual void onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) {}
	virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) {}

	virtual void onRejoining(const char* uid, const char* roomid) {}
	virtual void onReJoinRoom(const char* uid, const char* roomid) {}

	virtual void onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}
	virtual void onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

	virtual void onRemoteUserJoin(const char* uid) {}
	virtual void onRemoteUserLeave(const char* uid,int reson) {}

	virtual void onRemotePublish(tUCloudRtcStreamInfo& info) {}
	virtual void onRemoteUnPublish(tUCloudRtcStreamInfo& info) {}

	virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}
	virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) {}

	virtual void onLocalStreamMuteRsp(const int code, const char* msg,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
	virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}
	virtual void onRemoteTrackNotify(const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) {}

	virtual void onStartRecord(const int code, const char* msg, const char* recordid) {}
	virtual void onStopRecord(const int code, const char* msg, const char* recordid) {}

	virtual void onSendRTCStats(tUCloudRtcStreamStats& rtstats) {}
	virtual void onRemoteRTCStats(tUCloudRtcStreamStats rtstats) {}
	virtual void onRemoteAudioLevel(const char* uid, int volume) {}

	//common
	virtual void onLocalAudioLevel(int volume) {}
	virtual void onKickoff(int code) {}
	virtual void onWarning(int warn) {}
	virtual void onError(int error) {}
};

class _EXPORT_API UCloudRtcEngine
{
public:
	static UCloudRtcEngine *sharedInstance();
	static void destroy();
	static const char *getSdkVersion();

	virtual void regRtcEventListener(UCloudRtcEventListener* listener) = 0;

	virtual int setSdkMode(eUCloudRtcSdkMode mode) = 0;
	virtual int setChannelType(eUCloudRtcChannelType roomtype) = 0;
	virtual int setStreamRole(eUCloudRtcUserStreamRole role) = 0;
	virtual void setLogLevel(eUCloudRtcLogLevel level) = 0;
	virtual void setTokenSecKey(const char* seckey) = 0;
	virtual int setAutoPublishSubscribe(bool autoPub, bool autoSub) = 0;
	virtual int setAudioOnlyMode(bool audioOnly) = 0;

	virtual int enableExtendRtspVideocapture(bool enable, const char* rtspvideocapture) = 0;
	virtual int enableExtendVideocapture(bool enable, UCloudRtcExtendVideoCaptureSource* videocapture) = 0;
	virtual int startAudioMixing(const char* filepath, bool replace, bool loop,float musicvol) = 0;
	virtual int stopAudioMixing() = 0;
	virtual void regAudioFrameCallback(UCloudRtcAudioFrameCallback* callback) = 0;

	virtual int joinChannel(tUCloudRtcAuth& auth) = 0;
	virtual int leaveChannel() = 0;

	virtual void setVideoProfile(eUCloudRtcVideoProfile profile) = 0;
	virtual int  getDesktopNums() = 0;
	virtual void setCaptureScreenPagrams(tUCloudRtcScreenPargram& pgram) = 0;
	virtual void setDesktopProfile(eUCloudRtcScreenProfile profile) = 0;

	virtual int publish(eUCloudRtcMeidaType type, bool hasvideo, bool hasaudio) = 0; 
	virtual int unPublish(eUCloudRtcMeidaType type) = 0;
	virtual int startPreview(tUCloudRtcVideoCanvas& view) = 0;
	//virtual int startPreviewEx(bool externredner, tUCloudRtcVideoCanvas& view, UCloudRtcVideoExtendRender* render) = 0;
	virtual int stopPreview(tUCloudRtcVideoCanvas& view) = 0;
	virtual int muteLocalMic(bool mute) = 0;
	virtual int muteLocalVideo(bool mute, eUCloudRtcMeidaType streamtype) = 0;

	virtual int subscribe(tUCloudRtcStreamInfo& info) = 0;
	virtual int unSubscribe(tUCloudRtcStreamInfo& info) = 0;
	virtual int startRemoteView(tUCloudRtcVideoCanvas& view) = 0;
	//virtual int startRemoteViewEx(bool externredner, tUCloudRtcVideoCanvas& view, UCloudRtcVideoExtendRender* render) = 0;
	virtual int stopRemoteView(tUCloudRtcVideoCanvas& view) = 0;
	virtual int muteRemoteAudio(tUCloudRtcMuteSt& info, bool mute) = 0;
	virtual int muteRemoteVideo(tUCloudRtcMuteSt& info, bool mute) = 0;

	virtual int startRecord(tUCloudRtcRecordConfig& recordconfig) = 0;
	virtual int stopRecord() = 0;

	virtual int configLocalCameraPublish(bool enable) = 0;
	virtual bool isLocalCameraPublishEnabled() = 0;
	virtual int configLocalScreenPublish(bool enable) = 0;
	virtual bool isLocalScreenPublishEnabled() = 0;
	virtual int configLocalAudioPublish(bool enable) = 0;
	virtual bool isLocalAudioPublishEnabled() = 0;

	virtual bool isAutoPublish() = 0;
	virtual bool isAutoSubscribe() = 0;
	virtual bool isAudioOnly() = 0;

protected:
	virtual ~UCloudRtcEngine() {}
};

#endif
