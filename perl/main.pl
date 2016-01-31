$c='main';

{
        local $c='sub';
        print "$c\n";
        print "$main::c\n";
}

print "$c\n";
