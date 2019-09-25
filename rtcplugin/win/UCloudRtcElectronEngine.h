#ifndef _ULOUCD_RTC_URTC_ELECTRON_ENGINE_IMPL_
#define _ULOUCD_RTC_URTC_ELECTRON_ENGINE_IMPL_

#include "UCloudRtcEngine.h"
#include "UCloudRtcMediaDevice.h"
#include "UCloudRtcElectronDefine.h"
#include <list>
#include <mutex>
#include "node_event_handler.h"

class UCloudRtcElectronEngine : 
	public UCloudRtcEventListener,  
	public UCloudRtcAudioLevelListener,
	public UCloudRtcExtendVideoCaptureSource,
	public UCloudRtcVideoFrameObserver
	{
public:
	UCloudRtcElectronEngine();
	virtual ~UCloudRtcElectronEngine();

	int InitDevEngine(Persistent<Object>& obj, Persistent<Function>& persist);
	int UnInitDevEngine();

	int InitRTCEngine(Persistent<Object>& obj, Persistent<Function>& persist);
	int UnInitRTCEngine();

	int enableExtendVideoSource(bool enable);

	int InitBeautyEngine(int32_t wndview) ;
	int UnInitBeautyEngine() ;

	UCloudRtcEngine* GetUrtcEngine();
	UCloudRtcMediaDevice* GetMeidaDevice();

	//event listener
	virtual void onServerDisconnect();
	virtual void onJoinRoom(int code, const char* msg, const char* uid, const char* roomid);
	virtual void onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid);

	virtual void onRejoining(const char* uid, const char* roomid);
	virtual void onReJoinRoom(const char* uid, const char* roomid);

	virtual void onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info);
	virtual void onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info);

	virtual void onRemoteUserJoin(const char* uid);
	virtual void onRemoteUserLeave(const char* uid, int reson);

	virtual void onRemotePublish(tUCloudRtcStreamInfo& info);
	virtual void onRemoteUnPublish(tUCloudRtcStreamInfo& info);

	virtual void onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info);
	virtual void onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info);

	virtual void onLocalStreamMuteRsp(const int code, const char* msg,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute);
	virtual void onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute);
	virtual void onRemoteTrackNotify(const char* uid,
		eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute);

	virtual void onSendRTCStats(tUCloudRtcStreamStats& rtstats);
	virtual void onRemoteRTCStats(tUCloudRtcStreamStats rtstats);

	virtual void onStartRecord(const int code, const char* msg, const char* recordid)  ;
	virtual void onStopRecord(const int code, const char* msg, const char* recordid) ;

	// vol level
	virtual void onLocalAudioLevel(int volume);
	virtual void onRemoteAudioLevel(const char* uid, int volume);

	virtual void onKickoff(int code);
	virtual void onWarning(int warn);
	virtual void onError(int error);

	//miclevel
	virtual void onMiceAudioLevel(int volume);


	void startVideoCapture(int videoprofile);
	void stopVideoCapture();

	virtual  void onCaptureFrame(unsigned char* videoframe, int buflen);
	virtual  bool doCaptureFrame(tUCloudRtcI420VideoFrame* videoframe);

	void selectBundlePath(std::string path);
	void beautyFrame();
	void addFrameItem();
private:

	UCloudRtcEngine*   m_rtcengine;
	UCloudRtcMediaDevice* m_mediadevice;
	UCloudRtcMediaDevice* m_usermediadevice;
	ucloud::rtc::NodeEventHandler* m_eventhandler;

	uint8_t* m_lpImageBuffer;
	std::list<tVideoFrame*> m_videolist ;
	std::mutex m_buflock ;

	bool m_engineinit;
};

#endif

