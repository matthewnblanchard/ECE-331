#!/usr/bin/perl
# use strict;
# use warnings;

open (IN, "$ARGV[0]")
         or die "Failed to open file: '$ARGV[0]'\n";

while (<IN>) {
        $line = $_;
        # print $line;    # DEBUG
        @t = split / /, $line;  # Split off Date/Time info
        
        # Check date
        # print "$t[0]\n"; #DEBUG
        next unless ($t[0] =~ /^\d{4}-(0[1-9]|1[0-2])-([0-2]\d|3[01])$/); 

        # Check time
        # print "$t[1]\n"; #DEBUG
        next unless ($t[1] =~ /^([01]\d|2[0-3]):[0-5]\d:[0-5]\d$/);

        # Check timezone
        # print "$t[2]\n"; #DEBUG
        next unless ($t[2] =~ /^\w{3}:$/);

        # Split off receive path info
        @receive = split /,/, $t[3];
        
        # Check for SSID of packet origin/destination
        # print "$receive[0]\n"; #DEBUG
        next unless ($receive[0] =~ /^\w+-\d+>AP\w+$/);

        # Check for fields up to Q-Construct
        $i = 0;           # Counter
        $exit = 0;        # Exit flag
        until ($receive[$i++] =~ /^qA[a-zA-Z]$/) {
                $exit = 1 unless ($receive[$i - 1] =~ /[\w*-]+$/);
                # print "$receive[$i - 1]\n"; # DEBUG
        }       
        next if ($exit);
        
        # Check for SSID of IGate
        # print "$receive[$i]\n"; # DEBUG
        next unless ($receive[$i] =~ /^\w+(-?)\w*:\//);

        # Split off location,temp,speed,etc info
        @param = split /\//, $line;

        # Check transit time & Latitude
        # print "$param[$1]\n"; # DEBUG
        next unless ($param[1] =~ /^([01]\d|2[0-3])[0-5]\d[0-5]\d[hz]([0-8]\d|90)[0-5]\d\.\d{2}[NS]$/);

        # Check longitude/Object symbol/Course
        next unless ($param[2] =~ /^(0\d{2}|1[0-7]\d|180)[0-5]\d\.\d{2}[EW]\S\d{3}$/);

        # Check speed
        next unless ($param[3] =~ /^\d{3}$/);

        # Check altitude (feet)
        next unless ($param[4] =~ /^A=\d{6}((!\S{3}!)?)$/);

        # Grab additional fields until whitespace is hit (indicates end of line or notes)
        $i = 5;
        $exit = 0;      # Break out and exit if a field doesn't match one of the accepted formats
        until ($param[$i++] =~ /^\S+\s\S*$/) {
                $exit = 0;
                next if ($param[$i - 1] =~ /^a=\d+\.\d$/);
                next if ($param[$i - 1] =~ /^R=(-?)\d+$/);
                next if ($param[$i - 1] =~ /^Ti=(-?)\d+$/);
                next if ($param[$i - 1] =~ /^Te=(-?)\d+((\d+\.\d+ up \d+\.\d+ down)?)$/);
                next if ($param[$i - 1] =~ /^V=\d+$/);
                next if ($param[$i - 1] =~ /^T=(-?)\d+$/);
                next if ($param[$i - 1] =~ /^t=(-?)\d+$/); 
                $exit = 1;
                last;
        }
        next if ($exit);

        # Grab last field prior to notes
        $exit = 1;
        $exit = 0 if ($param[$i - 1] =~ /^a=\d+\.\d$/);
        $exit = 0 if ($param[$i - 1] =~ /^R=(-?)\d+$/);
        $exit = 0 if ($param[$i - 1] =~ /^Ti=(-?)\d+$/);
        $exit = 0 if ($param[$i - 1] =~ /^Te=(-?)\d+((\d+\.\d+ up \d+\.\d+ down)?)$/);
        $exit = 0 if ($param[$i - 1] =~ /^V=\d+$/);
        $exit = 0 if ($param[$i - 1] =~ /^T=(-?)\d+$/);
        $exit = 0 if ($param[$i - 1] =~ /^t=(-?)\d+$/); 
        next if ($exit);

        print $line;
} 
