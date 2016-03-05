use constant WEEKABBR =>{
      'Monday' => 'Mon',
      'Tuesday' => 'Tue',
      'Wednesday' => 'Wed',
      'Thursday' => 'Thu',
      'Friday' => 'Fri'};
# ------------------------------------------------------------------------
%abbr = WEEKABBR;
$day = 'Wednesday';
#print "The abbrevaiation for $day is ", $abbr{$day};
print $abbr{$day};
