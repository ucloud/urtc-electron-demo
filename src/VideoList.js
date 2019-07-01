import React, {Component} from 'react'
import { Card,Icon } from 'antd';
const { Meta } = Card;
const electron = require('electron');
const ipcRenderer = electron.ipcRenderer;
import './videoList.less';
import videoConference from './icon/video_conference.svg';
import {getSdk, movePreviewWidow} from "./Util";

export default class VideoList extends Component{
    constructor(props){
        super(props);
        this.videoList = [];
    }
    componentDidMount(){
        //窗口移动
        ipcRenderer.on('window-moved',()=>{
            const { allVideoWindows, parentWindow } = this.props;
            this.videoList.map(video => {
                const streamId = video.streamid;
                if(streamId){
                    const win = allVideoWindows[streamId];
                    if(win){
                        movePreviewWidow(win,parentWindow,1);
                    }
                }
            });
        });

        //最小化窗口
        ipcRenderer.on('window-minimized',(a,b)=>{
            const { allVideoWindows } = this.props;
            this.videoList.map(video => {
                const streamId = video.streamid;
                if(streamId){
                    const win = allVideoWindows[streamId];
                    if(win){
                        win.hide();
                    }
                }
            });
        })
        //窗口还原
        ipcRenderer.on('window-restored',(a,b)=>{
            const { allVideoWindows } = this.props;
            setTimeout(()=>{
                this.videoList.map(video => {
                    const streamId = video.streamid;
                    if(streamId){
                        const win = allVideoWindows[streamId];
                        if(win){
                            win.show();
                        }
                    }
                });
            },500);
        })
    }
    componentDidUpdate(){
        const {parentWindow,allVideoWindows} = this.props;
        this.videoList.map(video => {
            //小窗口
            const streamId = video.streamid;
            const win = allVideoWindows[streamId];
            if(win){
                win.pDom = this.refs[streamId];
                movePreviewWidow(win,parentWindow,1);
            }
        })
    }

    /**
     * 开启/关闭画面
     */
    muteVideo = (streamId,muted=false)=>{
        const { addLog } = this.props;
        let type = muted?'打开':'关闭';
        getSdk().then(resp=>{
            const urtcSdk = resp.urtcSdk;
            if('localScreen' === streamId){
                urtcSdk.MuteLocalVideo(muted, 2);
                addLog('info','您点击了'+type+'本地桌面画面！');
            }else if('localCam' === streamId){
                urtcSdk.MuteLocalVideo(muted, 1);
                addLog('info','您点击了'+type+'本地媒体画面！');
            }else{
                const jsonarg = {} ;
                jsonarg.uid = streamId.substr(0, streamId.length-1) ;
                const mtype = streamId.substr(streamId.length-1,1) ;
                jsonarg.mtype =  parseInt(mtype) ;
                jsonarg.mute =  muted ;
                const jsonStr = JSON.stringify(jsonarg) ;
                urtcSdk.MuteRemoteVideo(jsonStr);
                addLog('info','您点击了'+type+' '+streamId+'画面！');
            }
        }).catch(ex=>{
            addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        })
    }
    /**
     * 开启/关闭声音
     * @param streamId
     * @param muted
     */
    muteAudio = (streamId,muted=false)=>{
        const { addLog } = this.props;
        let type = muted?'打开':'关闭';
        getSdk().then(resp=>{
            const urtcSdk = resp.urtcSdk;
            if('localCam' === streamId){
                urtcSdk.MuteLocalAudio(muted);
                addLog('info','您点击了'+type+'本地媒体声音！');
            }else{
                const jsonarg = {} ;
                jsonarg.uid = streamId.substr(0, streamId.length-1) ;
                const mtype = streamId.substr(streamId.length-1,1) ;
                jsonarg.mtype =  parseInt(mtype) ;
                jsonarg.mute =  muted ;
                const jsonStr = JSON.stringify(jsonarg) ;
                urtcSdk.MuteRemoteAudio(jsonStr);
                addLog('info','您点击了'+type+' '+streamId+'声音！');
            }
        }).catch(ex=>{
            addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        })

    }

    render(){
        const { videos,setBigPreview } = this.props;
        this.videoList = videos;
        //删除第一项 因为第一项被放大
        this.videoList = videos.slice(1);
        let indexKey = 0;
        return <div className="video-list clearfix">
            {this.videoList.map(stream=>{
                const { muteaudio, mutevideo, streamid = '', video, audio } = stream;
                const openColor = '#54adff';
                const closeColoe = '#ccc';
                // muteaudio: false
                // mutevideo: false
                indexKey++;
                let actions = [];
                if(video){
                    actions.push(<Icon style={{color: mutevideo?closeColoe:openColor }} type="video-camera" onClick={() => this.muteVideo(streamid, !mutevideo)} />);
                }
                if(audio){
                    actions.push(<Icon style={{color: muteaudio?closeColoe:openColor }} type="sound" onClick={()=>this.muteAudio(streamid, !muteaudio)} />);
                }
                if(streamid){
                    actions.push(<Icon type="fullscreen" onClick={()=>{setBigPreview(streamid)}}/>);
                }else{
                    actions.push(<Icon type="lock" />);
                }
                return <Card key={indexKey} hoverable style={{ width: 163 }} cover={<img ref={streamid} alt="视频" src={videoConference} />} actions={actions}>
                    <Meta title={stream.userName} />
                </Card>
            })}
        </div>
    }
}