use Class::Struct;
use strict;
struct Command =>{
    stage => '$', #running, callback
    node => '$', 
    command => '$',
    client => '$',
    action => '$'
};

my $cmd = Command->new(
                        stage =>'running',
                        node => 'fs3',
                        command => '11',
                        client => 'c910',
                        action => 'complete'
                    );
print $cmd;
