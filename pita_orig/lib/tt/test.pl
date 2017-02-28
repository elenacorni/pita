#!/usr/bin/perl
use File::Basename;
use strict;
use Cwd;

our ( $path );
$path = cwd();
print "path: $path\n";

our ($startPath) = dirname($path);
print "startPath: $startPath\n";

print "my name is: $0\n\n";

