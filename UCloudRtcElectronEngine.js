/**
 * URTCSdkEngine 引擎类
 */
import UCloudRtcSdkC from './plugin/lib/release/UCloudRtcElectronEngine.node';

export class UCloudRtcElectronEngine {
    constructor(urtcsdkengine) {
        this.urtcsdk = urtcsdkengine ;
    }

    /**
     * 初始化设备引擎
     * @param volstatefun 音频能量回调 fuction state(vol(int 0 --255) ) {}
     * @return Int 0 成功非0 失败
     */
    InitDevEngine(volstatefun){
        return this.urtcsdk.initdevengine(volstatefun) ;
    }
    UnInitDevEngine() {
        return this.urtcsdk.uninitdevengine() ;
    }
    /**
     * 获取摄像头个数
     * @return Int 0 成功非0 失败
     */
    GetCameraNums() {
        return this.urtcsdk.getcamnums() ;
    }
    /**
     * 获取摄像头设备信息  返回名称和设备id
     * @param pos 数组下标位置
     * @param jsonstr 设备信息 
     *  json格式  {
            deviceid:'',
            devicename:''
        };
     * @return Int 0 成功非0 失败
     */
    GetCameraInfo(pos, jsonstr) {
        return this.urtcsdk.getcamdevinfo(pos, jsonstr) ;
    }
    /**
     * 获取麦克风个数
     * @return Int 0 成功非0 失败
     */
    GetMicphoneNums() {
        return this.urtcsdk.getmicnums() ;
    }
    /**
     * 获取麦克风设备信息  返回名称和设备id
     * @param pos 数组下标位置
     * @param jsonstr 设备信息 
     *  json格式  {
            deviceid:'',
            devicename:''
        };
     * @return Int 0 成功非0 失败
     */
    GetMicphoneInfo(pos, jsonstr) {
        return this.urtcsdk.getmicdevinfo(pos, jsonstr) ;
    }
    /**
     * 获取扬声器数量
     * @return Int 0 成功非0 失败
     */
    GetPlayoutNums() {
        return this.urtcsdk.getplayoutnums() ;
    }
    /**
     * 获取扬声器设备信息  返回名称和设备id
     * @param pos 数组下标位置
     * @param jsonstr 设备信息 
     *  json格式  {
            deviceid:'',
            devicename:''
        };
     * @return Int 0 成功非0 失败
     */
    GetPlayoutInfo(pos, jsonstr) {
        return this.urtcsdk.getplayoutdevinfo(pos, jsonstr) ;
    }
    /**
     * 开始摄像头测试
     * @param devid 设备id 标识
     * @param wndview 窗口句柄参数 
     * @return Int 0 成功非0 失败
     */
    StartCameraTest(devid, wndview) {
        return this.urtcsdk.startcamtest(devid, wndview) ;
    }
    /**
     * 停止摄像头测试
     * @return Int 0 成功非0 失败
     */
    StopCameraTest() {
        return this.urtcsdk.stopcamtest() ;
    }
   /**
     * 开始麦克风测试
     * @param devid 设备id 标识
     * @return Int 0 成功非0 失败
     */
    StartMicphoneTest(devid) {
        return this.urtcsdk.startmictest(devid) ;
    }
   /**
     * 停止麦克风测试
     * @return Int 0 成功非0 失败
     */
    StopMicphoneTest() {
        return this.urtcsdk.stopmictest() ;
    }
    /**
     * 开始扬声器测试
     * @param devid 设备id 标识
     * @param dewavfilepathvid wav 格式文件地址
     * @return Int 0 成功非0 失败
     */
    StartPlayoutTest(devid, wavfilepath) {
        return this.urtcsdk.startplaytest(devid, wavfilepath) ;
    }
   /**
     * 停止扬声器测试
     * @return Int 0 成功非0 失败
     */
    StopPlayoutTest() {
        return this.urtcsdk.stopplaytest() ;
    }
    /**
     * 开始摄像头采集 用户获取videoframe 然后交给rtc 发送走
     * @param profile 参见 videoprofile
     * @return Int 0 成功非0 失败
     */
    StartVideoCapture(profile) {
        return this.urtcsdk.startvideocapture(profile) ;
    }
   /**
     * 停止摄像头采集
     * @return Int 0 成功非0 失败
     */
    StopVideoCapture() {
        return this.urtcsdk.stopvideocapture() ;
    }
    /**
     * 设置要使用的摄像头设备
     *  @param jsonstr 设备信息
     *  json格式  {
            deviceid:'',
            devicename:''
        };
     * @return Int 0 成功非0 失败
     */
    SetActiveCamera(jsonstr) {
        return this.urtcsdk.setactivecam(jsonstr) ;
    }
    /**
     * 设置要使用的麦克风设备
     *  @param jsonstr 设备信息
     *  json格式  {
            deviceid:'',
            devicename:''
        };
     * @return Int 0 成功非0 失败
     */
    SetActiveMicphone(jsonstr) {
        return this.urtcsdk.setactivemic(jsonstr) ;
    }
    /**
     * 设置要使用的扬声器设备
     *  @param jsonstr 设备信息
     *  json格式  {
            deviceid:'',
            devicename:''
        };
     * @return Int 0 成功非0 失败
     */
    SetActivePlayout(jsonstr) {
        return this.urtcsdk.setactiveplay(jsonstr) ;
    }
    /**
     * 设置麦克风的音量
     *  @param volume 音量 0 -- 255
     * @return Int 0 成功非0 失败
     */
    SetMicphoneVolume(volume) {
        return this.urtcsdk.setrecordvol(volume) ;
    }
    /**
     * 获取麦克风的音量
     * @return Int 0 --255
     */
    GetMicphoneVolume() {
        return this.urtcsdk.getrecordvol() ;
    }
    /**
     * 设置扬声器音量
     *  @param volume 音量 0 -- 255
     * @return Int 0 成功非0 失败
     */
    SetSpeakerVolume(volume) {
        return this.urtcsdk.setspeakervol(volume) ;
    }
    /**
     * 获取扬声器音量
     * @return Int  0 --255
     */
    GetSpeakerVolume() {
        return this.urtcsdk.getspeakervol() ;
    }

    /**
     * 初始化rtc 引擎
     * @param enginecallback 事件回调 fuction state(eventid, jsonmsg) {}
     * @return Int  0 成功 非0失败
     */
    InitRtcEngine(enginecallback) {
        return this.urtcsdk.initrtcengine(enginecallback) ;
    }
    /**
     * 销毁rtc 引擎
     * @return Int  0 --255
     */
    UnInitRtcengine() {
        return this.urtcsdk.uninitrtcengine() ;
    }
    /**
     * 销毁rtc 引擎
     * @return Int  0 --255
     */
    EnableVideoPreproc(enable) {
        return this.urtcsdk.enableextvideocapture(enable) ;
    }
    /**
     * 获取SDK 版本信息
     * @return string
     */
    GetSdkVersion() {
        return this.urtcsdk.getsdkversion() ;
    }
    /**
     * 设置SDK工作模式
     * @param mode 模式 0 正式模式 1 测试模式 正式模式自己生成key 
     * 测试模式传递token到sdk sdk 生成token
     * @return int 0 成功 非0失败
     */
    SetSdkMode(mode) {
        return this.urtcsdk.setsdkmode(mode) ;
    }
    /**
     * 设置sdk seckey
     * @param seckey 测试模式时 传入key 供SDK生成token
     * @return int 0 成功 非0失败
     */
    SetTokenSeckey(seckey) {
        return this.urtcsdk.settokenseckey(seckey) ;
    }
    /**
     * 设置本地流权限
     * @param role 0 发布权限 1 订阅权限 2 所有权限
     * @return int 0 成功 非0失败
     */
    SetStreamRole(role) {
        return this.urtcsdk.setstreamrole(role) ;
    }
    /**
     * 设置日志级别
     * @param level 0 debug 1 info 2 warb 3 error 4 不输出
     * @return int 0 成功 非0失败
     */
    SetLoglevel(level) {
        return this.urtcsdk.setloglevel(level) ;
    }
    /**
     * 设置媒体质量等级
     * @param profile 1 180p 2 240p 3 360p 4 480p 5 720p 6 1080p
     * @return int 0 成功 非0失败
     */
    SetVideoProfile(profile) {
        return this.urtcsdk.setvideoprofile(profile) ;
    }
    /**
     * 设置房间类型
     * @param chtype 1 实时互动 2 live
     * @return int 0 成功 非0失败
     */
    SetChannelType(chtype) {
        return this.urtcsdk.setchanneltype(chtype) ;
    }
    /**
     * 设置桌面采集输出等级
     * @param profile 1 低质量 2 中质量 3 高质量
     * @return int 0 成功 非0失败
     */
    SetScreenOutProfile(profile) {
        return this.urtcsdk.setscreenprofile(profile) ;
    }
    /**
     * 获取桌面数量
     * @return int 
    */
    GetScreenNums() {
        return this.urtcsdk.getscreennums() ;
    }
    /**
     * 设置桌面采集参数
     * @param jsonstr
     * {
         index:桌面索引
         x:x x 起始坐标
         y:y y 起始坐标
         width: 采集宽度
         height:采集高度
     * }
     * @return int 0 成功 非0失败
    */
    SetScreenCaptureProgram(jsonstr) {
        return this.urtcsdk.setscreencapturepragram(jsonstr) ;
    }
    /**
     * 设置纯音频模式
     * @param audioonly true 纯音频模式 false:非纯音频模式
     * @return int 0 成功 非0失败
    */
    SetAudioOnlyMode(audioonly) {
        return this.urtcsdk.setaudioonlymode(audioonly) ;
    }
    /**
     * 启动背景音添加
      * @param jsonstr
     * {
         filepath:本地文件路径 string
         repleace 是否替换micphone bool
         loop 是否循环播放
         vol: 背景音音量
     * }
     * @return int 0 成功 非0失败
    */
    StartAudioMixing(jsonbody) {
        return this.urtcsdk.startaudiomixing(jsonbody) ;
    }
    /**
     * 停止背景音混音
     * @return int 0 成功 非0失败
    */
    StopAudioMixing() {
        return this.urtcsdk.stopaudiomixing() ;
    }   
    /**
     * 设置自动发布订阅
     * @param autopub true 主动发布  false 手动调用发布 
     * @param autosub true 主动订阅 false 手动调用发布
     * @return int 0 成功 非0失败
    */
    SetAutoPubSub(autopub, autosub) {
        return this.urtcsdk.setaudopubsub(autopub, autosub) ;
    }
    /**
     * 加入房间
     * {
         uid:用户id string
         rid: 房间标识 string
         appid：应用id string
         token: 用户认证秘钥 string
     * }
     * @return int 0 成功 非0失败
    */
    JoinRoom(jsonstr) {
        return this.urtcsdk.joinroom(jsonstr) ;
    }
    /**
     * 离开房间
     * @return int 0 成功 非0失败
    */
    LeaveRoom() {
        return this.urtcsdk.leaveroom() ;
    }
    /**
     * 开始本地渲染
     * {
         view: 窗口句柄 int
         uid: 用户标识 string
         mytpe: 媒体流类型 int 1 camera 2 screen
         rmode: 适配模式 int 0 默认 1 适配比例 2 充满 可能变形
     * }
     * @return int 0 成功 非0失败
    */
    StartLocalRender(jsonstr) {
        return this.urtcsdk.startpreview(jsonstr) ;
    }
    /**
     * 停止本地渲染
     * {
         view: 窗口句柄 int
         uid: 用户标识 string
         mytpe: 媒体流类型 int 1 camera 2 screen
         rmode: 适配模式 int 0 默认 1 适配比例 2 充满 可能变形
     * }
     * @return int 0 成功 非0失败
    */
    StopLocalRender(jsonstr) {
        return this.urtcsdk.stoppreview(jsonstr) ;
    }
    /**
     * 发布本地媒体流
     * @param mtype: int  1 camera 2 screen
     * @param pubvideo: boolean  true 订阅视频 false 不订阅视频
     * @param pubaudio: boolean  true 订阅音频 false 不订阅音频
     * @return int 0 成功 非0失败
    */
    PublishStream(mtype, pubvideo, pubaudio) {
        return this.urtcsdk.publishstream(mtype, pubvideo, pubaudio) ;
    }
    /**
     * 取消发布本地媒体流
     * @param mtype: int  1 camera 2 screen
     * @return int 0 成功 非0失败
    */
    UnPublishStream(mtype) {
        return this.urtcsdk.unpublishstream(mtype) ;
    }
    /**
     * 打开关闭本地音频
     * @param mute: boolean  true 关闭音频 false 打开音频
     * @return int 0 成功 非0失败
    */
    MuteLocalAudio(mute) {
        return this.urtcsdk.mutelocalaudio(mute) ;
    }
    /**
     * 打开关闭本地视频流
     * @param mtype: int  1 camera 2 screen
     * @param mute: boolean  true 关闭视频流 false 打开视频流
     * @return int 0 成功 非0失败
    */
    MuteLocalVideo(mtype ,mute) {
        return this.urtcsdk.mutelocalvideo(mtype, mute) ;
    }
    /**
     * 开始远端视频渲染
     * @param jsonstr:  string json 格式
     * {
        view: 窗口句柄 int
        uid: 用户标识 string
        mytpe: 媒体流类型 int 1 camera 2 screen
        rmode: 适配模式 int 0 默认 1 适配比例 2 充满 可能变形
     * }
     * @return int 0 成功 非0失败
    */
    StartRemoteRender(jsonstr) {
        return this.urtcsdk.startremoteview(jsonstr) ;
    }
    /**
     * 停止远端视频渲染
     * @param jsonstr:  string json 格式
     * {
        view: 窗口句柄 int
        uid: 用户标识 string
        mytpe: 媒体流类型 int 1 camera 2 screen
        rmode: 适配模式 int 0 默认 1 适配比例 2 充满 可能变形
    * }
    * @return int 0 成功 非0失败
    */
    StopRemoteRender(jsonstr) {
        return this.urtcsdk.stopremoteview(jsonstr) ;
    }
    /**
     * 订阅远端媒体流
     * @param jsonstr:  string json 格式
     * {
        uid: 用户标识 string
        audio: 是否订阅音频 boolean true 订阅 false 不订阅
        video: 是否订阅视频 boolean true 订阅 false 不订阅
        mtype: 媒体流类型 int 1 camera 2 screen
     * }
     * @return int 0 成功 非0失败
    */
    SubscribeStream(jsonstr) {
        return this.urtcsdk.subscribestream(jsonstr) ;
    }
    /**
     * 取消订阅远端媒体流
     * @param jsonstr:  string json 格式
     * {
        uid: 用户标识 string
        audio: 默认填 false
        video: 默认填 false
        mtype: 媒体流类型 int 1 camera 2 screen
     * }
     * @return int 0 成功 非0失败
    */
    UnSubscribeStream(jsonstr) {
        return this.urtcsdk.unsubscribestream(jsonstr) ;
    }
    /**
     * 打开关闭远端音频
     * @param jsonstr:  string json 格式
     * {
        uid: 用户标识 string
        mute: 是否关闭远端音频 boolean true 关闭 false 打开
        mtype: 媒体流类型 int 填1 即可
     * }
     * @return int 0 成功 非0失败
    */
    MuteRemoteAudio(jsonstr) {
        return this.urtcsdk.muteremoteaudio(jsonstr) ;
    }
    /**
     * 打开关闭远端视频流
     * @param jsonstr:  string json 格式
     * {
        uid: 用户标识 string
        mute: 是否关闭远端视频流 boolean true 关闭 false 打开
        mtype: 媒体流类型 int 填1 即可
     * }
     * @return int 0 成功 非0失败
    */
    MuteRemoteVideo(jsonstr) {
        return this.urtcsdk.muteremotevideo(jsonstr) ;
    }
    /**
     * 开启会议录制
     * @param jsonstr:  string json 格式
     * {
        mainuid: 录制视频时主窗口用户id string
        mvtype: 录制视频时主窗口视频类型 int 1 摄像头 2 桌面
        profile: 录制视频时对外输出等级 int 1 标清 2 高清 3 超高清
        rtype:  录制类型 int 1 录制混音 2 录制音视频混流
        wpos: 录制视频时水印位置 1 左上 2 左下 3 右上 4 右下
        bucket: "urtcrecord" ufile 对应的bucket 地址
        region: "cn-bj" ufile bucket所在的地区
     * }
     * @return int 0 成功 非0失败
    */
    StartRoomRcord(jsonstr) {
        return this.urtcsdk.startrecord(jsonstr) ;
    }
    /**
     * 停止会议录制
     * @return int 0 成功 非0失败
    */
    StopRoomRecord() {
        return this.urtcsdk.stoprecord() ;
    }
    /**
    * 配置主动发布时 摄像头是否发布(默认同时控制音频)
    * @param enable 启用摄像头发布 boolean true 发布 false 不发布
    * @return int 0 成功 非0失败
    */
    ConfigCameraPublish(enable) {
        return this.urtcsdk.configcamerapublish(enable) ;
    }
    /**
    * 配置主动发布时 是否启用摄像头发布
    * @return true 发布 false 不发布
    */
    IsConfigCameraPublish() {
        return this.urtcsdk.isconfigcampublish() ;
    }
    /**
    * 配置主动发布时 桌面是否发布
    * @param enable 启用桌面发布 boolean true 发布 false 不发布
    * @return int 0 成功 非0失败
    */
    ConfigScreenPublish(enable) {
        return this.urtcsdk.configscreenpublish(enable) ;
    }
    /**
    * 配置主动发布时 否启用桌面发布
    * @return true 发布 false 不发布
    */
    IsConfigScreenPublish() {
        return this.urtcsdk.isconfigscreenpublish() ;
    }
    /**
    * 配置主动发布时 音频是否发布
    * @param enable 启用音频发布 boolean true 发布 false 不发布
    * @return int 0 成功 非0失败
    */
    ConfigAudioPublish(enable) {
        return this.urtcsdk.configaudiopublish(enable) ;
    }
    /**
    * 配置主动发布时 否启用音频发布
    * @return true 发布 false 不发布
    */
    IsConfigAudioPublish() {
        return this.urtcsdk.isconfigaudiopublish() ;
    }
    /**
    * 是否启用主动发布
    * @return true 自动发布 false 手动调用接口发布
    */
    IsAutoPublish() {
        return this.urtcsdk.isautopublish() ;
    }
    /**
    * 是否启用主动订阅
    * @return true 自动订阅 false 手动调用接口订阅
    */
    IsAutoSubscribe() {
        return this.urtcsdk.isautosub() ;
    }
    /**
    * 是否为纯音频模式
    * @return true 纯音频模式 false 非纯音频模式
    */
    IsAudioOnlyMode() {
        return this.urtcsdk.isaudioonly() ;
    }
    /**
     * 美颜
     * @return Int 0 成功非0 失败
     */
    InitBeautyEngine(wnd) {
        return this.urtcsdk.initbeautyengine(wnd) ;
    }
    /**
     * 美颜
     * @return Int 0 成功非0 失败
     */
    UnInitBeautyEngine() {
        return this.urtcsdk.uninitbeautyengine() ;
    }
    /**
     * 设置道具
     * @return Int 0 成功非0 失败
     */
    SelectBundle(path) {
        return this.urtcsdk.selectbundle(path) ;
    }
    /**
     * 美颜
     * @return Int 0 成功非0 失败
     */
    BeautifyFrame() {
        return this.urtcsdk.beautyframe() ;
    }
    /**
     * 挂件加美颜
     * @return Int 0 成功非0 失败
     */
    AddFrameItme() {
        return this.urtcsdk.addframeitem() ;
    }
}

// rtc 引擎类
export const urtcSdk = new UCloudRtcElectronEngine(UCloudRtcSdkC);