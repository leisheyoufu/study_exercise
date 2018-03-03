var gulp_webpack = require("gulp-webpack");
var gp = require("gulp");
var gulp_concat = require("gulp-concat");
var gulp_uglify = require("gulp-uglify");
var gulp_webpack = require("gulp-webpack");
var webpack_config = require("./webpack.config.js");
var webpack = require("webpack");

//在gulpfile重新写入两个task任务
//生成JS文件
gp.task("build-js",function(){
   gulp_webpack(webpack_config,webpack)
       .pipe(gp.dest('./build/js'))
})
//最终生成
gp.task("run",['build-js'],function(){
    gp.src(['./src/tpl/*.html'])
        .pipe(gp.dest('./build/html'))
})