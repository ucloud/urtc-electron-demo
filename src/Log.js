var log4js = require('log4js');

log4js.configure({
    appenders: { webrtc: { type: 'dateFile',maxLogSize: 4096, filename:'./logs/log',alwaysIncludePattern: true,pattern: 'yyyy-MM-dd.log'}},
    replaceConsole: true,
    categories: { default: { appenders: ['webrtc'], level: 'debug' } }
});
var logger = log4js.getLogger('webrtc');
logger.level = 'debug';


export const saveLog = (type,content)=>{
    if('info' === type || 'success' === type){
        logger.info(content);
    }else if('warning' === type){
        logger.warn(content);
    }else if('error' === type){
        logger.error(content);
    }
};