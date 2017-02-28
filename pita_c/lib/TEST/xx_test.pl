#!/usr/bin/perl

use strict;
use List::Util qw[shuffle min max];

use strict;
use List::Util qw[shuffle min max];

my $file_ref;
my $file = $ARGV[0];
if (length($file) < 1 or $file =~ /^-/) 
{
  print STDERR "length-file: " . length($file) . " file: " . $file . "\n";
  $file_ref = \*STDIN;
}
else
{
  open(FILE, $file) or die("Could not open file '$file'.\n");
  $file_ref = \*FILE;
}

my $done = 0;
my $record;
print STDERR "\ndone:         " . $done . "\n";
print STDERR "record:     " . $record . "\n";
print STDERR "file:         " . $file . "\n";
print STDERR "file_ref:     " . $file_ref . "\n";

print STDERR "<\$file_ref>: " . <$file_ref> . "\n";
print STDERR "<\$file_ref>: " . <$file_ref> . "\n";

if (!($record = <$file_ref>))
{
  $done = 1;
}

print STDERR "\ndone-dopo:    " . $done . "\n";
print STDERR "record-dopo:  " . $record . "\n";
print STDERR "file-dopo:    " . $file . "\n";
print STDERR "file_rf-dopo: " . $file_ref . "\n";
