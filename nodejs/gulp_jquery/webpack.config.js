var HtmlWebpackPlugin = require('html-webpack-plugin'); //万事先引用
var webpack = require("webpack");

module.exports = {
    entry: [ //entry 是入口文件，可以多个，代表要编译那些js
        './src/main.js',
        './src/login.js',
        './src/reg.js',
    ],
    output: {
        path: __dirname + '/build/js', //输出文件夹
        filename: 'build.js' //最终打包生成的文件名
    },
    plugins: [
        new HtmlWebpackPlugin({
            filename: __dirname + '/build/html/login.html',
            template: __dirname + '/src/tpl/login.html',
            inject: "body"

        }), //初始化这个对象
        new webpack.ProvidePlugin({
            $: 'jquery' //这里请确保你的jquery已经安装了。否则要路径引用哦
        })
    ]

}