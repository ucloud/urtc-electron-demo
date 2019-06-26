export default class EventEmitter {
  constructor() {
    this.events = {};
  }

  /**
   * 监听事件
   * @param eventName 事件名称
   * @param callBack 事件回调
   */
  on(eventName, callBack) {
    this.events[eventName] = this.events[eventName] || [];
    this.events[eventName].push(callBack);
  }

  /**
   * 触发事件
   * @param eventName 事件名称
   * @param data 参数
   */
  emit(eventName, data) {
    const events = this.events[eventName];
    if (!events) {
      return;
    }
    events.map(event => event(data));
  }
}
