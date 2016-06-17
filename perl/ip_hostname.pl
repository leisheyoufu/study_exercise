use Socket;
use Sys::Hostname;
my $hostname = 'www.yahoo123213.com.cn';
my $addr = (gethostbyname($hostname))[4];
my ($a,$b,$c,$d) = unpack('C4',$addr);
print "$a.$b.$c.$d\n";
my $input  ="10.4.40.23";
if($input =~ /^\d+.\d+.\d+.\d+$/)
{
    my $name = gethostbyaddr(inet_aton($input),AF_INET);
    print "$name\n";
}