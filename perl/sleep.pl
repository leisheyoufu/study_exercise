my $a = "a";
  print "a=$a\n";
print "sleep 5\n";
sleep(5);
print "ord(a)".ord($a)."\n";
print "sleep a=ord($a)\n" if $a!=0;
sleep(ord($a)); #if $a != 0;
print "sleep 10\n";
sleep(10);
