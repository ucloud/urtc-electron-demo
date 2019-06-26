//视频列表
import React, {Component} from 'react'
import { Card,Icon } from 'antd';
import {createWindow, getSdk, movePreviewWidow} from "./Util";
const electron = require('electron');
const ipcRenderer = electron.ipcRenderer;
import PageBottom from './PageBottom';
import videoConference from './icon/video_conference.svg';

export default class PageContent extends Component {
    constructor(props) {
        super(props);
    }
    componentDidMount(){
        //窗口移动
        ipcRenderer.on('window-moved',()=>{
            const { videoWindow, parentWindow } = this.props;
            if(videoWindow){
                movePreviewWidow(videoWindow,parentWindow,1);
            }
        });

        //最小化窗口
        ipcRenderer.on('window-minimized',(a,b)=>{
            const { videoWindow } = this.props;
            if(videoWindow){
                videoWindow.hide();
            }
        })
        // //窗口还原
        ipcRenderer.on('window-restored',(a,b)=>{
            const { videoWindow } = this.props;
            if(videoWindow){
                setTimeout(()=>{
                    videoWindow.show();
                },500);
            }
        })
    }
    componentDidUpdate(){
        const { videoWindow, parentWindow } = this.props;
        if(videoWindow){
            videoWindow.pDom = this.refs['big_video_bg'];
            movePreviewWidow(videoWindow,parentWindow,1,1);
            videoWindow.setSize(960,540);
        }
    }
    render() {
        const {video, addLog, roomId} = this.props;
        return (
            <div className="page-content-warpper">
                <div className="empty-data-warpper">
                    <div className="video-window-warper">
                        <Card title={video.userName} style={{ width: '100%' }}>
                            <img ref="big_video_bg" className="video-window-img" src={videoConference} />
                        </Card>
                    </div>
                </div>
            </div>
        )
    }
}