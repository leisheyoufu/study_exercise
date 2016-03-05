my $rc = fork;
if ($rc == 0) {
    print "this is child $$\n";
    $SIG{INT} = sub {
        print "int received\n";
    };
    $SIG{SYS} = sub {
        print "sigsys signal received\n";
    };
    sleep(100);
    print "sleep end\n";
} else {
    print "this is father $$ rc=$rc\n";
    sleep(5);
    #kill 'INT', $rc
    kill 'SYS', $rc;
}
