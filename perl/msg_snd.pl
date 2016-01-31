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

my $pal;
foreach $pal('Tom','Dick','Harry','Pete','Hank')
{
  $msg->snd($msgtype, "Hi, $pal", IPC_NOWAIT) or die "send message failed: $!";
  print "BUFFER: ",$pal,"\n";
  $msg->snd($msgtype, "Hi, $pal", IPC_NOWAIT) or die "send message failed: $!";
}
  
# end
$msg->snd($msgtype, "end", IPC_NOWAIT) or die "send message failed: $!";
print "BUFFER: end\n";
