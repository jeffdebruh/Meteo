set dgrid3d
set datafile separator ";"
set xlabel "longitude"
set ylabel "latitude"
set pm3d map intermolate 64,64
splot "data.txt" using 2:3:4 w pm3d title "height of different stations"
