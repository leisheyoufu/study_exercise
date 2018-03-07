// 引入 gulp
var gulp = require('gulp');

// 引入组件
var jshint = require('gulp-jshint');
var less = require('gulp-less');
var concat = require('gulp-concat');
var uglify = require('gulp-uglify');
var rename = require('gulp-rename');

// 检查脚本
gulp.task('lint', function() {
    gulp.src('src/js/*.js') //该任务针对的文件
        .pipe(jshint()) //该任务调用的模块
        .pipe(jshint.reporter('default'));
});

// 编译Sass
gulp.task('less', function() {
    gulp.src('src/less/*.less')
        .pipe(less())
        .pipe(gulp.dest('./dist/css'));
});

// 合并，压缩文件
gulp.task('scripts', function() {
    gulp.src('src/js/*.js')
        .pipe(concat('all.js'))
        .pipe(gulp.dest('./dist'))
        .pipe(rename('all.min.js'))
        .pipe(uglify())
        .pipe(gulp.dest('./dist'));
});

// 默认任务
gulp.task('default', function() {
    gulp.run('lint', 'less', 'scripts');

    // 监听js文件变化
    gulp.watch('src/js/*.js', function() {
        gulp.run('lint', 'less', 'scripts');
    });
    // 监听less文件变化
    gulp.watch('src/less/*.less', function() {
        gulp.run('lint', 'less', 'scripts');
    });
});