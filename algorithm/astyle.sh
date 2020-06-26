basepath=$(cd `dirname $0`; pwd)
dir=$basepath/leetcode
filelist=`find $dir -type f -name "*.c" -or -name "*.h" -or -name "*.cpp"`
astyle=$basepath/astyle
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     astyle=$basepath/astyle;;
    Darwin*)    astyle=$basepath/astyle_mac;;
esac
for file in $filelist
do
    $astyle --style=linux --indent=spaces=4 $file
    if [ -f "$file.orig" ]; then
        rm "$file.orig"
    fi
done
