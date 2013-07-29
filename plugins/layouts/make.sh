#!/bin/sh

IMPORT="-I /Users/bjd/.rvm/gems/ruby-1.9.3-p392/gems/breakpoint-2.0.5/stylesheets -I /Users/bjd/.rvm/gems/ruby-1.9.3-p392/gems/zen-grids-1.4/stylesheets"
REQUIRE="-r /Users/bjd/.rvm/gems/ruby-1.9.3-p392/gems/breakpoint-2.0.5/lib/breakpoint.rb -r /Users/bjd/.rvm/gems/ruby-1.9.3-p392/gems/zen-grids-1.4/lib/zen-grids.rb"

sass --compass $IMPORT $REQUIRE --update -t expanded -f bartlett:bartlett
sass --compass $IMPORT $REQUIRE --update -t expanded -f bartlett_flipped:bartlett_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f boxton:boxton
sass --compass $IMPORT $REQUIRE --update -t expanded -f brenham:brenham
sass --compass $IMPORT $REQUIRE --update -t expanded -f brenham_flipped:brenham_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f brown:brown
sass --compass $IMPORT $REQUIRE --update -t expanded -f bryant:bryant
sass --compass $IMPORT $REQUIRE --update -t expanded -f bryant_flipped:bryant_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f burr:burr
sass --compass $IMPORT $REQUIRE --update -t expanded -f burr_flipped:burr_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f geary:geary
sass --compass $IMPORT $REQUIRE --update -t expanded -f harris:harris
sass --compass $IMPORT $REQUIRE --update -t expanded -f hewston:hewston
sass --compass $IMPORT $REQUIRE --update -t expanded -f hewston_flipped:hewston_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f mccoppin:mccoppin
sass --compass $IMPORT $REQUIRE --update -t expanded -f moscone:moscone
sass --compass $IMPORT $REQUIRE --update -t expanded -f moscone_flipped:moscone_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f phelan:phelan
sass --compass $IMPORT $REQUIRE --update -t expanded -f pond:pond
sass --compass $IMPORT $REQUIRE --update -t expanded -f rolph:rolph
sass --compass $IMPORT $REQUIRE --update -t expanded -f sanderson:sanderson
sass --compass $IMPORT $REQUIRE --update -t expanded -f sanderson_flipped:sanderson_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f selby:selby
sass --compass $IMPORT $REQUIRE --update -t expanded -f selby_flipped:selby_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f sutro:sutro
sass --compass $IMPORT $REQUIRE --update -t expanded -f sutro_double:sutro_double
sass --compass $IMPORT $REQUIRE --update -t expanded -f taylor:taylor
sass --compass $IMPORT $REQUIRE --update -t expanded -f taylor_flipped:taylor_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f webb:webb
sass --compass $IMPORT $REQUIRE --update -t expanded -f webb_flipped:webb_flipped
sass --compass $IMPORT $REQUIRE --update -t expanded -f whelan:whelan
