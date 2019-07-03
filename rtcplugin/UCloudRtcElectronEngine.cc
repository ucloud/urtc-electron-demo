#include "UCloudRtcElectronEngine.h"
#include "json/json.h"

UCloudRtcElectronEngine::UCloudRtcElectronEngine()
{
	m_engineinit = false;
	m_eventhandler = new ucloud::rtc::NodeEventHandler;
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
	m_engineinit = false;

}

int UCloudRtcElectronEngine::InitDevEngine(Persistent<Object>& obj, Persistent<Function>& persist)
{
	if (m_eventhandler)
	{
		m_eventhandler->addEventHandler(UCLOUD_RTC_ONAUDIOVOL_NOTIFY, obj, persist);
	}
	m_mediadevice = UCloudRtcMediaDevice::sharedInstance(this);
	return 0 ;
	
}

int UCloudRtcElectronEngine::UnInitDevEngine()
{
	if (m_mediadevice)
	{
		m_mediadevice->stopCamTest();
		m_mediadevice->stopPlaybackDeviceTest();
		m_mediadevice->stopRecordingDeviceTest();
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
	m_rtcengine = UCloudRtcEngine::sharedInstance(this);
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

//miclevel
void UCloudRtcElectronEngine::onMiceAudioLevel(int volume)
{
	if (m_eventhandler)
	{
		m_eventhandler->onAudioVolNotify(volume);
	}
}
