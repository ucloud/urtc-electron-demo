#include "urtcengineimpl.h"
#include "json/json.h"

URTCEngineElectron::URTCEngineElectron()
{
	m_engineinit = false;
	m_eventhandler = new ucloud::rtc::NodeEventHandler;
}

URTCEngineElectron::~URTCEngineElectron()
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

int URTCEngineElectron::InitDevEngine(Persistent<Object>& obj, Persistent<Function>& persist)
{
	if (m_eventhandler)
	{
		m_eventhandler->addEventHandler(RTC_ONAUDIOVOL_NOTIFY, obj, persist);
	}
	m_mediadevice = UCloudRtcMediaDevice::sharedInstance(this);
	return 0 ;
	
}

int URTCEngineElectron::UnInitDevEngine()
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
		m_eventhandler->removeEventHandler(RTC_ONAUDIOVOL_NOTIFY);
	}
	return 0 ;
}

int URTCEngineElectron::InitRTCEngine(Persistent<Object>& obj, Persistent<Function>& persist)
{
	if (m_eventhandler)
	{
		m_eventhandler->addEventHandler(RTC_ONEVENT_NOTIFY, obj, persist);
	}
	m_rtcengine = UCloudRtcEngine::sharedInstance(this);
	return 0;
}

int URTCEngineElectron::UnInitRTCEngine()
{
	if (m_rtcengine)
	{
		m_rtcengine->destroy();
		m_rtcengine = nullptr;
	}
	if (m_eventhandler)
	{
		m_eventhandler->removeEventHandler(RTC_ONEVENT_NOTIFY);
	}
	return 0;
}

UCloudRtcEngine* URTCEngineElectron::GetUrtcEngine()
{
	return m_rtcengine;
}

UCloudRtcMediaDevice* URTCEngineElectron::GetMeidaDevice()
{
	return m_mediadevice;
}

//event listener
void URTCEngineElectron::onServerDisconnect() 
{
	if (m_eventhandler)
	{
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_SERVER_DIS, "");
	}
}
void URTCEngineElectron::onJoinRoom(int code, const char* msg, const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_JOINROOM, writer.write(jmessage).data() );
	}
}
void URTCEngineElectron::onLeaveRoom(int code, const char* msg, const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_LEAVEROOM, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onRejoining(const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_RECONNECTING, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onReJoinRoom(const char* uid, const char* roomid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["roomid"] = roomid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_RECONNECT, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onLocalPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_PUBLISH, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onLocalUnPublish(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_UNPUBLISH, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onRemoteUserJoin(const char* uid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_USER_JOIN, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onRemoteUserLeave(const char* uid, int reson) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_USER_LEAVE, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onRemotePublish(tUCloudRtcStreamInfo& info) 
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_REMOTE_PUBLISH, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onRemoteUnPublish(tUCloudRtcStreamInfo& info) 
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_REMOTE_UNPUBLISH, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_SUB_RESULT, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onUnSubscribeResult(const int code, const char* msg, tUCloudRtcStreamInfo& info) 
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_UNSUB_RESULT, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onLocalStreamMuteRsp(const int code, const char* msg,
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_LOCAL_MEDIA_MUTE, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onRemoteStreamMuteRsp(const int code, const char* msg, const char* uid,
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_REMOTE_MEDIA_MUTE, writer.write(jmessage).data());
	}
}
void URTCEngineElectron::onRemoteTrackNotify(const char* uid,
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
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_STREAM_ST_NOTIFY, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onSendRTCStats(tUCloudRtcStreamStats& rtstats) 
{
}

void URTCEngineElectron::onRemoteRTCStats(tUCloudRtcStreamStats rtstats) 
{
}

void URTCEngineElectron::onStartRecord(const int code, const char* msg, const char* recordid)  
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["recordid"] = recordid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_STARTRECORD, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onStopRecord(const int code, const char* msg, const char* recordid) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = code;
		jmessage["msg"] = msg;
		jmessage["data"]["recordid"] = recordid;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_STOPRECORD, writer.write(jmessage).data());
	}
}

// vol level
void URTCEngineElectron::onLocalAudioLevel(int volume) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["vol"] = volume;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_LOCAL_AUDIO_LEVEL, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onRemoteAudioLevel(const char* uid, int volume) 
{
	if (m_eventhandler)
	{
		Json::StyledWriter writer;
		Json::Value jmessage;
		jmessage["code"] = 0;
		jmessage["msg"] = "";
		jmessage["data"]["uid"] = uid;
		jmessage["data"]["vol"] = volume;
		m_eventhandler->onEventNotify(URTC_ELEC_EVENT_REMOTE_AUDIO_LEVEL, writer.write(jmessage).data());
	}
}

void URTCEngineElectron::onKickoff(int code) 
{
}

void URTCEngineElectron::onWarning(int warn)
{
}

void URTCEngineElectron::onError(int error) 
{
}

//miclevel
void URTCEngineElectron::onMiceAudioLevel(int volume)
{
	if (m_eventhandler)
	{
		m_eventhandler->onAudioVolNotify(volume);
	}
}
