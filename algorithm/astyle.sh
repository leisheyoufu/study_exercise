basepath=$(cd `dirname $0`; pwd)
dir=$basepath/leetcode
filelist=`find $dir -type f -name "*.c" -or -name "*.h" -or -name "*.cpp"`
for file in $filelist
do
    $basepath/astyle --style=linux --indent=spaces=4 $file
    if [ -f "$file.orig" ]; then
        rm "$file.orig"
    fi
done
