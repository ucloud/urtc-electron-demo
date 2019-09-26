import React, {Component} from 'react'
import {Button, Switch} from "antd";
import { getSdk, messageHanddle, getLocalUserInfo } from "./Util";

export default class PageBottom extends Component{
    constructor(props){
        super(props);
        this.mediaConfig = {
            videoenable:true,
            audioenable:true
        }
        this.state = {
            //发布摄像头的按钮被点击
            pCameraLoadding:false,
            //发布桌面按钮被点击
            pScreenLoadding:false,
            //网速测试按钮被点击
            netTestLoadding:false
        }
    }

    //视频的开关值发生变化
    videoOptChange = (value)=>{
        this.mediaConfig.videoenable = value;
    }
    //声音开关值发生变化
    audioOptChange = value =>{
        this.mediaConfig.audioenable = value;
    }

    /**
     * 发布摄像头的内容
     */
    publishvideocam=()=>{
        this.setState({pCameraLoadding:true});
        //房间ID
        const { roomId, addLog, localCam } = this.props;
        addLog('info','您点击了发布媒体按钮！');
        if(roomId){
            getSdk().then(resp=>{
                console.log(' 初始化美颜引擎 开始 1') ;
                resp.urtcSdk.InitBeautyEngine(localCam.getNativeWindowHandle().readInt32LE()) ;
                resp.urtcSdk.StartVideoCapture(3) ;
                console.log(' 初始化美颜引擎 开始 3') ;
                resp.urtcSdk.PublishStream(1,this.mediaConfig.videoenable, this.mediaConfig.audioenable);
            }).catch(ex=>{
                this.setState({pCameraLoadding:false});
                addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
            })
        }else{
            this.setState({pCameraLoadding:false});
            addLog('error','获取当前房间失败，您可能还未加入房间！');
        }
    }

    /**
     * 取消发布摄像头内容
     */
    cancelPublishvideocam=()=>{
        const { roomId, addLog } = this.props;
        addLog('info','您点击了取消媒体发布按钮！');
        getSdk().then(resp=>{
            resp.urtcSdk.StopVideoCapture() ;
            resp.urtcSdk.UnInitBeautyEngine() ;
            resp.urtcSdk.UnPublishStream(1);
        }).catch(ex=>{
            addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        });
    }
    /***
     * 发布桌面
     */
    publishvideoScreen = ()=>{
        this.setState({pScreenLoadding:true});
        const { roomId, addLog,localScreen } = this.props;
        addLog('info','您点击了发布桌面按钮！');
        if(roomId){
            getSdk().then(resp=>{
                const jsonarg = {} ;
                jsonarg.index = 0 ;
                jsonarg.x = 0 ;
                jsonarg.y = 0 ;
                jsonarg.width = 0 ;
                jsonarg.height = 0 ;
                const jsonStr = JSON.stringify(jsonarg) ;
                console.log("publishstream : "+ jsonStr) ;
                resp.urtcSdk.SetScreenCaptureProgram(jsonStr) ;
                resp.urtcSdk.PublishStream(2,true, false);
            }).catch(ex=>{
                this.setState({pScreenLoadding:false});
                addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
            });
        }else{
            this.setState({pScreenLoadding:false});
            addLog('error','获取当前房间失败，您可能还未加入房间！');
        }
    }
    /**
     * 取消桌面发布
     */
    cancelPublishvideoScreen = () =>{
        const { roomId, addLog } = this.props;
        addLog('info','您点击了取消桌面发布按钮！');
        getSdk().then(resp=>{
            resp.urtcSdk.UnPublishStream(2);
        }).catch(ex=>{
            addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        });
    }

    /***
     * 录制会议
     */
    startRecord = ()=>{
        this.setState({startrecording:true});
        const { roomId, addLog } = this.props;
        addLog('info','您点击了开始录制！');
        if(roomId){
            getSdk().then(resp=>{
                const jsonarg = {} ;
                jsonarg.mainuid = getLocalUserInfo().userId ;
                jsonarg.profile = 1 ;
                jsonarg.rtype = 1 ;
                jsonarg.wpos = 1 ;
                jsonarg.mvtype = 1 ;
                jsonarg.bucket = "urtc-test" ;
                jsonarg.region = "cn-bj" ;
                const jsonStr = JSON.stringify(jsonarg) ;
                console.log("startRecord : "+ jsonStr) ;
                resp.urtcSdk.StartRoomRcord(jsonStr);
                this.setState({recording:true});
            }).catch(ex=>{
                this.setState({startrecording:false});
                addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
            });
        }else{
            this.setState({startrecording:false});
            addLog('error','获取当前房间失败，您可能还未加入房间！');
        }
    }
    /**
     * 停止录制
     */
    stopRecord = () =>{
        const { roomId, addLog } = this.props;
        addLog('info','您点击了停止录制！');
        getSdk().then(resp=>{
            resp.urtcSdk.StopRoomRecord();
        }).catch(ex=>{
            addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        });
    }

    /**
     * 离开房间
     */
    leaveRoom = ()=>{
        const { addLog, roomId } = this.props;
        addLog('info','您点击了离开房间按钮！');
        getSdk().then(resp=>{
            resp.urtcSdk.LeaveRoom();
        }).catch(ex=>{
            addLog('error',`出现错误：${ex.err || ex.code} --> ${ex.msg || ex.message}`);
        })
    }

    componentWillReceiveProps(nextProps, nextContext) {
        //处理按钮的状态
        let { pCameraLoadding, pScreenLoadding,startrecording } = this.state;
        const { camPushing, screenPushing,recording } = nextProps;
        //是否需要更新按钮状态
        let needSetState = false;
        if(pCameraLoadding && camPushing){
            needSetState = true;
            pCameraLoadding = false;
        }
        if(pScreenLoadding && screenPushing){
            needSetState = true;
            pScreenLoadding = false;
        }
        console.log("componentWillReceiveProps startrecording "+ startrecording) ;
        console.log("componentWillReceiveProps recording "+ recording) ;
        if(startrecording && recording){
            needSetState = true;
            startrecording = false;
        }
        if(needSetState){
            this.setState({pCameraLoadding,pScreenLoadding,startrecording});
        }
    }

    render(){
        const { roomId, camPushing, screenPushing, recording, hasTwoVideo } = this.props;
        const { pCameraLoadding, unpCameraLoadding, pScreenLoadding, unpScreenLoadding,startrecording,stoprecording } = this.state;
        return <div className="page-header" style={{padding:'20px'}}>
            <div className="header-item">
                <Switch disabled={camPushing} onChange={this.videoOptChange} checkedChildren="视频开" unCheckedChildren="视频关" defaultChecked />
                <Switch disabled={camPushing} onChange={this.audioOptChange} checkedChildren="音频开" unCheckedChildren="音频关" defaultChecked />
            </div>
            <div className="header-item">
                {camPushing?
                    <Button loading={unpCameraLoadding} onClick={this.cancelPublishvideocam} type="primary">取消发布媒体</Button>:
                    <Button disabled={ hasTwoVideo&&screenPushing } loading={pCameraLoadding} onClick={this.publishvideocam} type="primary">发布媒体</Button>
                }
                {screenPushing ?
                    <Button loading={unpScreenLoadding} onClick={this.cancelPublishvideoScreen} type="primary">取消发布桌面</Button>:
                    <Button disabled={ hasTwoVideo&&camPushing } loading={pScreenLoadding} onClick={this.publishvideoScreen} type="primary">发布桌面</Button>
                }
            </div>
            <div className="header-item">
                <Button onClick={this.leaveRoom} type="primary">退出房间</Button>
            </div>
            <div className="header-item">
                {recording?
                    <Button loading={stoprecording} onClick={this.stopRecord} type="primary">停止录制</Button>:
                    <Button disabled={recording} loading={startrecording} onClick={this.startRecord} type="primary">录制会议</Button>
                }
            </div>
        </div>
    }
}