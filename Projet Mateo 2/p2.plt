set datafile separator ";"
	set xlabel "Date/hour"
	set ylabel "Pressures"
	set style fill solid 1.00 border lt -1
	plot "data.txt" '' using 1:2 smooth mcspline lw 2 title "pressures"
