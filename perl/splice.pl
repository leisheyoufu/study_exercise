use Data::Dumper;
my @array = ('hello','1','3','world','world2');
#splice (@array, 1,1); #add element
foreach my $i (@array) {
	if ($i =='1') {
		$i = undef;
	}
}
#delete(@array, '1');
print Dumper(@array);
#splice (@array, 0, 1); 
print "delete \n";
my $str='world';
my @code = grep(/./, @array);
my @code = grep(/[^$str]/,@array);
print "delete".Dumper(@code);
