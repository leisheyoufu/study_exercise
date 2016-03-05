#use threads;
use Thread qw(yield);  
#use Thread;
my $process = 4;
my $child_num = 0;
  
print $threads::VERSION.chr(10);
  
while (1) {
    my $params = $child_num*10;
    my @thr;
    $thr[$child_num] = threads->new(\&start_thread, $params);        
        $child_num ++;
    #$params = $child_num*10;
    $thr[$child_num] = threads->new(\&start_thread, $params);
    foreach my $t (@thr) {
        $t->join();
        print "join $t\n";
    }
    #foreach my $t(threads->list()){ 
    #foreach my $t(threads->list(threads::joinable)){ 
    #    $t->join(); 
    #} 
  
    # all tasks done and no running child, then exit
    # if ($child_num==4){
    #    exit;
    #}
    print "main while exit\n";
    last;
}
  
sub start_thread(){
    # do actually task here 
    my $param = shift;
    print $param.chr(10);
    print "sleep $param\n";
    sleep($param);
    print "thread $param\n";
    sleep(5);
    print "sleep 5 end\n";
}
