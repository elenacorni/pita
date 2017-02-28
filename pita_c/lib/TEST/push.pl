#!/usr/bin/perl

    my @names = ('Foo', 'Bar');
    push @names, 'Moo';
    print "@names\n";     # Foo Bar Moo
     
    my @others = ('Darth', 'Vader');
    push @names, @others;
    print "@names\n";     # Foo Bar Moo Darth Vader

    my $stringa = "elena\tcorni\tciao\tciao\tprova";
    print "stringa: $stringa\n";
    push(@names, $stringa);
    print "names: @names\n";
    print "names[6]: $names[5]\n\n"
