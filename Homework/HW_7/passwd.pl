#!/usr/bin/perl

my %out;
my @usrs;
my $text;

open($text, '<', '/etc/passwd') or die;

while (my $line = <$text>) {
	chomp $line;
	my @x = split(/:/, $line);
	push (@usrs, $x[0]);
	$out{$x[0]} = $x[6];
}

foreach my $key (@usrs) {
	print "$key $out{$key}\n";
} 

