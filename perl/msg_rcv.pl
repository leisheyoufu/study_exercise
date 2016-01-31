#!/usr/bin/perl
use strict;
use warnings;
use IPC::SysV qw(IPC_PRIVATE S_IRWXU S_IRWXG S_IRWXO IPC_CREAT IPC_NOWAIT);
use IPC::Msg;


my($key, $msg, $msgid, $msgtype, $buf);
$key = IPC::SysV::ftok(".",'1');
print "key=$key\n";
$msg = new IPC::Msg($key, 0666 | IPC_CREAT) or die "create message queue: $!";
$msgtype = 1;
$msgid = $msg->id();
print "MSG_ID: ",$msgid,"\n";

my $running = 1;
while ($running)
{
  $msg->rcv($buf, 1024) or die "receive message failed: $!";
  print "BUFFER: ",$buf,"\n";


  if($buf eq "end")
  {
    $running = 0;
  }
}
$msg->remove();
