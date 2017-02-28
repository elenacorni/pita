#!/usr/bin/perl
use File::Basename;
use strict;

require "lib/load_args.pl";
require "lib/format_number.pl";

sub removeIllegalXMLChars
{
   my $str = $_[0];

   my $res_str = "";
   for (my $i = 0; $i < length($str); $i++) {
      my $char = substr($str, $i, 1);
      if ((ord($char) >= 32 and ord($char) <= 126) or ord($char) == 10 or ord($char) == 9) {
         $res_str .= $char;
         }
   }

   $res_str =~ s/\&/&amp;/g;
   $res_str =~ s/\"/&quot;/g;
   $res_str =~ s/\'/&apos;/g;
   $res_str =~ s/\</&lt;/g;
   $res_str =~ s/\>/&gt;/g;

   return $res_str;
}





