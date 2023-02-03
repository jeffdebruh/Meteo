set dgrid3d
set datafile separator ";"
set xlabel "longitude"
set ylabel "latitude"
set pm3d map intermolate 100,100
splot "data.txt" using 4:3:1 w pm3d title "mosture level of different stations"
