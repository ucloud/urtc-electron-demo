1 安装nodejs 安装8.x 版本， 10版本会有问题  本demo 安装 8.9.4
2 安装node-gyp 安装node-gyp@3.5.0 之后的版本可能不支持vs2015 ，只能支持vs2017编译，demo采用node-gyp@3.5.0
npm install -g node-gyp@3.5.0
3 安装python 2.x 版本，不支持3.x 版本，并设置到环境变量中去
4 git clone 
5 进入工程根目录  
npm i electron --arch=ia32 --save-dev   安装electron 版本
6 npm install 安装js 依赖
7 node-gyp rebuild --target=2.0.8 --arch=ia32 --dist-url=https://atom.io/download/electron 编译插件
编译好的库位于 更目录 build/release 目录下
8 将库拷贝到 pulgin/lib/release 目录下
9 调试打包

#### 开发环境  用于调试 代码不混淆
打开根目录 index.js 文件

注释掉 mainWindow.loadFile('dist/index.html')  
取消 mainWindow.loadURL('http://localhost:3000/index.html') 的注释

然后在根目录运行 npm run react-start  (运行该命令的窗口不要关闭)
然后在根目录运行 npm start 

### 项目打包   代码会混淆
打开根目录 index.js 文件
取消 mainWindow.loadFile('dist/index.html') 的注释
注释掉 mainWindow.loadURL('http://localhost:3000/index.html')

然后在根目录运行 npm run react-build    
然后在根目录运行 npm run build-win


1 node-gyp.js 找不到 解决方案
	set npm_config_node_gyp=C:\Users\usser\AppData\Roaming\npm\node_modules\node-gyp\bin\node-gyp.js
	npm config set python python
	npm config set msvs_version 2015

  