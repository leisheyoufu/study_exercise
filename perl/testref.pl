#!/usr/bin/perl -w
%hash=('Tom'=>'Male','Jerry'=>'Female');
$href=/%hash;
for $key (keys %$href) {
  print $key." is ".$href->{$key};
  print "/n";
}
if ( ref($href) eq "HASH" ) {
  print "href is a reference to a hash./n";
}
unless ( ref($href) ) {
  print "href is not a reference at all./n";
}
print "href is ",ref($href),"./n";