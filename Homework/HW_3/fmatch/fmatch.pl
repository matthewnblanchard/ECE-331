#!/usr/bin/perl
while(<STDIN>) {
        print if (/^(([+-]?\d*\.?\d+)|([+-]?\d+\.?\d*))$/);
        next;
}
