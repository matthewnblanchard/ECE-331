<?php
if (array_key_exists("year",$_POST)) {
	process($_POST["year"]);
}

function process($year)
{
        # Get current date
	$date = new DateTime('now');
        $cyear = $date->format('Y');     
	$cmonth = $date->format('F');
        $cdom = $date->format('j');

        # Bring date back to target year
	if ($cyear > $year) {
		$d = $cyear - $year;
		$date->sub(new DateInterval('P' . $d . 'Y'));
	} else {
		$d = $year - $cyear;
		$date->add(new DateInterval('P' . $d . 'Y'));
        }

        # Scroll back to beginning of year
        $date->setDate($date->format('Y'), 1, 1);

        # Print date object for debugging
        print_r($date);

        # Create tables by month
        for ($m = 1; $m <= 12; $m++) {

                # Create table
                $month = $date->format('F');
	        print "<TABLE Border=1>\n";
	        print "<TR><TH COLSPAN=7>$month $year</TR>\n";
                print "<TR><TH>Sun<TH>Mon<TH>Tue<TH>Wed<TH>Thu<TH>Fri<TH>Sat<TH></TR>\n";

                # Set day back to first of month
                $date->setDate($date->format('Y'), $date->format('m'), 1);

                # If weekday is not Sunday, scroll back to week beginning
                $wd = $date->format('w');
                if ($wd != 0) {
                        $date->sub(new DateInterval('P' . $wd . 'D'));
                }
                
                for ($i = 0; $i < (7*6); $i++) {        # Iterate over maximally 6 weeks
        
                        # Start the week if the day is a multiple of 7
	        	if (($i % 7 ) == 0) {     
	        		print "<TR>";
                        }

                        # Highlight cell if it's the current date
        		$dom = $date->format('j');     
        		if (($date->format('Y') == $cyear) and ($dom == $cdom) and ($month == $cmonth)) {  
		        	print "<TD ALIGN=\"CENTER\" BGCOLOR=\"#FFFFAA\">$dom";
		        } else {                        # Otherwise just print it
			        print "<TD ALIGN=\"CENTER\">$dom";
                        }

                        # End the week if it's the last day
		        if (($i % 7) == 6) {
                                print "</TR>";
                                
                                # Increment date
		                $date->add(new DateInterval('P1D'));

                                # Stop iterating if  the next week would hit the end of
                                # the month
			        if ($date->format('F') != $month) {    
				        break;
			        }
                        } else {
                                # Increment date
                                $date->add(new DateInterval('P1D'));
                        }
	        }
	        print "</TABLE>\n";
        }
	return;
}
?>
</BODY>
</HTML>
<?php
