const {app, BrowserWindow, globalShortcut,BrowserView,ipcMain} = require('electron')

let mainWindow;
let win;

//关闭硬件加速
app.disableHardwareAcceleration();

// 创建浏览器窗口。
function createWindow() {
    mainWindow = new BrowserWindow({
        width: 1302,
        height: 762,
        frame:false,
        show:false,
        resizable:false
    });

    mainWindow.once('ready-to-show', () => {
        mainWindow.show()
    })
    win = BrowserWindow.getFocusedWindow();
    //注册打开控制台的快捷键
    globalShortcut.register('CommandOrControl+F12', () => {
        mainWindow.webContents.toggleDevTools();
    });
    globalShortcut.register('CommandOrControl+F5', () => {
        if (!mainWindow) return;
        mainWindow.reload();
    });
    globalShortcut.register('CommandOrControl+Q', () => {
        mainWindow.close();
    });
    //隐藏菜单
    mainWindow.setMenu(null);
	//mainWindow.loadURL('https://demo.urtc.com.cn')
    // and load the index.html of the app.
    //mainWindow.loadFile('dist/index.html');
    mainWindow.loadURL('http://localhost:3000/index.html')

    // 窗口关闭后删除相应的元素。
    mainWindow.on('closed', function () {
        const ws = BrowserWindow.getAllWindows();
        if(ws.length > 0 ){
            ws.map(w => {
                w.close();
            });
        }
        mainWindow = null
    })
    mainWindow.on('move',()=>{
        mainWindow.webContents.send('window-moved');
    })
    mainWindow.on('resize',()=>{
        mainWindow.webContents.send('window-moved');
    })
    mainWindow.on('minimize',()=>{
        mainWindow.webContents.send('window-minimized');
    })
    mainWindow.on('restore',()=>{
        mainWindow.webContents.send('window-restored');
    })

    mainWindow.once('ready-to-show', () => {
        mainWindow.show()
    })
}

//为子进程提供主窗口Id 方便子进程查找主窗口
ipcMain.on('get-parent-window', (event) => {
    event.sender.send('send-parent-window', {winId:mainWindow.id})
})

//和渲染进程进行通信
ipcMain.on('window-message', (event, type) => {
    //最小化窗口
    if(type === 'minimize'){
        mainWindow.minimize();
    }else if(type === 'close'){
        //关闭窗口
        mainWindow.close();
    }
})

// Electron 会在初始化后并准备
// 创建浏览器窗口时，调用这个函数。
// 部分 API 在 ready 事件触发后才能使用。
app.on('ready', createWindow)

// 当全部窗口关闭时退出。
app.on('window-all-closed', function () {
    // 在 macOS 上，除非用户用 Cmd + Q 确定地退出，
    // 否则绝大部分应用及其菜单栏会保持激活。
    if (process.platform !== 'darwin') {
        app.quit()
    }
})

app.on('activate', function () {
    // 在macOS上，当单击dock图标并且没有其他窗口打开时，
    // 通常在应用程序中重新创建一个窗口。
    if (mainWindow === null) {
        createWindow()
    }
})