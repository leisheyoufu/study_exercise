use strict; 
use AnyEvent;
use AnyEvent::Util;

my $s1    = time;

my $quit_program = AnyEvent->condvar(
    cb => sub {
        warn "Done async";
    }
);

my $result;
$quit_program->begin( sub { shift->send($result) } );
my $i = 0;
while( $i < 5 ){
    $quit_program->begin;
    my $cmd = "echo $i";
    my $cv; $cv = run_cmd $cmd,
                "<" , "/dev/null",
                #">" , "/dev/null",
                "2>", "/dev/null";

    $cv->cb (sub {
        shift->recv and die "command failed";

        # undef $cv;
        $quit_program->end;
    });
    $i++;
}

$quit_program->end;   # end loop
my $foo = $quit_program->recv;
#say "Total elapsed time: ", time - $s1, " ms";