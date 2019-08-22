// addon.cc
#include <node.h>
#include "UCloudRtcElectronEngine.h"
#include "json/json.h"
#include "node_event_handler.h"
#include "node_log.h"

using namespace v8;
#define SAFE_DELETE(p) if((p)!=nullptr){delete (p);(p)=nullptr;}

//v8::Function* _eventcallback;
//ucloud::rtc::NodeEventHandler g_eventhandler;
UCloudRtcElectronEngine* m_elecengine = new UCloudRtcElectronEngine;

//device interface
void NodeInitDevEngine(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "InitDevEngine Wrong number of arguments")));
		return;
	}
	Local<Function> callback = args[0].As<Function>();
	if (callback.IsEmpty()) {
		return;
	}
	Persistent<Function> persist;
	persist.Reset(args.GetIsolate(), callback);
	Local<Object> obj = args.This();
	Persistent<Object> persistObj;
	persistObj.Reset(args.GetIsolate(), obj);
	
	m_elecengine->InitDevEngine(persistObj, persist);

}

void NodeUnInitDevEngine(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (m_elecengine)
	{
		m_elecengine->UnInitDevEngine();
	}

	Local<Number> num = Number::New(isolate, 0);
	args.GetReturnValue().Set(num);
}
void NodeGetCamNums(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t counts = 0;
	if (m_elecengine->GetMeidaDevice())
	{
		counts = m_elecengine->GetMeidaDevice()->getCamNums();
	}
	Local<Number> num = Number::New(isolate, counts);
	args.GetReturnValue().Set(num);
}

void NodeGetCamDevinfo(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
    if (args.Length() < 2) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "GetCamDevinfo Wrong number of arguments")));
        return;
    }
	tUCloudRtcDeviceInfo tDevinfo;
	int32_t index = args[0]->Int32Value();

	int32_t nRetValue = 0;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->getVideoDevInfo(index, &tDevinfo);
		if (nRetValue == 0)
		{
			Local<Value> devid = napi_create_string_(isolate, tDevinfo.mDeviceId);
			Local<Value> devname = napi_create_string_(isolate, tDevinfo.mDeviceName);

			Local<Object> devinfo = args[1]->ToObject(isolate);

			Local<Value> idpropName = napi_create_string_(isolate, "deviceid");
			devinfo->Set(isolate->GetCurrentContext(), idpropName, devid);

			Local<Value> namepropName = napi_create_string_(isolate, "devicename");
			devinfo->Set(isolate->GetCurrentContext(), namepropName, devname);
		}
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(nRetValue);
}

void NodeGetRecordNums(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t counts = 0;
	if (m_elecengine->GetMeidaDevice())
	{
		counts = m_elecengine->GetMeidaDevice()->getRecordDevNums();
	}
	Local<Number> num = Number::New(isolate, counts);
	args.GetReturnValue().Set(num);
}

void NodeGetRecordDevinfo(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 2) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "GetCamDevinfo Wrong number of arguments")));
		return;
	}
	tUCloudRtcDeviceInfo tDevinfo;
	int32_t index = args[0]->Int32Value();

	int32_t nRetValue = 0;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->getRecordDevInfo(index, &tDevinfo);
		if (nRetValue == 0)
		{
			Local<Value> devid = napi_create_string_(isolate, tDevinfo.mDeviceId);
			Local<Value> devname = napi_create_string_(isolate, tDevinfo.mDeviceId);

			Local<Object> devinfo = args[1]->ToObject(isolate);

			Local<Value> idpropName = napi_create_string_(isolate, "deviceid");
			devinfo->Set(isolate->GetCurrentContext(), idpropName, devid);

			Local<Value> namepropName = napi_create_string_(isolate, "devicename");
			devinfo->Set(isolate->GetCurrentContext(), namepropName, devname);
		}
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(nRetValue);
}

void NodeGetPlayoutNums(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t counts = 0;
	if (m_elecengine->GetMeidaDevice())
	{
		counts = m_elecengine->GetMeidaDevice()->getPlayoutDevNums();
	}
	Local<Number> num = Number::New(isolate, counts);
	args.GetReturnValue().Set(num);
}

void NodeGetPlayoutDevinfo(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 2) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return;
	}
	tUCloudRtcDeviceInfo tDevinfo;
	int32_t index = args[0]->Int32Value();

	int32_t nRetValue = 0;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->getPlayoutDevInfo(index, &tDevinfo);
		if (nRetValue == 0)
		{
			Local<Value> devid = napi_create_string_(isolate, tDevinfo.mDeviceId);
			Local<Value> devname = napi_create_string_(isolate, tDevinfo.mDeviceName);

			Local<Object> devinfo = args[1]->ToObject(isolate);

			Local<Value> idpropName = napi_create_string_(isolate, "deviceid");
			devinfo->Set(isolate->GetCurrentContext(), idpropName, devid);

			Local<Value> namepropName = napi_create_string_(isolate, "devicename");
			devinfo->Set(isolate->GetCurrentContext(), namepropName, devname);

			args.GetReturnValue().Set(0);
		}
		
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(nRetValue);
}

void NodeStartVideoCaptureTest(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 2) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StartVideoCaptureTest Wrong number of arguments")));
		return;
	}
	Local<String> devid = args[0]->ToString();
	int len = devid->Utf8Length();
	char* buf = new char[len + 1];
	memset(buf, 0, len + 1);
	devid->WriteUtf8(buf);

	int videownd = args[1]->Int32Value();

	int32_t nRetValue = -1;;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->startCamTest(buf, UCLOUD_RTC_VIDEO_PROFILE_640_360, (void*)videownd);
	}

	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
	LOG_INFO("StartVideoCaptureTest devid = %s,  videownd = %d", buf, videownd) ;
    SAFE_DELETE(buf);
}

void NodeStopVideoCaptureTest(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->stopCamTest();
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
}

void NodeStartMicTest(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
    if (args.Length() < 1) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "StartMicTest Wrong number of arguments")));
        return;
    }
	Local<String> devid = args[0]->ToString();
	int len = devid->Utf8Length();
	char* buf = new char[len + 1];
	memset(buf, 0, len + 1);
	devid->WriteUtf8(buf);

    LOG_INFO("StartMicTest devid %s", buf);
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->startRecordingDeviceTest(buf, m_elecengine);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
    SAFE_DELETE(buf);
}

void NodeStopMicTest(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->stopRecordingDeviceTest();
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
}

void NodeStartPlayTest(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 2) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StartMicTest Wrong number of arguments")));
		return;
	}
	Local<String> devid = args[0]->ToString();
	int len = devid->Utf8Length();
	char* buf = new char[len + 1];
	memset(buf, 0, len + 1);
	devid->WriteUtf8(buf);

	len = 0;
	Local<String> filepath = args[0]->ToString();
	len = filepath->Utf8Length();
	char* bufpath = new char[len + 1];
	memset(bufpath, 0, len + 1);
	filepath->WriteUtf8(bufpath);

	LOG_INFO("StartMicTest devid %s", buf);
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->startPlaybackDeviceTest(buf, bufpath);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
	SAFE_DELETE(buf);
	SAFE_DELETE(bufpath);
}

void NodeStopPlayTest(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->stopPlaybackDeviceTest();
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
}

void NodeSetActiveCam(const FunctionCallbackInfo<Value>& args) {
    LOG_INFO("start NodeSetActiveCam");
    Isolate* isolate = args.GetIsolate();
    if (args.Length() < 1) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "SetActiveCam Wrong number of arguments")));
        return;
    }
    tUCloudRtcDeviceInfo tDevinfo;
    Local<Object> params = args[0]->ToObject();

    Local<Value> device_name = params->Get(String::NewFromUtf8(isolate, "devicename"));
    Local<String> device_name_str = device_name->ToString();
    int32_t len = device_name_str->Utf8Length();
    char* device_name_buf = new char[len + 1];
    memset(device_name_buf, 0, len + 1);
    device_name_str->WriteUtf8(device_name_buf);
    memcpy(tDevinfo.mDeviceName, device_name_buf, len + 1);

    Local<Value> device_id = params->Get(String::NewFromUtf8(isolate, "deviceid"));
    Local<String> device_id_str = device_id->ToString();
    len = device_id_str->Utf8Length();
    char *device_id_buf = new char[len + 1];
    memset(device_id_buf, 0, len + 1);
    device_id_str->WriteUtf8(device_id_buf);
    memcpy(tDevinfo.mDeviceId, device_id_buf, len + 1);

    LOG_INFO("cam device name %s id %s", tDevinfo.mDeviceName, tDevinfo.mDeviceId);

	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->setVideoDevice(&tDevinfo);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
    SAFE_DELETE(device_name_buf);
    SAFE_DELETE(device_id_buf);
}

void NodeSetActiveMic(const FunctionCallbackInfo<Value>& args) {
    LOG_INFO("start NodeSetActiveCam");
    Isolate* isolate = args.GetIsolate();
    if (args.Length() < 1) {
        isolate->ThrowException(Exception::TypeError(
            String::NewFromUtf8(isolate, "SetActiveMic Wrong number of arguments")));
        return;
    }
    tUCloudRtcDeviceInfo tDevinfo;
    Local<Object> params = args[0]->ToObject();

    Local<Value> device_name = params->Get(String::NewFromUtf8(isolate, "devicename"));
    Local<String> device_name_str = device_name->ToString();
    int32_t len = device_name_str->Utf8Length();
    char* device_name_buf = new char[len + 1];
    memset(device_name_buf, 0, len + 1);
    device_name_str->WriteUtf8(device_name_buf);
    memcpy(tDevinfo.mDeviceName, device_name_buf, len + 1);

    Local<Value> device_id = params->Get(String::NewFromUtf8(isolate, "deviceid"));
    Local<String> device_id_str = device_id->ToString();
    len = device_id_str->Utf8Length();
    char *device_id_buf = new char[len + 1];
    memset(device_id_buf, 0, len + 1);
    device_id_str->WriteUtf8(device_id_buf);
    memcpy(tDevinfo.mDeviceId, device_id_buf, len + 1);

    LOG_INFO("mic device name %s id %s", tDevinfo.mDeviceName, tDevinfo.mDeviceId);
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->setRecordDevice(&tDevinfo);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
    SAFE_DELETE(device_id_buf);
    SAFE_DELETE(device_name_buf);
}

void NodeSetActivePlay(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetActivePlay Wrong number of arguments")));
		return;
	}
	tUCloudRtcDeviceInfo tDevinfo;
	Local<Object> params = args[0]->ToObject();

	Local<Value> device_name = params->Get(String::NewFromUtf8(isolate, "devicename"));
	Local<String> device_name_str = device_name->ToString();
	int32_t len = device_name_str->Utf8Length();
	char* device_name_buf = new char[len + 1];
	memset(device_name_buf, 0, len + 1);
	device_name_str->WriteUtf8(device_name_buf);
	memcpy(tDevinfo.mDeviceName, device_name_buf, len + 1);

	Local<Value> device_id = params->Get(String::NewFromUtf8(isolate, "deviceid"));
	Local<String> device_id_str = device_id->ToString();
	len = device_id_str->Utf8Length();
	char *device_id_buf = new char[len + 1];
	memset(device_id_buf, 0, len + 1);
	device_id_str->WriteUtf8(device_id_buf);
	memcpy(tDevinfo.mDeviceId, device_id_buf, len + 1);

	LOG_INFO("mic device name %s id %s", tDevinfo.mDeviceName, tDevinfo.mDeviceId);
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->setPlayoutDevice(&tDevinfo);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
	SAFE_DELETE(device_id_buf);
	SAFE_DELETE(device_name_buf);
}

void NodeSetRecordVol(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetRecordVol Wrong number of arguments")));
		return;
	}
	int32_t volume = args[0]->Int32Value();
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->setRecordingDeviceVolume(volume);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
}

void NodeGetRecordVol(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	int32_t volume = 0;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		mediadevice->getRecordingDeviceVolume(&volume);
	}
	Local<Number> num = Number::New(isolate, volume);
	args.GetReturnValue().Set(num);
}

void NodeSetPlayVol(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetPlayVol Wrong number of arguments")));
		return;
	}
	int32_t volume = args[0]->Int32Value();
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->setPlaybackDeviceVolume(volume);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
}

void NodeGetPlayVol(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	int32_t volume = 0;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		mediadevice->getRecordingDeviceVolume(&volume);
	}
	Local<Number> num = Number::New(isolate, volume);
	args.GetReturnValue().Set(num);
}

void NodeSetSpeakerVol(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetSpeakerVol Wrong number of arguments")));
		return;
	}
	int32_t volume = args[0]->Int32Value();
	int32_t nRetValue = -1;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		nRetValue = mediadevice->setPlaybackDeviceVolume(volume);
	}
	Local<Number> num = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(num);
}

void NodeGetSpeakerVol(const FunctionCallbackInfo<Value>& args) {
	LOG_INFO("start NodeSetActiveCam");
	Isolate* isolate = args.GetIsolate();
	int32_t volume = 0;
	UCloudRtcMediaDevice* mediadevice = m_elecengine->GetMeidaDevice();
	if (mediadevice)
	{
		mediadevice->getPlaybackDeviceVolume(&volume);
	}
	Local<Number> num = Number::New(isolate, volume);
	args.GetReturnValue().Set(num);
}

void NodeInitRtcEngine(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "InitDevEngine Wrong number of arguments")));
		return;
	}
	Local<Function> callback = args[0].As<Function>();
	if (callback.IsEmpty()) {
		return;
	}
	startLogService("electronmedia.log") ;
	Persistent<Function> persist;
	persist.Reset(args.GetIsolate(), callback);
	Local<Object> obj = args.This();
	Persistent<Object> persistObj;
	persistObj.Reset(args.GetIsolate(), obj);

	m_elecengine->InitRTCEngine(persistObj, persist);

}

void NodeUnInitRtcEngine(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (m_elecengine)
	{
		m_elecengine->UnInitRTCEngine();
	}
	Local<Number> num = Number::New(isolate, 0);
	args.GetReturnValue().Set(num);
}

//engine interface
void NodeGetSdkVersion(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		const char* content = rtcengine->getSdkVersion();
		Local<Value> devid = napi_create_string_(isolate, content);
		args.GetReturnValue().Set(devid);
	}
	else 
	{
		Local<Value> devid = napi_create_string_(isolate, "v1");
		args.GetReturnValue().Set(devid);
	}
}
void NodeSetToeknSeckey(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();

	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
    int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		rtcengine->setTokenSecKey(jsonmsg);
		Local<Number> retValue = Number::New(isolate,0);
		args.GetReturnValue().Set(retValue);
	}
	else 
	{
		Local<Number> retValue = Number::New(isolate,-1);
		args.GetReturnValue().Set(retValue);
	}
	SAFE_DELETE(jsonmsg) ;
}


void NodeSetSdkMode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetSdkMode Wrong number of arguments")));
		return;
	}
	int32_t sdkmode = args[0]->Int32Value();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->setSdkMode(static_cast<eUCloudRtcSdkMode>(sdkmode));
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeSetStreamRole(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetStreamRole Wrong number of arguments")));
		return;
	}
	int32_t role = args[0]->Int32Value();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->setStreamRole(static_cast<eUCloudRtcUserStreamRole>(role));
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeSetLogLevel(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetLogLevel Wrong number of arguments")));
		return;
	}
	int32_t loglevel = args[0]->Int32Value();
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		rtcengine->setLogLevel(static_cast<eUCloudRtcLogLevel>(loglevel));
	}

	Local<Number> retValue = Number::New(isolate, 0);
	args.GetReturnValue().Set(retValue);
}

void NodeSetAutoPubSub(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 2) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetAutoPubSub Wrong number of arguments")));
		return;
	}
	bool autopub = args[0]->BooleanValue();
	bool autosub = args[1]->BooleanValue();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->setAutoPublishSubscribe(autopub, autosub);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeSetAudioOnlyMode(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetAudioOnlyMode Wrong number of arguments")));
		return;
	}
	bool audioonly = args[0]->BooleanValue();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->setAudioOnlyMode(audioonly);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeStartAudioMixing(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StartAudioMixing Wrong number of arguments")));
		return;
	}

	Local<String> jsonbody = args[0]->ToString();
    int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);
	LOG_INFO("NodeStartAudioMixing = %s", jsonmsg) ;

	const char* filepath = retObj["filepath"].asCString() ;
	bool repleace = retObj["repleace"].asBool() ;
	bool loop = retObj["loop"].asInt() ;
	float vol = retObj["vol"].asFloat() ;
    LOG_INFO("NodeStartAudioMixing filepath = %s", filepath ) ;
	
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->startAudioMixing(filepath, repleace, loop, vol);
		LOG_INFO("NodeStartAudioMixing = %d", nRetValue) ;
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeStopAudioMixing(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->stopAudioMixing();
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeSetVideoProfile(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetVideoProfile Wrong number of arguments")));
		return;
	}
	int32_t videofile = args[0]->Int32Value();
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		rtcengine->setVideoProfile(static_cast<eUCloudRtcVideoProfile>(videofile));
	}

	Local<Number> retValue = Number::New(isolate, 0);
	args.GetReturnValue().Set(retValue);
}


void NodeSetScreenProfile(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetScreenProfile Wrong number of arguments")));
		return;
	}
	int32_t videofile = args[0]->Int32Value();
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		rtcengine->setDesktopProfile(static_cast<eUCloudRtcScreenProfile>(videofile));
	}

	Local<Number> retValue = Number::New(isolate, 0);
	args.GetReturnValue().Set(retValue);
}

void NodeGetScreenNums(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	int32_t nRetValue = 0 ;
	if (rtcengine)
	{
		nRetValue = rtcengine->getDesktopNums();
	}
	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeSetScreenPagram(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SetScreenPagram Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
    int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	LOG_INFO("NodeSetScreenPagram = %s", jsonmsg) ;
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	int index = retObj["index"].asInt() ;
	int xpos = retObj["x"].asInt() ;
	int ypos = retObj["y"].asInt() ;
	int width = retObj["width"].asInt() ;
	int height = retObj["height"].asInt() ;

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		LOG_INFO("NodeSetScreenPagram = %s", jsonmsg) ;
		tUCloudRtcScreenPargram pgram;
		pgram.mScreenindex = index;
		pgram.mXpos = xpos;
		pgram.mYpos = ypos;
		pgram.mWidth = width;
		pgram.mHeight = height;
		rtcengine->setCaptureScreenPagrams(pgram);

		nRetValue = 0 ;
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeJoinChannel(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "JoinChannel Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
    int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	LOG_INFO("NodeJoinChannel = %s", jsonmsg) ;
	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	std::string uid = retObj["uid"].asString();
	std::string roomid = retObj["rid"].asString();
	std::string appid = retObj["appid"].asString();
	std::string token = retObj["token"].asString();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		//LOG_INFO("NodeJoinChannel = %s", jsonmsg) ;
		tUCloudRtcAuth auth;
		auth.mUserId = uid.data();
		auth.mRoomId = roomid.data();
		auth.mAppId = appid.data();
		auth.mUserToken = token.data();

		nRetValue = rtcengine->joinChannel(auth);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeLeaveChannel(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->leaveChannel();
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeStartPreview(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StartPreview Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	int32_t hwnd = retObj["view"].asInt();
	std::string uid = retObj["uid"].asString();
	int32_t mtype = retObj["mtype"].asInt();
	int32_t renermode = retObj["rmode"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcVideoCanvas videoview;
		videoview.mUserId = uid.data();
		videoview.mVideoView = hwnd;
		videoview.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		videoview.mRenderMode = static_cast<eUCloudRtcRenderMode>(renermode);
		nRetValue = rtcengine->startPreview(videoview);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeStopPreview(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StopPreview Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	int32_t hwnd = retObj["view"].asInt();
	std::string uid = retObj["uid"].asString();
	int32_t mtype = retObj["mtype"].asInt();
	int32_t renermode = retObj["rmode"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcVideoCanvas videoview;
		videoview.mUserId = uid.data();
		videoview.mVideoView = hwnd;
		videoview.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		videoview.mRenderMode = static_cast<eUCloudRtcRenderMode>(renermode);
		nRetValue = rtcengine->stopPreview(videoview);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodePublishStream(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 3) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "PublishStream Wrong number of arguments")));
		return;
	}
	int32_t mtype = args[0]->Int32Value();
	bool hasvideo = args[1]->BooleanValue();
	bool hasaudio = args[2]->BooleanValue();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->publish(static_cast<eUCloudRtcMeidaType>(mtype), hasvideo, hasaudio);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeUnPublishStream(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "UnPublishStream Wrong number of arguments")));
		return;
	}
	int32_t mtype = args[0]->Int32Value();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->unPublish(static_cast<eUCloudRtcMeidaType>(mtype));
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeMuteLocalMic(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "MuteLocalMic Wrong number of arguments")));
		return;
	}
	bool mute = args[0]->BooleanValue();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->muteLocalMic(mute);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeMuteLocalVideo(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "MuteLocalVideo Wrong number of arguments")));
		return;
	}
	bool mute = args[0]->BooleanValue();
	int32_t mtype = args[1]->Int32Value();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->muteLocalVideo(mute, static_cast<eUCloudRtcMeidaType>(mtype));
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeStartRemoteRender(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StartRemoteRender Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	int32_t hwnd = retObj["view"].asInt();
	std::string uid = retObj["uid"].asString();
	int32_t mtype = retObj["mtype"].asInt();
	int32_t renermode = retObj["rmode"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcVideoCanvas videoview;
		videoview.mUserId = uid.data();
		videoview.mVideoView = hwnd;
		videoview.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		videoview.mRenderMode = static_cast<eUCloudRtcRenderMode>(renermode);
		nRetValue = rtcengine->startRemoteView(videoview);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeStopRemoteView(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StopRemoteView Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	int32_t hwnd = retObj["view"].asInt();
	std::string uid = retObj["uid"].asString();
	int32_t mtype = retObj["mtype"].asInt();
	int32_t renermode = retObj["rmode"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcVideoCanvas videoview;
		videoview.mUserId = uid.data();
		videoview.mVideoView = hwnd;
		videoview.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		videoview.mRenderMode = static_cast<eUCloudRtcRenderMode>(renermode);
		nRetValue = rtcengine->stopRemoteView(videoview);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeSubStream(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "SubStream Wrong number of arguments")));
		return;
	}

	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);
	
	LOG_INFO("start NodeSetActiveCam");

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	std::string uid = retObj["uid"].asString();
	bool audio = retObj["audio"].asBool();
	bool video = retObj["video"].asBool();
	int32_t mtype = retObj["mtype"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcStreamInfo streaminfo;
		streaminfo.mUserId = uid.data();
		streaminfo.mEnableVideo = video;
		streaminfo.mEnableAudio = audio;
		streaminfo.mEnableData = false;
		streaminfo.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		nRetValue = rtcengine->subscribe(streaminfo);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeUnSubStream(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "UnSubStream Wrong number of arguments")));
		return;
	}

	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	std::string uid = retObj["uid"].asString();
	bool audio = retObj["audio"].asBool();
	bool video = retObj["video"].asBool();
	int32_t mtype = retObj["mtype"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcStreamInfo streaminfo;
		streaminfo.mUserId = uid.data();
		streaminfo.mEnableVideo = video;
		streaminfo.mEnableAudio = audio;
		streaminfo.mEnableData = false;
		streaminfo.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		nRetValue = rtcengine->unSubscribe(streaminfo);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeMuteRemoteAudio(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "MuteRemoteAudio Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	std::string uid = retObj["uid"].asString();
	bool mute = retObj["mute"].asBool();
	int32_t mtype = retObj["mtype"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcMuteSt mutest;
		mutest.mMute = mute;
		mutest.mUserId = uid.data();
		mutest.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		nRetValue = rtcengine->muteRemoteAudio(mutest, mute);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeMuteRemoteVideo(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "MuteRemoteVideo Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	std::string uid = retObj["uid"].asString();
	bool mute = retObj["mute"].asBool();
	int32_t mtype = retObj["mtype"].asInt();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		tUCloudRtcMuteSt mutest;
		mutest.mMute = mute;
		mutest.mUserId = uid.data();
		mutest.mStreamMtype = static_cast<eUCloudRtcMeidaType>(mtype);
		nRetValue = rtcengine->muteRemoteVideo(mutest, mute);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}

void NodeStartRecord(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "StartRecord Wrong number of arguments")));
		return;
	}
	Local<String> jsonbody = args[0]->ToString();
	int32_t bodylen = jsonbody->Utf8Length();
	char *jsonmsg = new char[bodylen + 1];
	memset(jsonmsg, 0, bodylen + 1);
	jsonbody->WriteUtf8(jsonmsg);

	Json::Reader reader;
	Json::Value retObj;
	reader.parse(jsonmsg, retObj, false);

	std::string mainviewid = retObj["mainuid"].asString();
	int32_t profile = retObj["profile"].asInt();
	int32_t recordtype = retObj["rtype"].asInt();
	int32_t waterpos = retObj["wpos"].asInt();
	int32_t mainviewmtype = retObj["mvtype"].asInt();
	std::string bucket = retObj["bucket"].asString();
	std::string region = retObj["region"].asString();

	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();

	LOG_INFO("start NodeStartRecord mainviewid = %s && profile=%d && rtype=%d && wpos=%d && mvtype=%d",
							mainviewid.data(), profile, recordtype, waterpos, mainviewmtype);
	if (rtcengine)
	{
		tUCloudRtcRecordConfig recordconfig;
		recordconfig.mMainviewuid = mainviewid.data();
		recordconfig.mProfile = static_cast<eUCloudRtcRecordProfile>(profile);
		recordconfig.mRecordType = static_cast<eUCloudRtcRecordType>(recordtype);
		recordconfig.mWatermarkPos = static_cast<eUCloudRtcWaterMarkPos>(waterpos);
		recordconfig.mMainviewmediatype = static_cast<eUCloudRtcMeidaType>(mainviewmtype);
		recordconfig.mBucket = bucket.data() ;
		recordconfig.mBucketRegion = region.data() ;
		nRetValue = rtcengine->startRecord(recordconfig);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
	SAFE_DELETE(jsonmsg);
}


void NodeStopRecord(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->stopRecord();
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeConfigCameraPublish(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "ConfigCameraPublish Wrong number of arguments")));
		return;
	}
	bool enable = args[0]->BooleanValue();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->configLocalCameraPublish(enable);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeIsCameraPublishEnable(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool camenable = false;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		camenable = rtcengine->isLocalCameraPublishEnabled();
	}

	args.GetReturnValue().Set(camenable);
}

void NodeConfigScreenPublish(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "ConfigScreenPublish Wrong number of arguments")));
		return;
	}
	bool enable = args[0]->BooleanValue();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->configLocalScreenPublish(enable);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeIsScreenPublishEnable(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool camenable = false;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		camenable = rtcengine->isLocalScreenPublishEnabled();
	}

	args.GetReturnValue().Set(camenable);
}

void NodeConfigAudioPublish(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	if (args.Length() < 1) {
		isolate->ThrowException(Exception::TypeError(
			String::NewFromUtf8(isolate, "ConfigAudioPublish Wrong number of arguments")));
		return;
	}
	bool enable = args[0]->BooleanValue();
	int32_t nRetValue = -1;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		nRetValue = rtcengine->configLocalAudioPublish(enable);
	}

	Local<Number> retValue = Number::New(isolate, nRetValue);
	args.GetReturnValue().Set(retValue);
}

void NodeIsAudioPublishEnable(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool camenable = false;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		camenable = rtcengine->isLocalAudioPublishEnabled();
	}

	args.GetReturnValue().Set(camenable);
}

void NodeIsAutoPublish(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool camenable = false;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		camenable = rtcengine->isAutoPublish();
	}

	args.GetReturnValue().Set(camenable);
}

void NodeIsAutoSubscribe(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool camenable = false;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		camenable = rtcengine->isAutoSubscribe();
	}

	args.GetReturnValue().Set(camenable);
}

void NodeIsAudioOnly(const FunctionCallbackInfo<Value>& args) {
	Isolate* isolate = args.GetIsolate();
	bool camenable = false;
	UCloudRtcEngine* rtcengine = m_elecengine->GetUrtcEngine();
	if (rtcengine)
	{
		camenable = rtcengine->isAudioOnly();
	}

	args.GetReturnValue().Set(camenable);
}

void Init(Local<Object> exports, Local<Object> module) {
	NODE_SET_METHOD(exports, "initdevengine", NodeInitDevEngine);
	NODE_SET_METHOD(exports, "uninitdevengine", NodeUnInitDevEngine);
	NODE_SET_METHOD(exports, "getcamnums", NodeGetCamNums); //testdone
	NODE_SET_METHOD(exports, "getcamdevinfo", NodeGetCamDevinfo); //testdone
	NODE_SET_METHOD(exports, "getmicnums", NodeGetRecordNums);  //testdone
	NODE_SET_METHOD(exports, "getmicdevinfo", NodeGetRecordDevinfo); //testdone
	NODE_SET_METHOD(exports, "getplayoutnums", NodeGetPlayoutNums);  //testdone
	NODE_SET_METHOD(exports, "getplayoutdevinfo", NodeGetPlayoutDevinfo); //testdone
	NODE_SET_METHOD(exports, "startcamtest", NodeStartVideoCaptureTest); //testdone
	NODE_SET_METHOD(exports, "stopcamtest", NodeStopVideoCaptureTest); //testdone
	NODE_SET_METHOD(exports, "startmictest", NodeStartMicTest); //testdone
	NODE_SET_METHOD(exports, "stopmictest", NodeStopMicTest); //testdone
	NODE_SET_METHOD(exports, "startplaytest", NodeStartPlayTest); //testdone
	NODE_SET_METHOD(exports, "stopplaytest", NodeStopPlayTest); //testdone
    NODE_SET_METHOD(exports, "setactivecam", NodeSetActiveCam); // todo - done testdone
    NODE_SET_METHOD(exports, "setactivemic", NodeSetActiveMic); //todo - done testdone
	NODE_SET_METHOD(exports, "setactiveplay", NodeSetActivePlay); //todo - done testdone
	NODE_SET_METHOD(exports, "setrecordvol", NodeSetRecordVol); //todo - done testdone
	NODE_SET_METHOD(exports, "getrecordvol", NodeGetRecordVol); //todo - done testdone

	NODE_SET_METHOD(exports, "setplayoutvol", NodeSetPlayVol); //todo - done testdone
	NODE_SET_METHOD(exports, "getplayoutvol", NodeGetPlayVol); //todo - done testdone

	NODE_SET_METHOD(exports, "setspeakervol", NodeSetSpeakerVol); //todo - done testdone
	NODE_SET_METHOD(exports, "getspeakervol", NodeGetSpeakerVol); //todo - done testdone
	//rtcengine
	NODE_SET_METHOD(exports, "initrtcengine", NodeInitRtcEngine);
	NODE_SET_METHOD(exports, "uninitrtcengine", NodeUnInitRtcEngine);
	NODE_SET_METHOD(exports, "getsdkversion", NodeGetSdkVersion);
	NODE_SET_METHOD(exports, "settokenseckey", NodeSetToeknSeckey);
	NODE_SET_METHOD(exports, "setsdkmode", NodeSetSdkMode);
	NODE_SET_METHOD(exports, "setstreamrole", NodeSetStreamRole);   //testdone
	NODE_SET_METHOD(exports, "setloglevel", NodeSetLogLevel); //testdone
	NODE_SET_METHOD(exports, "setvideoprofile", NodeSetVideoProfile); //testdone
	NODE_SET_METHOD(exports, "setscreenprofile", NodeSetScreenProfile); //testdone
	NODE_SET_METHOD(exports, "getscreennums", NodeGetScreenNums); //testdone
	NODE_SET_METHOD(exports, "setscreencapturepragram", NodeSetScreenPagram); //testdone
	NODE_SET_METHOD(exports, "setaudioonlymode", NodeSetAudioOnlyMode); //testdone
	NODE_SET_METHOD(exports, "setaudopubsub", NodeSetAutoPubSub); //testdone
	NODE_SET_METHOD(exports, "startaudiomixing", NodeStartAudioMixing); //testdone
	NODE_SET_METHOD(exports, "stopaudiomixing", NodeStopAudioMixing); //testdone

	NODE_SET_METHOD(exports, "joinroom", NodeJoinChannel); // testdone
    NODE_SET_METHOD(exports, "leaveroom", NodeLeaveChannel); //todo - done testdone

	NODE_SET_METHOD(exports, "startpreview", NodeStartPreview); // testdone
	NODE_SET_METHOD(exports, "stoppreview", NodeStopPreview); //todo - done testdone
    NODE_SET_METHOD(exports, "publishstream", NodePublishStream); //todo - done testdone
    NODE_SET_METHOD(exports, "unpublishstream", NodeUnPublishStream); //todo - done testdone
    NODE_SET_METHOD(exports, "mutelocalaudio", NodeMuteLocalMic); //todo - done testdone
    NODE_SET_METHOD(exports, "mutelocalvideo", NodeMuteLocalVideo); //todo - done testdone

   
	NODE_SET_METHOD(exports, "startremoteview", NodeStartRemoteRender); // testdone
	NODE_SET_METHOD(exports, "stopremoteview", NodeStopRemoteView); //todo - done testdone
    NODE_SET_METHOD(exports, "subscribestream", NodeSubStream); //todo - done testdone
    NODE_SET_METHOD(exports, "unsubscribestream", NodeUnSubStream); //todo - done
	NODE_SET_METHOD(exports, "muteremoteaudio", NodeMuteRemoteAudio); //todo - done testdone
	NODE_SET_METHOD(exports, "muteremotevideo", NodeMuteRemoteVideo); //todo - done testdone
	
	NODE_SET_METHOD(exports, "startrecord", NodeStartRecord); // testdone
	NODE_SET_METHOD(exports, "stoprecord", NodeStopRecord); //todo - done testdone

	NODE_SET_METHOD(exports, "configcamerapublish", NodeConfigCameraPublish); // testdone
	NODE_SET_METHOD(exports, "isconfigcampublish", NodeIsCameraPublishEnable); //todo - done testdone
	NODE_SET_METHOD(exports, "configscreenpublish", NodeConfigScreenPublish); // testdone
	NODE_SET_METHOD(exports, "isconfigscreenpublish", NodeIsScreenPublishEnable); //todo - done testdone
	NODE_SET_METHOD(exports, "configaudiopublish", NodeConfigAudioPublish); // testdone
	NODE_SET_METHOD(exports, "isconfigaudiopublish", NodeIsAudioPublishEnable); //todo - done testdone
	
	NODE_SET_METHOD(exports, "isautopublish", NodeIsAutoPublish); //todo - done testdone
	NODE_SET_METHOD(exports, "isautosub", NodeIsAutoSubscribe); //todo - done testdone
	NODE_SET_METHOD(exports, "isaudioonly", NodeIsAudioOnly); //todo - done testdone
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)
