import React, {Component} from 'react'
import { Icon } from 'antd';

export default class UserList extends Component {
    constructor(props) {
        super(props)
    }

    render() {
        const users = this.props.users;
        return (
            <div className="user-list-warpper">
                <div className="sider-title">用户列表</div>
                {users.length>0?<ul className="user-list-content">
                    {users.map((user,index)=>{
                        return <li key={index} className="user-item"><Icon type="user" />{user.uid}</li>
                    })}
                </ul>:<div className="empty-data-warpper">您未加入房间或当前房间无用户</div>}
            </div>
        )
    }
}