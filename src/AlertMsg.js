import React, {Component} from 'react'
import {Alert,Icon} from "antd";
import {render} from "react-dom";
import {messageHanddle} from './Util';
import './style/message.less';

export default class AlertMsg extends Component{
    constructor(props){
        super(props);
        this.state = {
            type:'success',
            message:'欢迎使用URTC服务',
            haseMessage:true
        };
    }
    componentDidMount() {
        messageHanddle.on('app-message', data => {
            this.setState({type:data.type,message:data.content});
        })
    }
    closeMessage = (e) => {
        e.preventDefault();
        this.setState({message:''});
    }
    render() {
        const { message, type } = this.state;
        const className = `ant-alert ant-alert-${type} ant-alert-no-icon ant-alert-closable`
        return <div className="alert-msg-warpper" style={{padding:'2px'}}>
            {message?
                <div data-show="true" className={className}>
                    <div className="ant-alert-message" dangerouslySetInnerHTML={{ __html: this.state.message}} />
                    <a className="ant-alert-close-icon" onClick={this.closeMessage}>
                        <Icon type="close" />
                    </a>
                </div>:null}
        </div>
    }
}