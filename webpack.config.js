const path = require('path');
const webpack = require('webpack');
const getThemeConfig = require('./theme.js');
theme = getThemeConfig();

module.exports = {
    context: path.join(__dirname,"src/"),
    entry: './app.js',
    output: {
        path: path.join(__dirname, '/dist'),
        filename: 'app.js'
    },
    module:{
        rules:[
            {
                test:/\.js?$/,
                include:[
                    path.resolve(__dirname,'src')
                ],
                use:['babel-loader']
            },
            //less-loader 如果是2以上的版本  一定要配 javascriptEnabled:true
            {test:/\.less$/,use:['style-loader','css-loader',{ loader:'less-loader',options: {'modifyVars':theme,javascriptEnabled:true}}]},
            {test:/\.node$/,use:[{loader:'native-ext-loader',options: {rewritePath: "resources/app/plugin/lib/release/"}}]},
            {
                test: /\.(jpe?g|png|gif|svg)$/,
                loader: 'file-loader',
                options: {
                    name: 'images/[path][name].[ext]'
                }
            }
        ]
    },
    //处理在react中引入electron报 can't resolve fs 的错
    target:'electron-renderer'
};