import React from 'react';
import PropTypes from 'prop-types';
import {render} from 'react-dom';

const electron = require('electron');
const ipcRenderer = electron.ipcRenderer;
const {BrowserWindow} = electron.remote;

import { Layout } from 'antd';
const { Header, Footer, Sider, Content } = Layout;

import PageHeader from './Header';
import PageContent from './PageContent';
import VideoList from './VideoList';
import PageBottom from './PageBottom';
import AlertMsg from './AlertMsg';
import {version} from '../package';
import {
    createWindow,
    getSdk,
    getTime,
    decodeUserInfo,
    getLocalUserInfo,
    messageHanddle,
    setLocalUserInfo
} from "./Util";

import './style/app.less'
import {saveLog} from "./Log";

//父窗口
let parent = null;
//父窗口是否显示
let windowIsShow = true;
//向主进程去获取主窗口
ipcRenderer.send('get-parent-window');
ipcRenderer.on('send-parent-window',(event,win)=>{
    parent = BrowserWindow.fromId(win.winId);
    //放在这里渲染是为了等到获取到 parent以后再开始渲染页面
    render(<App />, document.getElementById('app'));
})
//父窗口最小化
ipcRenderer.on('window-minimized',(a,b)=>{
    windowIsShow = false;
})
//父窗口还原
ipcRenderer.on('window-restored',(a,b)=>{
    windowIsShow = true;
})

/**
 * 处理新流的加入问题
 * @param videos 原始的流数组
 * @param userId 新流的用户ID
 * @param video 新的流
 */
const addStream = (videos,video) => {
    const userId = video.userId;
    //是否是新成员推入的流
    let oldUser = false;
    for(let i=0,len=videos.length;i<len;i++){
        const vi = videos[i];
        if(vi.userId === userId){
            //如果当前用户没有流，就直接替换
            if(!vi.streamid){
                videos[i] = video;
            }else{
                //如果当前用户已有流，就再加入一个记录
                videos.push(video);
            }
            oldUser = true;
        }
    }
    if(!oldUser){
        videos.push(video);
    }
}

/**
 * 处理移除流
 * @param videos 所有的视频流
 * @param streamid 被移除的流id
 */
const removeStream = (videos,streamid) => {
    for(let i=0,len=videos.length; i<len; i++){
        const v = videos[i];
        if(v.streamid === streamid){
            const user = videos.filter(vi=> vi.userId === v.userId);
            //如果当前用户有多个流，就干掉当前流的所有信息
            if(user.length > 1){
                videos.splice(i,1);
            }else{
                //如果当前用户只有一个流，就只干掉流信息保留用户
                videos[i] = { userId:v.userId, userName:v.userName };
            }
            break;
        }
    }
}

var enentMap={
    5000:function(){
        com.addLog('success',"ok");
    },
    5001:function () {
        com.addLog('error','服务器连接断开');
    },
    5002:function (resp,com) {
        //加入房间
        const code = resp.code;
        const msg = resp.msg;
        
        console.log("joinroom "+ JSON.stringify(resp)) ;
        if(code == 0 ) {
            const uid = resp.data.uid;
            const roomid = resp.data.roomid;
            const userinfo = {} ;
            userinfo.roomid = roomid ;
            userinfo.fullname = uid+ "_"+ roomid ;
            setLocalUserInfo(userinfo.fullname) ;
            com.updateRommId(roomid);
            let videos = [];
            const localUser = getLocalUserInfo();
            videos.push(localUser);
            com.setState({videos});
            com.addLog('success','加入房间成功！当前房间ID：'+ roomid);
        }else {
            const errorMsg = `加入房间失败->${resp.code} : ${resp.msg}`
            com.addLog('error',errorMsg);
            messageHanddle.emit('joinroom-fail',{content:errorMsg});
        }
        
    },
    5003:function (resp,com) {
        //离开房间
        com.addLog('success','离开房间成功！');
        let allVideoWindows = com.state.allVideoWindows;
        //关闭所有视频窗口
        for(let key in allVideoWindows){
            const win = allVideoWindows[key];
            if('localCam' === key || 'localScreen' === key){
                win.setContentSize(160,90);
                win.hide();
            }else{
                win.close();
                delete allVideoWindows[key];
            }
        }
        //如果大的预览窗口在，就关掉它
        if(com.bigPreview){
            try {
                com.bigPreview.close();
            }catch (e) {}
        }
        //清空用户列表和视频列表  将推流状态也设置为否
        com.setState({videos:[],allVideoWindows,roomId:'',camPushing:false,screenPushing:false,recording:false});
    },
    5004:function (resp,com) {
        //重连中
        com.addLog('warning','服务器重连中……');
    },
    5005:function (resp,com) {
        //重连成功
        com.addLog('success','服务器重连成功');
    },
    5006:function (resp,com) {
        //视频发布成功
        const code = resp.code;
        const msg = resp.msg;
        const uid = resp.data.uid;
        const roomid = resp.data.roomid;
        if(code == 0) {
            com.addLog('success','发布媒体内容成功！');
            const localUser = getLocalUserInfo();
            const video = resp.data || {};
            const videos = com.state.videos;
            video.userName =  localUser.userName;
            video.userId = localUser.userId;
            video.isLocal = true;
            video.muteaudio = false ;
            video.mutevideo = false ;
            video.video = true ;
            video.audio = true ;
            console.log(" video mtype "+ video.mtype) ;
            if(video.mtype == 1) {
                const localView  = com.state.allVideoWindows.localCam ;
                video.streamid = "localCam";
                addStream(videos,video);
                const jsonarg = {} ;
                jsonarg.uid = video.userId ;
                jsonarg.view = localView.getNativeWindowHandle().readInt32LE() ;
                jsonarg.mtype = video.mtype ;
                jsonarg.rmode = 1 ;
                getSdk(true).then(resp=>{
                    const urtcSdk = resp.urtcSdk;
                    const jsonStr = JSON.stringify(jsonarg) ;
                    console.log("startlocalpreview camera : "+ jsonStr) ;
                    urtcSdk.StartLocalRender(jsonStr) ;
                })
                com.setState({videos,camPushing:true},() => {
                    localView.show();
                 });
            }else if(video.mtype == 2) {
                const localView  = com.state.allVideoWindows.localScreen ;
                video.streamid = "localScreen";
                addStream(videos,video);
                const jsonarg = {} ;
                jsonarg.uid = video.userId ;
                jsonarg.view = localView.getNativeWindowHandle().readInt32LE() ;
                jsonarg.mtype = video.mtype ;
                jsonarg.rmode = 1 ;
                getSdk(true).then(resp=>{
                    const urtcSdk = resp.urtcSdk;
                    const jsonStr = JSON.stringify(jsonarg) ;
                    console.log("startlocalpreview screen : "+ jsonStr) ;
                    urtcSdk.StartLocalRender(jsonStr) ;
                })
                com.setState({videos,screenPushing:true},() => {
                     localView.show();
                 });
            } 
        }else{
            //
        }
       
    },
    5007:function (resp,com) {
        //取消媒体 {code:0 msg:msg, data:{}}
        com.addLog('success','取消发布媒体内容成功！');
        const { videos, allVideoWindows } = com.state;
        const win = allVideoWindows['localCam'];
        const code = resp.code ;
        const msg = resp.msg ;

        const mtype = resp.data.mtype ;
        if(code == 0) {
            if(mtype == 1) {
                com.addLog('success','取消发布媒体内容成功！');
                const { videos, allVideoWindows } = com.state;
                const win = allVideoWindows['localCam'];
                //再将窗口缩小，再隐藏，免得下次发布时 直接出现大的画面
                win.setContentSize(160,90);
                win.hide();
                //从视频列表中删除摄像头
                removeStream(videos,'localCam');
                com.setState({camPushing:false, videos});
            }else if(mtype == 2) {
                com.addLog('success','取消发布桌面内容成功！');
                const { allVideoWindows, videos } = com.state;
                const win = allVideoWindows['localScreen'];
                //再将窗口缩小，再隐藏，免得下次发布时 直接出现大的画面
                win.setContentSize(160,90);
                win.hide();
                //删除本地桌面
                removeStream(videos,'localScreen');
                com.setState({screenPushing:false,videos});
            }
        }else {

        }
    },
    5008:function (resp,com) {
        let { videos, allVideoWindows, roomId} = com.state;
        // console.log(" resp.data.roomId** "+ roomId) ;
        // console.log(" resp.data.uid "+ resp.data.uid) ;
        const userInfo = {} ;
        userInfo.userId = resp.data.uid ;
        userInfo.userName = resp.data.uid ;
        //console.log("userinfo "+ JSON.stringify(userInfo)) ;
        const video = userInfo;
        addStream(videos,userInfo);
        //console.log(" resp.data.roomid "+ roomId) ;
        com.addLog('success','用户：'+userInfo.userName+' 加入房间！');
        com.setState({videos});
    },
    5009:function (resp,com) {
        com.addLog('success','用户：'+resp.data.uid+' 离开房间！');
        let { videos, allVideoWindows, roomId} = com.state;
        const newVideos = [];
        const userId = resp.data.uid;
        videos.map(video => {
            if(video.userId === userId){
                const streamId = video.streamid;
                com.addLog('success','用户：'+resp.data.uid+' streamId :'+streamId);
                const win = allVideoWindows[streamId];
                if(streamId && win){
                    if(video.isLocal){
                        win.hide();
                    }else{
                        win.close();
                        delete allVideoWindows[streamId];
                    }
                }
            }else{
                newVideos.push(video);
            }
        })
        videos = newVideos;
        com.setState({videos});
    },
    5010:function (resp,com) {
        let { videos, allVideoWindows,roomId } = com.state;
       // let  data = {} | resp.data ;
        const video = {};
        video.userName =  resp.data.uid;
        video.userId = resp.data.uid;
        video.streamid = resp.data.uid+ resp.data.mtype ;
        video.video = resp.data.video ;
        video.audio = resp.data.audio ;
        //流发布消息
        com.addLog('success','有新的流加入->'+video.streamid);
        //有视频流加入
        let win = createWindow({parent:parent});
        allVideoWindows[video.streamid] = win;
        com.addLog('success','addstream '+JSON.stringify(video));
        addStream(videos,video);
        const mtype = resp.data.mtype ;
        //com.addLog('success','addstream '+JSON.stringify(video));
        com.setState({videos,allVideoWindows},() => {
            //拉流
            getSdk().then(resp=>{
                const jsonarg = {} ;
                jsonarg.uid = video.userId ;
                jsonarg.video = video.video ;
                jsonarg.audio = video.audio ;
                jsonarg.mtype = mtype ;
                const jsonStr = JSON.stringify(jsonarg) ;
                com.addLog('success','substream '+jsonStr);
                console.log("substream "+ jsonStr) ;
                resp.urtcSdk.SubscribeStream(jsonStr);
            }).catch(ex=>{
                com.addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
            })
        });
    },
    5011:function (resp,com) {
         //有视频流离开
         let { videos, allVideoWindows } = com.state;
         const streamid = resp.data.uid+resp.data.mtype ;
         const win = allVideoWindows[streamid];
         if(win){
             win.close();
         }
         delete allVideoWindows[streamid];
         //有视频流离开
         removeStream(videos,streamid);
         com.setState({videos,allVideoWindows});
    },
    5012:function (resp,com) {
        //订阅结果
        const code = resp.code ;
        const msg = resp.msg ;
        if(code == 0) {
            const uid = resp.data.uid ;
            const mtype = resp.data.mtype ;
            const streamId= uid+mtype;
            const win = com.state.allVideoWindows[streamId];
            const videos = com.state.videos;
            videos.map(video=>{
                if(video.streamid === streamId){
                    video.mutevideo = false;
                    video.muteaudio = false;

                    getSdk().then(resp=>{
                        const jsonarg = {} ;
                        jsonarg.uid = video.userId ;
                        jsonarg.view = win.getNativeWindowHandle().readInt32LE() ;
                        jsonarg.rmode = 1 ;
                        jsonarg.mtype = mtype ;
                        const jsonStr = JSON.stringify(jsonarg) ;
                        com.addLog('success','startremoteview '+jsonStr);
                        console.log("startremoteview "+ jsonStr) ;
                        resp.urtcSdk.StartRemoteRender(jsonStr);
                    }).catch(ex=>{
                        com.addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
                    }) ;
                    //显示出视频的画面
                    if(windowIsShow && win){
                        win.show();
                    }
                    video.unSubscribeed = false;
                }
            })
            com.setState({videos});
        }
   },
   5013:function (resp,com) {
        com.addLog('success','取消订阅成功！');
        const videos = com.state.videos;
        const uid = resp.data.uid ;
        const mtype = resp.data.mtype ;
        const streamId = uid+mtype;
        const win = com.state.allVideoWindows[streamId];
        if(win){
            win.hide();
        }
        videos.map(video=>{
            if(video.streamid === resp.data.streamid){
                video.unSubscribeed = true;
            }
        })
        com.setState({videos});
    },
    5014:function (resp,com) {
        // mute 本地媒体
        com.addLog('success','开启/关闭本地音频成功！');
        const videos = com.state.videos;
        const mtype = resp.data.mtype ;
        const ttype = resp.data.ttype ;
        if(mtype == 1) {
            if(ttype == 0) {
                videos.map(video=>{
                    if('localCam' === video.streamid){
                        video.muteaudio = !video.muteaudio;
                    }
                })
            }else if(ttype == 1) {
                videos.map(video=>{
                    if('localCam' === video.streamid){
                        video.mutevideo = !video.mutevideo;
                    }
                })
            }
        }else if(mtype == 2) {
            videos.map(video=>{
                if('localScreen' === video.streamid){
                    video.mutevideo = !video.mutevideo;
                }
            })
        }
        com.setState({videos});
    },
    5015:function (resp,com) {
        com.addLog('success','开启/关闭远端视频成功！');
        const videos = com.state.videos;
        const mtype = resp.data.mtype ;
        const ttype = resp.data.ttype ;
        const streamid = resp.data.uid+mtype ;
        if(ttype == 0) {
            for(let i=0,len=videos.length;i<len;i++){
                let video = videos[i];
                if(streamid === video.streamid){
                    video.muteaudio = resp.data.mute;
                    videos[i] = video;
                    break;
                }
            }
            
        }else if(ttype == 1) {
            for(let i=0,len=videos.length;i<len;i++){
                let video = videos[i];
                if(streamid === video.streamid){
                    video.mutevideo = resp.data.mute;
                    videos[i] = video;
                    break;
                }
            }
        }

        com.setState({videos});
    },
    5016:function (resp,com) {
        com.addLog('success','远端媒体流变化');
        const videos = com.state.videos;
        const mtype = resp.data.mtype ;
        const ttype = resp.data.ttype ;
        const streamid = resp.data.uid+mtype ;

       
        com.setState({videos});
        if(mtype == 1) {
            if(ttype == 0) {
                for(let i=0,len=videos.length;i<len;i++){
                    const v = videos[i];
                    if(v.streamid === streamid){
                        v.video = resp.data.mute;
                        break;
                    }
                }
            }else if(ttype == 1) {
                for(let i=0,len=videos.length;i<len;i++){
                    const v = videos[i];
                    if(v.streamid === streamid){
                        v.audio = resp.data.mute;
                        break;
                    }
                }
            }
        }else if(mtype == 2) {
            for(let i=0,len=videos.length;i<len;i++){
                const v = videos[i];
                if(v.streamid === streamid){
                    v.video = resp.data.mute;
                    break;
                }
            }
        }
        com.setState({videos});
    },
    5019:function (resp,com) {
        //录制请求响应
        const code = resp.code;
        const msg = resp.msg;
        const recordid = resp.data.recordid;
        const videos = com.state.videos;
        if(code == 0) {
            com.addLog('success','发起录制成功！');
            com.setState({videos,recording:true},() => {
            });
        }else{
            com.addLog('success','发起录制失败 ！'+msg);
            com.setState({videos,startrecording:false},() => {
            });
        }
       
    },
    5020:function (resp,com) {
        //录制请求响应
        const code = resp.code;
        const msg = resp.msg;
        const recordid = resp.data.recordid;
        const videos = com.state.videos;
        if(code == 0) {
            com.addLog('success','停止录制成功！');
            com.setState({videos,recording:false},() => {
            });
        }else{
            com.addLog('success','停止录制失败 ！'+msg);
        }
       
    }
}

class App extends React.Component{
    constructor(props){
        super(props);
        this.state={
            //当前房间的roomid
            roomId:'',
            //视频列表
            videos:[],
            //摄像头正在推流
            camPushing:false,
            //正在推桌面流
            screenPushing:false,
            recording:false,
            //所有的窗口
            allVideoWindows:{
                localCam:createWindow({parent:parent}),
                localScreen:createWindow({parent:parent})
            }
        }
    }
    componentDidMount(){
        //页面关闭或刷新时关闭所有小窗口
        window.addEventListener('beforeunload',() => {
            const { allVideoWindows } = this.state;
            for(let key in allVideoWindows){
                const win = allVideoWindows[key];
                if(win){
                    win.close();
                }
            }
        })
    }
    /**
     * 添加日志
     * @param content 日志内容
     * @param type 日志类型
     */
    addLog=(type,content)=>{
        saveLog(type,content);
        //只显示错误和警告信息
        if(type === 'warning' || type === 'error'){
            messageHanddle.emit('app-message',{type,content});
        }
    }
    /**
     * 更新房间ID
     * @param roomId
     */
    updateRommId= roomId => {
        this.setState({roomId});
    }

    //在渲染后调用
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

    setBigPreview = (streamId) => {
        const { videos , allVideoWindows } = this.state;
        videos.map(video => {
            if(video.streamid === streamId){
                video.isBig = true;
            }else{
                //将大窗口改小
                if(video.isBig === true && video.streamid){
                    const win = allVideoWindows[video.streamid];
                    if(win){
                        win.setContentSize(160,90);
                    }
                }
                video.isBig = false;
            }
        });
        this.setState({videos});
    }

    render(){
        const {roomId,allVideoWindows,videos,logs,screenPushing,camPushing,recording} = this.state;
        //将有视频的放前面
        videos.sort((a,b)=>{
            const flag1 = b.streamid ? 1 : -1;
            const flag2 = a.streamid ? 1 : -1;
            return flag1 - flag2;
        });
        let bigindex = -1;
        let sipleVideo = videos[0] || {};
        //是否已找到大的视频
        let findBigVideo = false;
        //是否已找到发布了2个视频的人
        let findtwoVideo = false;
        //统计每个人的视频数集合
        const twoVideousers = {};
        for(let i=0,len=videos.length;i<len;i++){
            let video = videos[i];
            const { isBig, streamid, userId } = video;
            //将放大的窗口调到第一位
            if(isBig){
                bigindex = i;
                sipleVideo = videos[bigindex];
                findBigVideo = true;
            }
            //统计有两个视频的人
            if(streamid){
                if(twoVideousers[userId]){
                    twoVideousers[userId]++;
                    findtwoVideo = true
                }else{
                    twoVideousers[userId] = 1;
                }
            }
            //如果大视频和有2个视频的人都找到  就跳出循环
            if(findBigVideo && findtwoVideo){
                break;
            }
        }
        //将放大的视频调到第一位
        if(bigindex>0){
            videos.splice(bigindex,1);
            videos.unshift(sipleVideo);
        }
        //选一个放大的视频 默认第一个
        if(videos.length > 0 && bigindex === -1 && videos[0].streamid){
            videos[0].isBig = true;
        }

        //验证一下是否有人发了两个视频（同时发了本地和桌面）
        const userObj = {};
        for(let i=0,len = videos.length;i<len;i++){
            const video = videos[i];
            if(video.streamid){
                userObj.userId = 1;
            }
        }

        //没有加入房间时的界面
        const notLoginDom = <Layout>
            <Content>
                <PageHeader parentWindow={parent} addLog={this.addLog} initEngine={this.initEngine}/>
                <div className="page-content-warpper">
                    <div className="empty-data-warpper">
                        当前版本号：{version}
                    </div>
                </div>
            </Content>
        </Layout>;
        //加入房间后的界面
        const loginedDom = <Layout>
            <Content>
                <PageContent roomId={roomId} addLog={this.addLog} parentWindow={parent} videoWindow={allVideoWindows[sipleVideo.streamid]} video={sipleVideo}/>
                <PageBottom hasTwoVideo={findtwoVideo} recording={recording} camPushing={camPushing} screenPushing={screenPushing} localCam={allVideoWindows.localCam} localScreen={allVideoWindows.localScreen} addLog={this.addLog} roomId={roomId}/>
            </Content>
            <Sider width={326}>
                <VideoList addLog={this.addLog} setBigPreview={this.setBigPreview} videos={videos} parentWindow={parent} allVideoWindows={allVideoWindows} />
                <AlertMsg />
            </Sider>
        </Layout>;

        if(roomId){
            return loginedDom;
        }
        return notLoginDom;
    }
}