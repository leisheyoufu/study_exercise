'use strict'

const util = require('gulp-util')
const devServer = require('webpack-dev-server')
const webpack = require('webpack')
const path = require("path")
var HtmlWebpackPlugin = require('html-webpack-plugin');//万事先引用
module.exports=
{
    devtool: util.env.production ? false : 'source-map',
    devServer: {
        historyApiFallback:true,
        inline:true,
        contentBase: path.join(__dirname, "build"),
        publicPath: "",
        compress: true,
        port: 9000
    },
    entry:[                     //entry是入口文件，可以多个，代表要编译哪些JS
        './src/main.js'
    ],
    output:{
        path: __dirname+'/build/js',      //输出文件夹
        filename: 'build.js',    //最终打包生成的文件名
        publicPath:"",
    },
    plugins:[
        new HtmlWebpackPlugin({
            template: __dirname + '/src/tpl/login.html',
            filename: __dirname + '/build/html/login.html',
            inject:"body",　　//在head中引用就写head
            hash:true　　　　　　
        }), //初始化这个对象
        new webpack.HotModuleReplacementPlugin()
    ]
}
