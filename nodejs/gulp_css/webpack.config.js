var HtmlWebpackPlugin = require('html-webpack-plugin'); //万事先引用
var webpack = require("webpack");
var ExtractTextPlugin = require("extract-text-webpack-plugin");

module.exports = {
    entry: { //多节点设置
        "main": './src/main.js',
        "user": ['./src/login.js', './src/reg.js']
    },
    output: {
        path: __dirname + '/build/js', //输出文件夹
        filename: '[name].js' //最终打包生成的文件名
    },
    plugins: [
        new HtmlWebpackPlugin({
            filename: __dirname + '/build/html/login.html',
            template: __dirname + '/src/tpl/login.html',
            inject: "body"

        }), //初始化这个对象
        new webpack.optimize.SplitChunksPlugin({
            name: "user", //entry定义的节点名
            filename: "user.js", //最终要生成到文件名
            minChunks: Infinity
        }),
        new webpack.ProvidePlugin({
            $: 'jquery' //这里请确保你的jquery已经安装了。否则要路径引用哦
        }),
        new ExtractTextPlugin("main.css")
    ],
    externals: {
        'jquery': 'jQuery' //或者 ‘jquery’:’$’
    },
    module: {
        rules: [{
            test: /\.css$/,
            use: ExtractTextPlugin.extract({
                fallback: "style-loader",
                use: "css-loader"
            })
        }]
    }
}