#include "UCloudRtcElectronEngine.h"
extern "C" {
	#include "beautyapi.h"
}

#include "VideoPackageQueue.h"
#include "json/json.h"
#include "node_log.h"

UCloudRtcElectronEngine::UCloudRtcElectronEngine()
{
	m_engineinit = false;
	m_eventhandler = new ucloud::rtc::NodeEventHandler;
	m_lpImageBuffer = new uint8_t[0x800000];
	m_usermediadevice = nullptr ;
}

UCloudRtcElectronEngine::~UCloudRtcElectronEngine()
{
	if (m_rtcengine)
	{
		m_rtcengine->destroy();
	}
	if (m_mediadevice)
	{
		m_mediadevice->destory();
	}
	if (m_eventhandler)
	{
		delete m_eventhandler;
	}
	m_eventhandler = nullptr;
	m_rtcengine = nullptr;
	m_mediadevice = nullptr;
	m_usermediadevice = nullptr ;
	m_engineinit = false;

}

int UCloudRtcElectronEngine::InitDevEngine(Persistent<Object>& obj, Persistent<Function>& persist)
{
	if (m_eventhandler)
	{
		m_eventhandler->addEventHandler(UCLOUD_RTC_ONAUDIOVOL_NOTIFY, obj, persist);
	}
	m_mediadevice = UCloudRtcMediaDevice::sharedInstance();
	m_mediadevice->InitAudioMoudle() ;
	m_mediadevice->InitVideoMoudle() ;
	return 0 ;
	
}

int UCloudRtcElectronEngine::UnInitDevEngine()
{
	if (m_mediadevice)
	{
		m_mediadevice->stopCamTest();
		m_mediadevice->stopPlaybackDeviceTest();
		m_mediadevice->stopRecordingDeviceTest();
		m_mediadevice->UnInitAudioMoudle() ;
		m_mediadevice->UnInitVideoMoudle() ;
		m_mediadevice->destory();
		m_mediadevice = nullptr;
	}
	if (m_eventhandler)
	{
		m_eventhandler->removeEventHandler(UCLOUD_RTC_ONAUDIOVOL_NOTIFY);
	}
	return 0 ;
}

int UCloudRtcElectronEngine::InitRTCEngine(Persistent<Object>& obj, Persistent<Function>& persist)
{
	if (m_eventhandler)
	{
		m_eventhandler->addEventHandler(UCLOUD_RTC_ONEVENT_NOTIFY, obj, persist);
	}
	m_rtcengine = UCloudRtcEngine::sharedInstance();
	m_rtcengine->regRtcEventListener(this) ;
	m_rtcengine->setChannelType(UCLOUD_RTC_CHANNEL_TYPE_COMMUNICATION) ;
	return 0;
}

int UCloudRtcElectronEngine::UnInitRTCEngine()
{
	if (m_rtcengine)
	{
		m_rtcengine->destroy();
		m_rtcengine = nullptr;
	}
	if (m_eventhandler)
	{
		m_eventhandler->removeEventHandler(UCLOUD_RTC_ONEVENT_NOTIFY);
	}
	return 0;
}

int UCloudRtcElectronEngine::enableExtendVideoSource(bool enable)
{
	if (m_rtcengine)
	{
		m_rtcengine->enableExtendVideocapture(enable, this);
	}
	return 0 ;
}

int UCloudRtcElectronEngine::InitBeautyEngine(int32_t wndview) 
{
	tBeautyConfig bconfig;
	bconfig.mVideoWidth = 640;
	bconfig.mVideoHeight = 360;
	bconfig.videownd = (void*)wndview ;
	return InitBeautyMoudle(bconfig) ;
}

int UCloudRtcElectronEngine::UnInitBeautyEngine() 
{
	return UnInitBeautyMoudle() ;
}

UCloudRtcEngine* UCloudRtcElectronEngine::GetUrtcEngine()
{
	return m_rtcengine;
}

UCloudRtcMediaDevice* UCloudRtcElectronEngine::GetMeidaDevice()
{
	return m_mediadevice;
}

//event listener
void UCloudRtcElectronEngine::onServerDisconnect() 
{
	if (m_eventhandler)
	{
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_SERVER_DIS, "");
	}
}
void UCloudRtcElectronEngine::onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_JOINROOM, writer.write(jmessage).data() );
	}
}
void UCloudRtcElectronEngine::onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_LEAVEROOM, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onRejoining(const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_RECONNECTING, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onReJoinRoom(const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_RECONNECT, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = info.mUserId;
		jmessage["data"]["video"] = info.mEnableVideo;
		jmessage["data"]["audio"] = info.mEnableAudio;
		jmessage["data"]["data"] = info.mEnableData;
		jmessage["data"]["mtype"] = info.mStreamMtype;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_PUBLISH, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = info.mUserId;
		jmessage["data"]["video"] = info.mEnableVideo;
		jmessage["data"]["audio"] = info.mEnableAudio;
		jmessage["data"]["data"] = info.mEnableData;
		jmessage["data"]["mtype"] = info.mStreamMtype;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_UNPUBLISH, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onRemoteUserJoin(const char* uid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_USER_JOIN, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onRemoteUserLeave(const char* uid, int reson) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_USER_LEAVE, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onRemotePublish(tUCloudRtcStreamInfo& info) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = info.mUserId;
		jmessage["data"]["video"] = info.mEnableVideo;
		jmessage["data"]["audio"] = info.mEnableAudio;
		jmessage["data"]["data"] = info.mEnableData;
		jmessage["data"]["mtype"] = info.mStreamMtype;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_REMOTE_PUBLISH, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onRemoteUnPublish(tUCloudRtcStreamInfo& info) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = info.mUserId;
		jmessage["data"]["video"] = info.mEnableVideo;
		jmessage["data"]["audio"] = info.mEnableAudio;
		jmessage["data"]["data"] = info.mEnableData;
		jmessage["data"]["mtype"] = info.mStreamMtype;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_REMOTE_UNPUBLISH, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = info.mUserId;
		jmessage["data"]["video"] = info.mEnableVideo;
		jmessage["data"]["audio"] = info.mEnableAudio;
		jmessage["data"]["data"] = info.mEnableData;
		jmessage["data"]["mtype"] = info.mStreamMtype;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_SUB_RESULT, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = info.mUserId;
		jmessage["data"]["video"] = info.mEnableVideo;
		jmessage["data"]["audio"] = info.mEnableAudio;
		jmessage["data"]["data"] = info.mEnableData;
		jmessage["data"]["mtype"] = info.mStreamMtype;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_UNSUB_RESULT, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onLocalStreamMuteRsp(const int code, const char* msg,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["mtype"] = mediatype;
		jmessage["data"]["ttype"] = tracktype;
		jmessage["data"]["mute"] = mute;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_LOCAL_MEDIA_MUTE, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["mtype"] = mediatype;
		jmessage["data"]["ttype"] = tracktype;
		jmessage["data"]["mute"] = mute;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_REMOTE_MEDIA_MUTE, writer.write(jmessage).data());
	}
}
void UCloudRtcElectronEngine::onRemoteTrackNotify(const char* uid,
	eUCloudRtcMeidaType mediatype, eUCloudRtcTrackType tracktype, bool mute) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["mtype"] = mediatype;
		jmessage["data"]["ttype"] = tracktype;
		jmessage["data"]["mute"] = mute;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_STREAM_ST_NOTIFY, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onSendRTCStats(tUCloudRtcStreamStats& rtstats) 
{
}

void UCloudRtcElectronEngine::onRemoteRTCStats(tUCloudRtcStreamStats rtstats) 
{
}

void UCloudRtcElectronEngine::onStartRecord(const int code, const char* msg, const char* recordid)  
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["recordid"] = recordid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_STARTRECORD, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onStopRecord(const int code, const char* msg, const char* recordid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["recordid"] = recordid;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_STOPRECORD, writer.write(jmessage).data());
	}
}

// vol level
void UCloudRtcElectronEngine::onLocalAudioLevel(int volume) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["vol"] = volume;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_LOCAL_AUDIO_LEVEL, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onRemoteAudioLevel(const char* uid, int volume) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["vol"] = volume;
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_REMOTE_AUDIO_LEVEL, writer.write(jmessage).data());
	}
}

void UCloudRtcElectronEngine::onKickoff(int code) 
{
}

void UCloudRtcElectronEngine::onWarning(int warn)
{
}

void UCloudRtcElectronEngine::onError(int error) 
{
}

void UCloudRtcElectronEngine::onMiceAudioLevel(int volume)
{
	if (m_eventhandler)
	{
		m_eventhandler->onAudioVolNotify(volume);
	}
}

void UCloudRtcElectronEngine::startVideoCapture(int videoprofile)
{
	if (m_usermediadevice == nullptr)
	{
		m_usermediadevice = UCloudRtcMediaDevice::sharedInstance();
	}
	LOG_INFO("UCloudRtcElectronEngine::startVideoCapture %d", m_usermediadevice ) ;
	CVideoPackageQueue::GetInstance()->SetVideoFrameLen(640 * 360 * 3 / 2);
	m_usermediadevice->startCaptureFrame((eUCloudRtcVideoProfile)videoprofile, this);
}

void UCloudRtcElectronEngine::stopVideoCapture()
{
	if (m_usermediadevice)
	{
		m_usermediadevice->stopCaptureFrame();
	}
}

void UCloudRtcElectronEngine::onCaptureFrame(unsigned char* videoframe, int buflen)
{
	m_buflock.lock() ;
	//LOG_INFO("UCloudRtcElectronEngine::onCaptureFrame framelen = %d", buflen ) ;
	tVideoFrame* video = new tVideoFrame ;
	video->m_videobuf = new uint8_t[buflen] ;
	video->m_buflen =  buflen ;
	memcpy(video->m_videobuf, videoframe, buflen);
	m_videolist.push_back(video) ;
	m_buflock.unlock() ;

	if (m_eventhandler)
	{
		m_eventhandler->onEventNotify(UCLOUD_RTC_ELEC_EVENT_DOCAPTURE, "");
	}
	
}

bool UCloudRtcElectronEngine::doCaptureFrame(tUCloudRtcI420VideoFrame* videoframe)
{
	//m_buflock.lock() ;
	uint32_t nBufferSize = 0x800000;

	BOOL bSuccess = CVideoPackageQueue::GetInstance()->PopVideoPackage(m_lpImageBuffer, &nBufferSize);
	if (!bSuccess) {
	//	m_buflock.unlock() ;
		return false;
	}
		
	 LOG_INFO("UCloudRtcElectronEngine::doCaptureFrame video width = %d && video height = %d ",  
	 	videoframe->mWidth, videoframe->mHeight) ;
	// int size = m_videolist.size() ;
	// LOG_INFO("UCloudRtcElectronEngine::doCaptureFrame videolist size = %d ",  size) ;
	// if (size <= 0)
	// {
	// 	m_buflock.unlock() ;
	// 	return false;
	// }
	
	// tVideoFrame* video = m_videolist.front() ;	
	// if (video)
	// {
	// 	//RenderItem(video->m_videobuf, video->m_buflen);
	// 	//CVideoPackageQueue::GetInstance()->PushVideoPackage(video->m_videobuf, video->m_buflen);
	// }
	// m_videolist.pop_front() ;
	// m_buflock.unlock() ;

	//LOG_INFO("UCloudRtcElectronEngine::doCaptureFrame framelen = %d", nBufferSize ) ;

	memcpy_s(videoframe->mYbuf, videoframe->mHeight*videoframe->mWidth, m_lpImageBuffer, videoframe->mHeight*videoframe->mWidth);
	memcpy_s(videoframe->mUbuf, videoframe->mHeight*videoframe->mWidth / 4, m_lpImageBuffer+ videoframe->mHeight*videoframe->mWidth,
		videoframe->mHeight*videoframe->mWidth/4);
	memcpy_s(videoframe->mVbuf, videoframe->mHeight*videoframe->mWidth / 4, m_lpImageBuffer + 5* videoframe->mHeight*videoframe->mWidth /4,
		videoframe->mHeight*videoframe->mWidth/4);
	// delete [] video->m_videobuf ;
	// delete video ;
	//m_buflock.unlock() ;
	return true;
}

void UCloudRtcElectronEngine::selectBundlePath(std::string path)
{
	m_buflock.lock() ;
	SelectBudle(path.data()) ;
	m_buflock.unlock() ;
}

void UCloudRtcElectronEngine::beautyFrame() 
{
	m_buflock.lock() ;
	int size = m_videolist.size() ;
	if (size>0)
	{
		tVideoFrame* video = m_videolist.front() ;
		m_videolist.pop_front() ;	
		m_buflock.unlock() ;
		if (video)
		{
			BeautyFrame(video->m_videobuf, video->m_buflen);
			CVideoPackageQueue::GetInstance()->PushVideoPackage(video->m_videobuf, video->m_buflen);
LOG_INFO("UCloudRtcElectronEngine::beautyFrame framelen = %d", video->m_buflen ) ;
			delete [] video->m_videobuf ;
			delete video ;
		}
		
	}
	
}

void UCloudRtcElectronEngine::addFrameItem() 
{
	m_buflock.lock() ;
	int size = m_videolist.size() ;
	if (size>0)
	{
		tVideoFrame* video = m_videolist.front() ;
		m_videolist.pop_front() ;
		m_buflock.unlock() ;	
		if (video)
		{
			RenderItem(video->m_videobuf, video->m_buflen);
			LOG_INFO("UCloudRtcElectronEngine::doCaptureFrame framelen = %d", video->m_buflen ) ;
			CVideoPackageQueue::GetInstance()->PushVideoPackage(video->m_videobuf, video->m_buflen);

			delete [] video->m_videobuf ;
			delete video ;
		}
		
	}
}
