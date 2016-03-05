use Storable qw/freeze thaw store_fd fd_retrieve/;
use Data::Dumper;

my %h;
$h{'hello'} = "hello world";
$h{'world'} = "USA";
my $file = "/tmp/storable.test";
my ($file, $fd);
my $rt = open(FILE1, "+>/tmp/storable.test");
print "cltest rt=$rt\n";
store_fd(\%h,\*FILE1);
close(FILE1);
$rt = open(FILE2,"+</tmp/storable.test");

my $retdata = fd_retrieve(\*FILE2);
print "cltest retdata=".Dumper($retdata)."\n";

my $serialized = freeze(\%h);
print "cltest freeze data".Dumper($serialized)."\n\n";
my %raw_data = %{ thaw($serialized)};
print "cltest rawdata = ".Dumper(%raw_data)."\n\n";
