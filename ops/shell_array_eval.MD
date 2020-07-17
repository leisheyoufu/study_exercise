## eval
vip3="vip3333"
m=3
val=`eval echo '$'vip$m`
echo $val
```
vip3333
```

result1="r1"
result2="r2"
result3="r3"
 
for i in {1..3}
do
    result=`eval echo '$'"result$i"`
    echo $result
done

## Declare array
my_array=(foo bar)
my_array[0]=foo

echo ${my_array[@]} # print values of an array
echo ${my_array[*]} # print values of an array

for i in "${my_array[@]}"; do echo "$i"; done
```
foo
bar
```

for i in "${my_array[*]}"; do echo "$i"; done
```
foo bar
```

## Array size
my_array=(foo bar baz)
echo "the array contains ${#my_array[@]} elements"
```
the array contains 3 elements
```

## Add value
my_array=(foo bar)
my_array+=(baz)
echo "${my_array[@]}"
```
foo bar baz
```

## Delete element in array
my_array=(foo bar baz)
unset my_array[1]
echo ${my_array[@]}
```
foo baz
```

declare -A my_array
my_array+=([foo]=bar [baz]=foobar)
unset my_array[foo]
echo ${my_array[@]}
```
foobar
```

## Delete array
unset my_array