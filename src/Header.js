import React from 'react';
const electron = require('electron');
const {ipcRenderer, shell} = electron;
import {getRoomByAttendeeCode, messageHanddle} from './Util';

import { Input,Button,Switch,Modal,Select,Progress,Popover,message } from 'antd';
import {
    createWindow,
    getTime,
    movePreviewWidow,
    getSdk,
    joinRoom, getLocalUserInfo
} from "./Util";
const {Option} = Select;

export default class PageHeader extends React.Component{
    constructor(props){
        super(props);
        //麦克风ID
        this.testmicrophoneId;
        //摄像头ID
        this.testCameraId;
        //摄像头预览窗口
        this.previewWidow;
        //摄像头预览窗口的占位div
        this.previewDiv;
        //添加日志的方法
        this.addLog = this.props.addLog;
        //倒计时的计时器
        this.countLastTimmer = null;
        this.state={
            visible: false,
            percent:0,
            cameras:[],
            microphones:[],
            joinLoadding:false
        }
    }
    componentDidMount() {
        var _this = this;
        //更新麦克风的音量
        getSdk(true).then(resp=>{
            const urtcSdk = resp.urtcSdk;
            urtcSdk.initdevengine(function (objectStr) {
                _this.setState({percent:objectStr*100/255})
            });

            //麦克风列表
            let micList = [];
            //获取麦克风的数量
            const micCount = urtcSdk.getmicnums();
            //循环获取所有麦克风的信息
            for(let i=0;i<micCount;i++){
                var obj = {
                    deviceid:'',
                    devicename:''
                };
                urtcSdk.getmicdevinfo(i,obj);
                micList.push(obj);
            }

            //摄像头列表
            let camList = [];
            //获取摄像头的数量
            const camCount = urtcSdk.getcamnums();
            for(let i=0;i<camCount;i++){
                let obj = {
                    deviceid:'',
                    devicename:''
                };
                urtcSdk.getcamdevinfo(i,obj);
                camList.push(obj);
            }
            this.setState({microphones:micList,cameras:camList});
        }).catch(ex=>{
            this.addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        })

        ipcRenderer.on('window-moved',(a,b)=>{
            if(this.previewWidow){
                this.previewWidow.pDom = this.previewDiv;
                movePreviewWidow(this.previewWidow,this.props.parentWindow,0,0);
            }
        })
        //兼听加入房间失败的事件
        messageHanddle.on('joinroom-fail',(data)=>{
            message.error(data.content);
            this.setState({joinLoadding:false});
        });
    }

    componentWillUnmount(){
        this.previewWidow && this.previewWidow.close();
        getSdk(true).then(resp=>{
            const urtcSdk = resp.urtcSdk;
            urtcSdk.stopcamtest();
            urtcSdk.stopmictest();
        })
    }

    /**
     * 加入房间
     */
    joinRoom = ()=>{
        const roomid = this.refs.roomid_input.input.value;
        const userid = this.refs.userid_input.input.value;
        if(!roomid){
            message.error('请输入房间id！');
            this.addLog('error','请输入房间id！');
            return;
        };
        if(!userid){
            message.error('请输入用户id！');
            this.addLog('error','请输入用户id！');
            return;
        }
        this.setState({joinLoadding:true});
        sessionStorage.setItem('room_id',roomid);
        getSdk().then(resp => {
            const urtcSdk = resp.urtcSdk;
            urtcSdk.initrtcengine(this.props.initEngine);
            urtcSdk.setsdkmode(1) ; // 0 normal 1 test , normal mode appid and token will be added by developer , test sdk generate
            urtcSdk.setstreamrole(2) ;
            urtcSdk.setaudioonlymode(false) ;
            urtcSdk.setaudopubsub(false, false) ;
            urtcSdk.setvideoprofile(1) ;
            urtcSdk.setscreenprofile(2) ;
            urtcSdk.settokenseckey("9129304dbf8c5c4bf68d70824462409f") ;
            const jsonarg = {} ;
            jsonarg.uid = userid ;
            jsonarg.rid = roomid ;
            jsonarg.appid = "URtc-h4r1txxy" ;// test mode this  define in sdk 
            const jsonStr = JSON.stringify(jsonarg) ;
            console.log("joinroom : "+ jsonStr) ;
            urtcSdk.joinroom(jsonStr);
        }).catch(ex => {
            this.setState({joinLoadding:false});
            message.error(`出现错误：${ex.err || ex.code} --> ${ex.msg || ex.message}`);
            this.addLog('error',`出现错误：${ex.err || ex.code} --> ${ex.msg || ex.message}`);
        })
    }

    /**
     * 设备测试
     */
    testTevice = ()=>{
        const parent = this.props.parentWindow;
        this.setState({visible:true});
        //这里定时防止第一次拿不到previewDiv
        setTimeout(()=>{
            this.previewDiv = this.refs.review_div;
            this.previewWidow = createWindow({width:360,height:240,parent:parent});
            this.previewWidow.pDom = this.previewDiv;
            movePreviewWidow(this.previewWidow,parent,0,0);
            setTimeout(()=>{
                this.previewWidow.show();
            },200);
            this.previewWidow.on('closed', () => {
                this.previewWidow = null;
            });
        },300);
    }
    /**
     * 关闭测试弹层
     */
    handleCancel = ()=>{
        this.setState({visible:false});
        if(this.previewWidow){
            this.previewWidow.close();
        }
        getSdk(true).then(resp=>{
            resp.urtcSdk.stopcamtest();
            resp.urtcSdk.stopmictest();
            this.setState({percent:0});
        }).catch(ex=>{
            this.addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        });

    }
    //记录当前选中的麦克风
    changeTestmicrophone = (value)=>{
        this.testmicrophoneId = value;
    }
    //记录当前选中的摄像头
    changeTestCamera = (value) =>{
        this.testCameraId = value;
    }
    //测试摄像头
    testCamera = () =>{
        if(!this.testCameraId){
            this.addLog('error','请先选择摄像头！');
            return;
        }
        this.addLog('info','您点击了测试摄像头按钮！');
        getSdk(true).then(resp=>{
            //先停止上一个摄像头的测试
            resp.urtcSdk.stopcamtest();
            resp.urtcSdk.startcamtest(this.testCameraId,this.previewWidow.getNativeWindowHandle().readInt32LE());
        }).catch(ex=>{
            this.addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        });
    }
    //测试麦克风
    testmicrophone = ()=>{
        if(!this.testmicrophoneId){
            this.addLog('error','请先选择麦克风！');
            return;
        }
        this.addLog('info','您点击了测试麦克风按钮！');
        getSdk(true).then(resp=>{
            //先停止上一个麦克风的测试
            resp.urtcSdk.stopmictest();
            //测试当前麦克风
            resp.urtcSdk.startmictest(this.testmicrophoneId);
        }).catch(ex=>{
            this.addLog('error',`出现错误：${ex.err || ex.code || ex.status} --> ${ex.msg || ex.message}`);
        });
    }

    render(){
        const notJoinRoom = <div className="page-header">
            <div className="header-item">
                房间ID: <Input ref="roomid_input" style={{width:100}}/>
                用户ID: <Input ref="userid_input" style={{width:100}}/>
            </div>
            <div className="header-item">
                <Button loading={this.state.joinLoadding} onClick={this.joinRoom} type="primary">加入会议</Button>
            </div>
            <div style={{marginLeft:'20px'}} className="header-item">
                <Button type="primary" onClick={this.testTevice}>设备测试</Button>
            </div>
            <Modal
                title="设备测试"
                okText="确定"
                centered={true}
                maskClosable={false}
                visible={this.state.visible}
                onCancel={this.handleCancel}
                footer={<Button type="primary" onClick={this.handleCancel}>确定</Button>}>
                <div ref="review_div" style={{width:360,height:240,marginBottom:'10px'}}></div>
                <div style={{marginBottom:'10px'}}>
                    摄像头列表：
                    <Select onChange={this.changeTestCamera} style={{ width: 275,marginRight:'10px'}}>
                        {this.state.cameras.map(camera=><Option key={camera.deviceid} value={camera.deviceid}>{camera.devicename}</Option>)}
                    </Select>
                    <Button type="primary" onClick={this.testCamera}>摄像头测试</Button>
                </div>
                <div>
                    麦克风列表：
                    <Select onChange={this.changeTestmicrophone} style={{ width: 275,marginRight:'10px'}}>
                        {this.state.microphones.map(microphone=><Option key={microphone.deviceid} value={microphone.deviceid}>{microphone.devicename}</Option>)}
                    </Select>
                    <Button type="primary" onClick={this.testmicrophone}>麦克风测试</Button>
                </div>
                <div>
                    <Progress strokeWidth={15}  style={{marginTop:10}} showInfo={false} percent={this.state.percent} />
                </div>
            </Modal>
        </div>;
        return notJoinRoom;
    }
}
