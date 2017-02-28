use File::Basename;
use strict;

my $catPath = "cat theFullPath | tr -d \"\\r\\n\"";
my $startPath = `$catPath`;

print ">>>> start: $startPath\n"

