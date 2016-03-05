use Data::Dumper;

my $cond = 1;
#$SIG{CHLD} = sub {
#	my $cpid;
#	while ( ( $cpid = waitpid( -1, WNOHANG ) ) > 0 ) {
#		print "child $cpid exist\n";
#		$cond = 0;
#	}
#};

open( LIST, "ls -l|" );
my @list = <LIST>;
close(LIST);
print "$$ cltest main $?\n";

my $pid = fork;


if ( $pid == 0 ) {
	
	
	open( LIST, "sleep 10|" );
	my @list = <LIST>;
	close(LIST);
	print "while child ".Dumper(@list)."\n";
	print "$$ cltest child1 $?\n";
	sleep(12);
	exit(0);
}

my $pid = fork;
if ( $pid == 0 ) {
    
    
    open( LIST, "sleep 10|" );
    my @list = <LIST>;
    close(LIST);
    print "while child ".Dumper(@list)."\n";
    print "$$ cltest child2 $?\n";
    sleep(12);
    exit(0);
}
else {
	$SIG{CHLD} = sub {
		my $cpid;
		while ( ( $cpid = waitpid( -1, WNOHANG ) ) > 0 ) {
			print "child $cpid exist\n";
			$cond = 0;
		}
	};
	open( LIST, "sleep 1|" );
	my @list = <LIST>;
	close(LIST);
	print "$$ cltest father $?\n";
	while ($cond) {
		print "in father while \n";
		sleep(1);
	}
}


