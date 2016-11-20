#!/usr/bin/env perl
use strict;
use Fcntl;
use Fcntl qw( :flock );

print "Current process $$\n";
my $lockfile = '/var/run/ipmiconsole.pid';

unless (sysopen(LOCKHANDLE, $lockfile, O_WRONLY | O_CREAT)) {
    die "Could not open $lockfile \n";
}

while (!flock(LOCKHANDLE, LOCK_EX | LOCK_NB)) {
    print "Process $$: Trying to aquire exclusive lock\n";
    sleep(1);
}
#or die "Could not lock $lockfile \n";
print "Aquire lock succesfully \n";
syswrite(LOCKHANDLE, $$, length($$));
sleep(20);
flock(LOCKHANDLE, LOCK_UN);
print "Release lock succesfully\n";
sleep(20);
close(LOCKHANDLE);
