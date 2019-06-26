import 'whatwg-fetch';
const electron = require('electron');
const {BrowserWindow} = electron.remote;
import urtcSdk from '../plugin/lib/release/urtcelectron.node';
import EventEmitter from "./EventEmitter";

let localUserInfo = {};
/**
 * 抛出错误
 * @param response
 */
const thowError = resp => {
    const error = new Error(resp.msg);
    error.status = resp.err;
    error.response = resp;
    throw error;
};

/**
 * 获取当前时间
 * @return {string}
 */
export const getTime = ()=>{
    const now = new Date();
    const hour = now.getHours();
    const min = now.getMinutes();
    const sec = now.getSeconds();
    return `${hour.toString().padStart(2,'0')}:${min.toString().padStart(2,'0')}:${sec.toString().padStart(2,'0')}`
}

/**
 * 创建electron的window窗口
 * @param width 宽度默认 234
 * @param height 高度 默认 137
 // * @param hasShadow 是否有阴影 默认 false
 * @param show 是否立刻显示 默认 false
 * @param frame 是否有边框 默认 false
 * @param resizable 是否可缩放 默认 false
 * @param movable 是否可拖动 默认false
 * @param skipTaskbar 是否显示在工具栏  默认false
 * @param parent 父窗口 默认null
 * @param thickFrame 边框的阴影 默认false
 * @return {Electron.Remote.BrowserWindow}
 */
export const createWindow = ({focusable=false,width=160,height=90,hasShadow=false,show=false,frame=false,resizable=false,movable=false,skipTaskbar=false,parent=null,thickFrame=false})=>{
    let win = new BrowserWindow({
        width,
        height,
        show,
        frame,
        resizable,
        movable,
        skipTaskbar,
        parent,
        thickFrame,
        focusable,
        webPreferences:{
            webgl:false
        }
    });
    win.on('closed', () => {
        win = null;
    });
    return win;
}

/**
 * 移动窗口
 * @param video
 */
export const movePreviewWidow = (win,parent,offsetX=0,offsetY=0)=>{
    const dom = win.pDom;
    if(win && dom && !win.isDestroyed()){
        const parentBound = parent.getBounds();
        const previewDivPosition = dom.getBoundingClientRect();
        const x = Math.round(parentBound.x + previewDivPosition.x+offsetX);
        const y = Math.round(parentBound.y + previewDivPosition.y+offsetY);
        win.setPosition(x,y,true);
    }
}

/**
 * 
 * @param userId
 * @returns {*}
 */
export const decodeUserInfo = (fullName) => {
    if (!fullName) {
        return null;
    }
    const index1 = fullName.lastIndexOf('_');
    if (index1 < 0) {
        return fullName;
    }
    const userName = fullName.substr(0, index1);
    const userId = fullName.substr(index1+1);
    return {
        userId,
        userName
    };
}

/**
 * 设置本地的用户信息
 * @param fullName
 */
export const setLocalUserInfo = (fullName)=> {
    localUserInfo = decodeUserInfo(fullName);
}
/**
 * 获取本地的用户信息
 */
export const getLocalUserInfo = () => {
    return localUserInfo;
}

/**
 * 获取SDK
 * @param urtcSdkOnly 只获取SDK 不考虑token
 * @param getNew 获取全新的token
 * @return {Promise<any>}
 */
export const getSdk = ()=>{
    return new Promise((resolve,reject)=>{
        resolve({urtcSdk});
    });
}



//消息订阅器
export const messageHanddle = new EventEmitter();