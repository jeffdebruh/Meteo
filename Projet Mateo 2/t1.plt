set datafile separator ";"
	set xlabel "Stations ID"
	set ylabel "Temperatures"
	set style fill solid 1.00 border lt -1
	fillcolor = "#80E0A080"
	plot "data.txt" using 1:3:4 w filledcurve fc rgb fillcolor title "Max Min range",	'' using 1:2 smooth mcspline lw 2 title "Average"
