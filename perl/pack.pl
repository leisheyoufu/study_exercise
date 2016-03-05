my $str = pack("A8",104);
print $str ."haha\n";
my $num = unpack("A8",$str);
print $num;

