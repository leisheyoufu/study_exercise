use IPC::SysV qw(IPC_PRIVATE S_IRUSR S_IWUSR);
use IPC::Msg;
my $msg = IPC::Msg->new(IPC_PRIVATE, S_IRUSR | S_IWUSR);
my $buf;
$msg->snd(1, 'hello world');
$msg->rcv($buf, 256);
print $buf;
$ds = $msg->stat;
$msg->remove;


