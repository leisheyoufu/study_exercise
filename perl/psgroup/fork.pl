#/bin/perl
use POSIX qw(WNOHANG setsid :errno_h);
#setsid;
#setpgrp(0,0) || die "$!";
#`/tmp/sleep.pl`;
#setpgrp(0,0);
my $rc = fork;
if ($rc == 0) {
    #POSIX::setsid();
#    setpgrp(0,0);
    setpgrp;
    print "parenet pid=$$ group pid=".getpgrp()."\n";
    my $pid = fork();
    if ($pid==0) {
        print "child pid=$$ group pid=".getpgrp()."\n";
        sleep 120;
    }
    else {
        sleep 120;
    }
} else {
   sleep 120;
   # system('/bin/sleep 120');
   #`/bin/sleep 120`;
}
