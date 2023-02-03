set autoscale
set datafile separator ";"
set xlabel "longitude"
set ylabel "latitude"
set size square
plot "data.txt" using 4:5:($3*cos(2*pi*$2/360)):($3*sin(2*pi*$2/360)) w vectors title "Wind"
