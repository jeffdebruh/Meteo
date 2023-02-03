#!/bin/bash

if [ $# -lt 1 ] ; then
#Verify if the script has enough arguments
	echo "Error, missing arguments";
	exit 7
fi

#almost ervery variable that will be used in the script
i=0;tmp=0;tri=0;f=0;a=0;t1=0;t2=0;t3=0;p1=0;p2=0;p3=0;wd=0;h=0;m=0;min=0;max=0;c=0;r=0

for i in $(seq 1 "$#"); do
#This loop will verify wether or not the arguments are here or not, and if so will verify if they are one or multiple instances of it
	if [ $f -eq 1 ] ; then
	#this loop is used to grab the input file
		a="${!i}";
		if [ ! -e $a ] ; then
			echo "This file does not exist"
			exit 21
		fi
		f=2
	fi
	if [ ! $c -le 0 ] ; then
	#this loop is used to grab the values of the minimum and maximum dates
		case $c in
			'1') min="${!i}";c=2;echo $min;;
			'2') max="${!i}";c=-1;echo $max ;;
			*)echo "Multiple use of an argument"; exit 24 ;;
		esac 
	fi
	case "${!i}" in
#this case verify that eache arguments appear only once 
		'-G') if [ $tmp -eq 0 ] ; then
			tmp=1;
		else
			echo "Multiple use of an argument";
			exit 1
		fi ;;
		'-r') if [ $r -eq 0 ] ; then
			r=1
		else
			echo "Multiple use of an argument";
			exit 30
		fi ;;
		'-F') if [ $tmp -eq 0 ]; then
			tmp=2;
		else
			echo "Multiple use of an argument";
			exit 2
		fi ;;
		'-S') if [ $tmp -eq 0 ] ; then
			tmp=3;
		else
			echo "Multiple use of an argument";
			exit 3
		fi ;;
		'-A') if [ $tmp -eq 0 ] ; then
			tmp=4;
		else
			echo "Multiple use of an argument";
			exit 4
		fi ;;
		'-O') if [ $tmp -eq 0 ] ; then
			tmp=5;
		else
			echo "Multiple use of an argument";
			exit 5
		fi ;;
		'-Q') if [ $tmp -eq 0 ] ; then
			tmp=6;
		else
			echo "Multiple use of an argument";
			exit 6
		fi ;;
		'--tab') if [ $tri -eq 0 ] ; then
			tmp=1;
		else
			echo "Multiple use of an argument";
			exit 7
		fi ;;
		'--abr') if [ $tri -eq 0 ] ; then
			tri=2;
		else
			echo "Multiple use of an argument";
			exit 8
		fi ;;
		'--avl') if [ $tri -eq 0 ] ; then
			tri=3;
		else
			echo "Multiple use of an argument";
			exit 9
		fi ;;
		'-d') if [ $min -eq 0 ] && [ $max -eq 0 ] ; then
			c=$(($c+1))
		else
			echo "Multiple use of an argument";
			exit 23
		fi ;;
		'-h') if [ $h -eq 0 ] ; then
			h=1
		else
			echo "Multiple use of an argument";
			exit 20 
		fi;;
		'-t1') if [ $t1 -eq 0 ] ; then
			t1=1
		else
			echo "Multiple use of an argument";
			exit 13 
		fi;;
		'-t2') if [ $t2 -eq 0 ] ; then
			t2=1
		else
			echo "Multiple use of an argument";
			exit 14
		fi;;
		'-t3') if [ $t3 -eq 0 ] ; then
			t3=1
		else
			echo "Multiple use of an argument";
			exit 14
		fi;;
		'-p1') if [ $p1 -eq 0 ] ; then
			p1=1
		else
			echo "Multiple use of an argument";
			exit 15
		fi;;
		'-p2') if [ $p2 -eq 0 ] ; then
			p2=1
		else
			echo "Multiple use of an argument";
			exit 16
		fi;;
		'-p3') if [ $p3 -eq 0 ] ; then
			p3=1
		else
			echo "Multiple use of an argument";
			exit 17
		fi;;
		'-w') if [ $wd -eq 0 ] ; then
			wd=1
		else
			echo "Multiple use of an argument";
			exit 18
		fi;;
		'-m') if [ $m -eq 0 ] ; then
			m=1
		else
			echo "Multiple use of an argument";
			exit 19
		fi;;
		'-f') if [ ! $f -eq 0 ] ; then
				if [ $f -eq 2 ] ; then
					echo "Multiple use of an argument";
					exit 10
				fi
			else
				f=1
			fi ;;
		*) ;;
	esac
done;

if [ ! $tmp -eq 0 ] ; then
#It will verify the localisation with real life coordinates
	sed -n '1p' $a > meteo2.csv
	cat $a | cut -d ';' -f10 > coo.txt
	sed 1d coo.txt -i
	coo="coo.txt"
	i=2
	while IFS="," read -r x y; do
		case "$tmp" in
			'1') if (( $(echo "$x < 6" |bc -l))) && (($(echo "$x > 2" |bc -l))) && (($(echo "$y > -55" |bc -l))) && (($(echo "$y < -51" |bc -l))); then
				sed -n ''$i'p' $a >> meteo2.csv
				fi ;;
			'2') if (( $(echo "$x < 53" |bc -l))) && (($(echo "$x > 41" |bc -l))) && (($(echo "$y > 6" |bc -l))) && (($(echo "$y < 10" |bc -l))); then
				sed -n ''$i'p' $a >> meteo2.csv
				fi ;;
			'3') if (( $(echo "$x < 47.2" |bc -l))) && (($(echo "$x > 46.7" |bc -l))) && (($(echo "$y > -56.5" |bc -l))) && (($(echo "$y < -56" |bc -l))); then 
				sed -n ''$i'p' $a >> meteo2.csv
				fi ;;
			'4') if (( $(echo "$x < 19" |bc -l))) && (($(echo "$x > 10" |bc -l))) && (($(echo "$y < -58" |bc -l))) && (($(echo "$y > -63" |bc -l))); then 
				sed -n ''$i'p' $a >> meteo2.csv
				fi ;;
			'5') if (( $(echo "$x > -61" |bc -l))) && (($(echo "$x < 10" |bc -l))) && (($(echo "$y > 36" |bc -l))) && (($(echo "$y < 128" |bc -l))); then 
				sed -n ''$i'p' $a >> meteo2.csv
				fi ;;
			'6') if (( $(echo "$x < -65" |bc -l))) && (($(echo "$x > 140" |bc -l))) && (($(echo "$y > 134" |bc -l))) && (($(echo "$y < -56" |bc -l))); then 
				sed -n ''$i'p' $a >> meteo2.csv
				fi ;;
			*) echo "Error" ;exit 12 ;;
		esac
	i=$(($i+1))
	done < "$coo"
fi

dateconvert () {
#convert the date in the file to integer that we can compare and verify that the date is only comprised of numbers
	if [ $# -eq 1 ] ; then 
		a=$(echo $1 | cut -c 1-10 | sed 's/-//g')
		if [[ ! $a =~ [0-9]+ ]]; then 
			if [ ! $a -ge 20100101 ] || [ ! $a -le 20300101 ] ; then
				echo "Date was either to late or to early"
				exit 25
			fi
			echo $a
			return 0
		else
			echo"Invalid date (contained something else than numbers)"
			exit 26
		fi
		else
			echo 0
	fi
}

sortdate () {
#Verify that the dates are inbetween the minimum and maximum ones that were input by the user
cat $1 | cut -d ';' -f2 > date.txt
	sed 1d date.txt -i
	date="date.txt"
	i=2
	min1=`dateconvert $min`
	max1=`dateconvert $max`
		while read line; do
			f=`dateconvert $line`
			if [ $f -ge $min1 ] && [ $f -le $max1 ] ; then
				sed -n ''$i'p' $1 >> $2
			fi
		i=$(($i+1))
		done < "$date"
}
>meteo3.csv

if [ $c -eq -1 ] ; then
#change the file the program will be working on with the right data wether the locations option or the date one was selected by the user
	if [ ! $tmp -eq 0 ] ; then
		sortdate meteo2.csv meteo3.csv
	else
		sortdate $a meteo3.csv
	fi
else
	if [ ! $tmp -eq 0 ] ; then
		cp meteo2.csv meteo3.csv
	else
		cp $a meteo3.csv
	fi
fi

addsc () {
#adds semicolons at the end of each line
cp $1 tmp.txt
awk '{print $0";"}' tmp.txt > $1
rm tmp.txt
}

i=0;
for i in $(seq 1 "$#"); do
#This loop will launch every Gnuplot command, one by one
  case "${!i}" in 
    '-h') cat meteo3.csv | cut -d ';' -f1,10,14 > height.txt
	sed 1d height.txt -i
	addsc height.txt
	if [ $r -eq 0 ] ; then
		./weather -fheight.txt -odata.txt -h
		rm height.txt
		gnuplot -persist h.plt
		rm data.txt
	else
		./weather -fheight.txt -odata.txt -h -r
		rm height.txt
		gnuplot -persist h.plt
		rm data.txt
	fi
      ;;
    '-t1')cat meteo3.csv | cut -d ';' -f1,11,12,13 > temp1.txt
	sed 1d temp1.txt -i
	addsc temp1.txt
	if [ $r -eq 0 ] ; then
		./weather -ftemp1.txt -odata.txt -t1 
		rm temp1.txt
		gnuplot -persist t1.plt
		rm data.txt
	else
		./weather -ftemp1.txt -odata.txt -t1 -r
		rm temp1.txt
		gnuplot -persist t1.plt
		rm data.txt
	fi
      ;;
    '-t2')cat meteo3.csv | tr -d '-'|tr 'T' ';' | cut -d ';' -f2,14 > temp2.txt
	sed 1d temp2.txt -i
	addsc temp2.txt
	if [ $r -eq 0 ] ; then
		./weather -ftemp2.txt -odata.txt -t2
		rm temp2.txt
		gnuplot -persist t2.plt
		rm data.txt
	else
		./weather -ftemp2.txt -odata.txt -t2 -r
		rm temp2.txt
		gnuplot -persist t2.plt
		rm data.txt
	fi
      ;;
    '-t3')cat meteo3.csv | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,14 > temp3.txt
	sed 1d temp3.txt -i
	addsc temp3.txt
	if [ $r -eq 0 ] ; then
		./weather -ftemp2.txt -odata.txt -t3
		rm temp3.txt
		gnuplot -persist t3.plt
		rm data.txt
	else
		./weather -ftemp2.txt -odata.txt -t3 -r
		rm temp3.txt
		gnuplot -persist t3.plt
		rm data.txt
	fi
      ;;
    '-p1')cat meteo3.csv | cut -d ';' -f1,2,7,8 > pressure1.txt
	sed 1d pressure1.txt -i
	addsc pressure1.txt
	if [ $r -eq 0 ] ; then
		./weather -fpressure1.txt -odata.txt -p1
		rm pressure1.txt
		gnuplot -persist p1.plt
		rm data.txt
	else
		./weather -fpressure1.txt -odata.txt -p1 -r
		rm pressure1.txt
		gnuplot -persist p1.plt
		rm data.txt
	fi
    ;;
    '-p2')cat meteo3.csv | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,9,8 > pressure2.txt
	sed 1d pressure2.txt -i
	addsc pressure2.txt
	if [ $r -eq 0 ] ;then 
		./weather -fpressure2.txt -odata.txt -p2
		rm pressure2.txt
		gnuplot -persist p2.plt
		rm data.txt
	else
		./weather -fpressure2.txt -odata.txt -p2 -r
		rm pressure2.txt
		gnuplot -persist p2.plt
		rm data.txt
	fi
    ;;
    '-p3')cat meteo3.csv | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,9,8 > pressure3.txt
	sed 1d pressure3.txt -i
	addsc pressure3.txt
	if [ $r -eq 0 ] ;then 
		./weather -fpressure2.txt -odata.txt -p2
		rm pressure2.txt
		gnuplot -persist p2.plt
		rm data.txt
	else
		./weather -fpressure2.txt -odata.txt -p2 -r
		rm pressure2.txt
		gnuplot -persist p2.plt
		rm data.txt
	fi
	;;
    '-w')cat meteo3.csv | cut -d ';' -f1,4,5,10 > wind.txt
	sed 1d wind.txt -i
	addsc wind.txt
	if [ $r -eq 0 ] ;then 
		./weather -fwind.txt -odata.txt -w
		rm wind.txt
		gnuplot -persist w.plt
		rm data.txt
	else
	./weather -fwind.txt -odata.txt -w -r
		rm w.txt
		gnuplot -persist w.plt
		rm data.txt
	fi
    ;;
    '-m')cat meteo3.csv cut -d ';' -f1,6,10 > moisture.txt
	sed 1d moisture.txt -i
	addsc moisture.txt
	if [ $r -eq 0 ] ;then 
		./weather -fmoisture.txt -odata.txt -m
		rm moisture.txt
		gnuplot -persist p2.plt
		rm data.txt
	else
		./weather -fmoisture.txt -odata.txt -m -r
		rm moisture.txt
		gnuplot -persist m.plt
		rm data.txt
	fi
	rm intermoist
    ;;
    *);;
  esac
done ;

#delete every now useless file
rm meteo3.csv
if [ -e meteo2.csv ] ; then
	rm meteo2.csv
fi

