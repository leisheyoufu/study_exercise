use Data::Dumper;
sub pid_exists {
	my $pid = shift;
	return 1 if $pid == 0;
	
	my $ret = kill(0, $pid);
	print "cltest ".Dumper($ret);
}

print $ARGV[0];
pid_exists $ARGV[0];


