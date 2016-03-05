my $str ='Unable to send RAW command (channel=0x0 netfn=0x2c lun=0x0 cmd=0x31 rsp=0x80): Unknown (0x80)';

#my $string = "I love perl";

#$string =~ s/(love)/<$1>/;
#$str = ~ s/(rsp=)/<$1>/;
#print $1;
sub  trim { my $s = shift; $s =~ s/^\s+|\s+$//g; return $s };
my @r = $str=~/.*?rsp=(.*)\)\:.*/;
print $r[0];
print "\n";
$str = ' aa 00 31 80';
$str =~ s/^\s+|\s+$//g;
#print "$str\n";
#$str = trim($str);
print $str;
print "cltest \n";
my $a = 2;
#my $a = 1 if $str;
$a = $str if $str;
print $a;
