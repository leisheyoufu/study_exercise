const ExtractTextPlugin = require("extract-text-webpack-plugin");

module.exports = {
    output: {
        path: __dirname + '/dist/js', //输出文件夹
        filename: 'index.js' //最终打包生成的文件名
    },
    module: {
        rules: [{
            test: /\.scss$/,
            use: ExtractTextPlugin.extract({
                use: [{
                    loader: "css-loader"
                }, {
                    loader: "sass-loader"
                }],
                fallback: "style-loader"
            })
        }]
    },
    plugins: [
        new ExtractTextPlugin({
            filename: 'index.css',
        })
    ],
}