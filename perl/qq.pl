use Data::Dumper;
my @msg = [0, "hello world"];
#push @msg, [1, "hello world1"];
foreach my $tmp (@msg) {
    print "cltest ".Dumper($tmp);
}
