use Fcntl;             # for sysopen
$fpath = '/tmp/namedpipe';

unless (-p $fpath) {   # not a pipe
    if (-e _) {        # but a something else
        die "$0: won't overwrite .signature\n";
    } else {
        require POSIX;
        POSIX::mkfifo($fpath, 0666) or die "can't mknod $fpath: $!";
        warn "$0: created $fpath as a named pipe\n";
    }
}

my $pipe;
open($pipe, '>', $fpath);
print "lock\n";
flock($pipe,LOCK_EX);
print "write\n";
print {$pipe} "456\n";# "pid $$ hello namedpipe\n";
close($pipe);
