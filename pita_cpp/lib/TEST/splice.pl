#!/usr/bin/perl

my $start = 0;
my $size  = 8;
my @dwarfs = qw(Doc Grumpy Happy Sleepy Sneezy Dopey Bashful aaa gg y   uuuuu dddd   cccc   eee  ll);
print "\n@dwarfs\n";
my @who = splice(@dwarfs, $start, $size);
print "splice(arr,$start, $size)\n";
print "> array-mod:     @dwarfs\n";
print "> return-splice: @who\n\n";

