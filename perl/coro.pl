use strict;
use Coro;
use AE qw( );
use AnyEvent::Util;
use Coro::EV;

sub ae_sleep {
	my ($secs) = @_;
	my $cv = AE::cv();
	my $guard = AE::timer( $secs, 0, $cv );
	$cv->recv();
}

sub func {
	my $para  = shift;
	my $count = 1;

	#	while ($count > 0 ) {
	#		if ($count % 1000000 == 0)
	#		{
	#			print "$count: in coro $para\n";
	#		}
	#		$count ++;
	#		ae_sleep(1);
	#	}
	while (1) {
		print "$count: in coro $para\n";
		ae_sleep(1);
		$count++;
	}

}

sub green_exec {
	my ( $cmd, $out_ptr, $err_ptr ) = @_;
	my $event = AnyEvent->condvar();
	my $result;
	my $exitcode = 0;
	$event->begin( sub { shift->send($result) } );
	$event->begin;
	my $task =
	  AnyEvent::Util::run_cmd( $cmd, "<", "/dev/null", ">", $out_ptr, "2>",
		$err_ptr );
	$task->cb(
		sub {
			$exitcode = shift->recv;
			$event->end;
		}
	);
	$event->end;
	$event->recv;
	return $exitcode;
}

sub run {
	my $cmd = shift;
	my $out;
	my $quit_program = AnyEvent->condvar();
	my $result;
	$quit_program->begin( sub { shift->send($result) } );
	my $i = 0;

	$quit_program->begin;

	my $cv;
	$cv = run_cmd $cmd, "<", "/dev/null",

	  ">", \$out, "2>", "/dev/null";

	$cv->cb(
		sub {
			shift->recv and die "command failed";

			#print $out;
			$quit_program->end;
		}
	);

	$quit_program->end;    # end loop
	$quit_program->recv;
	return $out;
}

sub main {

	my $coro1 = async {

		#func "1";
		while (1) {
			my $out;
			my $err;
			my $rc = green_exec( "sleep 1;echo hello world 1", \$out, \$err );
			print $out;
		}
	};
	my $coro2 = async {

		my $out;
		my $err;
		my $rc = green_exec( "exit 1", \$out, \$err );
		print $rc

	};
	print "main thread\n";
	$coro1->join();
}

main();

#my $cv = undef;
#my $status = '';
#my $pid = '';
#
#any '/' => sub {
#  my $self = shift;
#
#  unless ( $cv ) {
#    $cv = run_cmd [ qw(sleep 10) ] =>
#      '<'  => \*STDIN,
#      '>'  => \*STDOUT,
#      '2>' => \*STDERR,
#      '$$' => \$pid;
#    $cv->cb( sub {
#      say "DONE!";
#      $status = 'finished';
#      undef $cv;
#    });
#    $status = 'started';
#  }
#
#  $self->stash( pid => $pid, cmd_status => $status );
#  $self->render( 'index' );
#};

