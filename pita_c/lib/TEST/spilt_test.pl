#!/usr/bin/perl

use strict;

    my $str = "root:*:0:0:System Administrator:/var/root:/bin/sh";
        my @fields = split (/:/, $str);
	print "@fields\n";
	    my $username = $fields[0];
	        my $real_name = $fields[4];
		print "$str\n";
		    print "$username\n";
		     print "@fields[1]\n";
		                     print "@fields[2]\n";
				                     print "@fields[3]\n";
		        print "$real_name\n";
			print "@fields[5]\n";
			print "@fields[6]\n";

