# 1 描述
URTCelectron 是UCloud推出的一款适用于 Windows 平台的实时音视频 SDK，支持windows7 及以上系统，提供了音视频通话基础功能，提供灵活的接口，支持高度定制以及二次开发，支持electron2.0.7及以上版本，URTCSdkEngine.js 为SDK接口类。如果使用c++ 请参考[urtc-win-demo](https://github.com/ucloud/urtc-win-demo.git)。
# 2 功能列表
## 2.1 基本功能
* 基本的音视频通话功能	
* 支持内置音视频采集的常见功能	
* 支持静音关闭视频功能	
* 支持视频尺寸的配置(180P - 1080P)	
* 支持自动重连	
* 支持丰富的消息回调	
* 支持纯音频互动	
* 支持视频的大小窗口切换	
* 支持获取视频房间统计信息（帧率、码率、丢包率等）	
* 支持编码镜像功能		
* 支持屏幕录制功能	
## 2.2 增值功能
* 电子白板
* 终端智能测试（摄像头、麦克风、网络、播放器）
* AI鉴黄
* 视频录制/视频存储
* 视频水印
* 视频直播CDN分发
* 美颜
* 贴纸/滤镜/哈哈镜
* 背景分割
* 手势
* 虚拟形象
* 变声
# 3 方案介绍
## 3.1 方案架构
![](http://urtcwater.cn-bj.ufileos.com/%E5%9B%BE%E7%89%871.png)
## 3.2 方案优势
* 利用边缘节点就近接入
* 可用性99.99%
* 智能链路调度
* 自有骨干专线+Internet传输优化
* 数据报文AES加密传输
* 全API开放调度能力
* 端到端链路质量探测
* 多点接入线路容灾
* 抗丢包视频30% 音频70%
* 国内平均延时低于75ms 国际平均延时低于200ms
# 4 应用场景
## 4.1 主播连麦
支持主播之间连麦一起直播，带来与传统单向直播不一样的体验
48KHz 采样率、全频带编解码以及对音乐场景的特殊优化保证观众可以听到最优质的声音
## 4.2 视频会议
小范围实时音视频互动，提供多种视频通话布局模板，更提供自定义布局方式，保证会议发言者互相之间的实时性，提升普通观众的观看体验
## 4.3 泛文娱
### 4.3.1 一对一社交
客户可以利用UCloud实时音视频云实现 QQ、微信、陌陌等社交应用的一对一视频互动
### 4.3.2 狼人杀游戏
支持15人视频通话，玩家可在游戏中选择只开启语音或同时开启音视频
## 4.4 在线教育
支持自动和手动发布订阅视频流，方便实现课堂虚拟分组概念，同时支持根据角色设置流权限，保证课程秩序
## 4.5 在线客服
线上开展音视频对话，对客户的资信情况进行审核，方便金融科技企业实现用户在线签约、视频开户验证以及呼叫中心等功能
提供云端存储空间及海量数据的处理能力，提供高可用的技术和高稳定的平台
# 5 demo 编译使用
## 5.1 环境准备
1 安装nodejs 安装8.x 版本， 10版本会有问题  本demo 安装 8.9.4
2 安装node-gyp 安装node-gyp@3.5.0 之后的版本可能不支持vs2015 ，只能支持vs2017编译，demo采用node-gyp@3.5.0
npm install -g node-gyp@3.5.0
3 安装python 2.x 版本，不支持3.x 版本，并设置到环境变量中去
4 git clone 
5 进入工程根目录  
npm i electron --arch=ia32 --save-dev   安装electron 版本
6 npm install 安装js 依赖
7 node-gyp rebuild --target=2.0.8 --arch=ia32 --dist-url=https://atom.io/download/electron 编译插件
编译好的库位于 更目录 build/release 目录下
8 将库拷贝到 pulgin/lib/release 目录下
9 调试打包
## 5.2 调试
打开根目录 index.js 文件
注释掉 mainWindow.loadFile('dist/index.html')  
取消 mainWindow.loadURL('http://localhost:3000/index.html') 的注释
然后在根目录运行 npm run react-start  (运行该命令的窗口不要关闭)
然后在根目录运行 npm start 
## 5.3 打包
打开根目录 index.js 文件
取消 mainWindow.loadFile('dist/index.html') 的注释
注释掉 mainWindow.loadURL('http://localhost:3000/index.html')
然后在根目录运行 npm run react-build    
然后在根目录运行 npm run build-win
## 5.4 常见问题
### node-gyp.js 找不到 解决方案
set npm_config_node_gyp=C:\Users\usser\AppData\Roaming\npm\node_modules\node-gyp\bin\node-gyp.js
### 找不到python
npm config set python python
### 找不到编译工具
npm config set msvs_version 2015
# 6 正式环境接入使用
## 6.1 开发语言以及系统要求
开发语言：C++ + javascript
系统要求：Windows 7 及以上版本的 Windows 系统
## 6.2 开发环境
### 6.2.1 C++ 开发，自己编译electron SDK
Visual Studio 2015 开发环境 
Win32 Platform 
### 6.2.2 Javascript 开发
* 拷贝工程中URTCSdkEngine.js(java script 接口封装实现)， 拷贝pulgin到自己的目录下，注意URTCSdkEngine.js 中node文件引用路 径为./plugin/lib/release/urtcelectron.node，请保持路径正确，或者更改为自己的目录地址。
* 在文件中引：import {urtcSdk} from '../URTCSdkEngine';
## 6.3 初始化
### 6.3.1 实现eventcallback funtion实现回调处理
var eventMap={
    5000:function(){
        com.addLog('success',"ok");
    },
    5001:function () {
        com.addLog('error','服务器连接断开');
    },
    5002:function (resp,com) {
        //加入房间
    },
    5003:function (resp,com) {
        //离开房间
    },
    5004:function (resp,com) {
        //重连中
    },
    5005:function (resp,com) {
        //重连成功
    },
    5006:function (resp,com) {
        //视频发布成功
    },
    5007:function (resp,com) {
        //取消媒体 {code:0 msg:msg, data:{}}
    },
    5008:function (resp,com) {
       // 用户加入房间
    },
    5009:function (resp,com) {
       // 用户离开房间
    },
    5010:function (resp,com) {
       // 房间内新媒体发布
    },
    5011:function (resp,com) {
         //房间内有媒体流移除
    },
    5012:function (resp,com) {
        //订阅媒体流响应
   },
   5013:function (resp,com) {
        // 取消订阅媒体流响应
    },
    5014:function (resp,com) {
        // mute  本地媒体流响应
    },
    5015:function (resp,com) {
       // mute 远端媒体流响应
    },
    5016:function (resp,com) {
        // 远端媒体流变化
    },
    5019:function (resp,com) {
        //开始录制请求响应
    },
    5020:function (resp,com) {
        //停止请求录制响应
    }
}
initEngine = (eventId,objectStr)=>{
    if(!objectStr){
        objectStr = "{}";
    }
    var fun = enentMap[eventId];
    // console.log(eventId,objectStr);
    this.addLog('info',`SDK返回 ${eventId}:${objectStr}`);
    if(fun){
         fun(JSON.parse(objectStr),this);
    }
 }
### 6.3.2 调用接口初始化
urtcSdk.InitRtcEngine(initEngine);
       urtcSdk.SetSdkMode(1) ; 
       urtcSdk.SetStreamRole(2) ;
       urtcSdk.SetAudioOnlyMode(false) ;
       urtcSdk.SetAutoPubSub(false, false) ;
       urtcSdk.SetVideoProfile(1) ;
       urtcSdk.SetScreenOutProfile(2) ;
       urtcSdk.SetTokenSeckey("9129304dbf8c5c4bf68d70824462409f") ;
## 6.4 加入房间
const jsonarg = {} ;
          jsonarg.uid = userid ;
          jsonarg.rid = roomid ;
          jsonarg.appid = "URtc-h4r1txxy" ;// test appid 
          const jsonStr = JSON.stringify(jsonarg) ;
          console.log("joinroom : "+ jsonStr) ;
          urtcSdk.JoinRoom(jsonStr);
## 6.5 发布 取消发布
### 发布流：
urtcSdk.PublishStream(1,this.mediaConfig.videoenable, this.mediaConfig.audioenable);
### 取消发布：
urtcSdk.UnPublishStream(1);
## 6.6 订阅流 取消订阅
### 订阅流：
const jsonarg = {} ;
jsonarg.uid = userid ;
jsonarg.audio = true ;
jsonarg.video = true; 
jsonarg.mtype = 1;
const jsonStr = JSON.stringify(jsonarg) ;
console.log("joinroom : "+ jsonStr) ;
urtcSdk. SubscribeStream (jsonStr);
### 取消订阅：
const jsonarg = {} ;
jsonarg.uid = userid ;
jsonarg.audio = true ;
jsonarg.video = true; 
jsonarg.mtype = 1;
const jsonStr = JSON.stringify(jsonarg) ;
console.log("joinroom : "+ jsonStr) ;
urtcSdk. UnSubscribeStream (jsonStr);
## 6.7 离开房间
urtcSdk.LeaveRoom()
##6.8 编译运行
开始体验demo

