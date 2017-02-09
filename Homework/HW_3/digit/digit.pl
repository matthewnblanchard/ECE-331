#!usr/bin/perl
while(<STDIN>) {
        print if (/(\b100\b)|(\b[[:digit:]]{1,2}\b)/);
        next;
}
