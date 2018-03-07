//先到webpack.config.js中确认我们的入口文件
module.exports = {
    entry: [ //entry是入口文件，可以多个，代表要编译哪些JS
        './src/main.js'
    ],
    output: {
        path: __dirname + '/build/js', //输出文件夹
        filename: 'build.js' //最终打包生成的文件名
    }

}