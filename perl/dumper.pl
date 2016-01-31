#!/usr/bin/perl
# Godbach, 2011/05/07
use warnings;
use strict;
use Data::Dumper;

my $var = "Hello, world";
my @arr = qw(hello world bye bye);
my %foo = (
    name => 'zhangsan',
    age => '28',
    sx => 'male',
    company => {
        'intel' => '2',
        'ibm' => '3',
        'microsoft' => '2'
    },
);

# 打印变量
print "==> Dump Variable:\n";
print Dumper($var);

# 打印数组
print "==> Dump Array:\n";
print Dumper(@arr);

# 打印数组引用
print "==> Dump Array ref:\n";
print Dumper(\@arr);

# 打印 hash 
print "==> Dump Hash:\n";
print Dumper(%foo);

# 打印 hash 引用
print "==> Dump Hash ref:\n";
print Dumper(\%foo);

# 打印子 hash 
print "==> Dump Sub Hash\n";
print Dumper($foo{company});


exit 0;