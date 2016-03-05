my $pipe,$rt;
$fpath = '/tmp/namedpipe';
my $count =0;
my $ret = -1;
while ($count <2) {
	open($pipe, '<', $fpath);
	while($ret = read($pipe, $tmp, 4)!=0) {
		print $count. " $tmp ret=$ret\n";
		$count++;
	}
	close($pipe);
#	while($rt = read($pipe, $tmp, 8)) {
#		print $tmp;
#		$count++;
#	}
}
