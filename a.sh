#!/bin/bash

if [ $# -lt 1 ] ; then
	echo "Error, missing arguments";
	exit 7
fi

i=0;tmp=0;tri=0;f=0;a=0;t1=0;t2=0;t3=0;p1=0;p2=0;p3=0;wd=0;h=0;m=0;min=0;max=0;c=0
for i in $(seq 1 "$#"); do
	if [ $f -eq 1 ] ; then
		a="${!i}";
		if [ ! -e $a ] ; then
			exit 21
		fi
		f=2
	fi
	if [ ! $c -le 0 ] ; then
		case $c in
			'1') min="${!i}";c=2;echo $min;;
			'2') max="${!i}";c=-1;echo $max ;;
			*) exit 24 ;;
		esac 
	fi
	case "${!i}" in
		'-G') if [ $tmp -eq 0 ] ; then
			tmp=1;
		else
			exit 1
		fi ;;
		'-F') if [ $tmp -eq 0 ]; then
			tmp=2;
		else
			exit 2
		fi ;;
		'-S') if [ $tmp -eq 0 ] ; then
			tmp=3;
		else
			exit 3
		fi ;;
		'-A') if [ $tmp -eq 0 ] ; then
			tmp=4;
		else
			exit 4
		fi ;;
		'-O') if [ $tmp -eq 0 ] ; then
			tmp=5;
		else
			exit 5
		fi ;;
		'-Q') if [ $tmp -eq 0 ] ; then
			tmp=6;
		else
			exit 6
		fi ;;
		'--tab') if [ $tri -eq 0 ] ; then
			tmp=1;
		else
			exit 7
		fi ;;
		'--abr') if [ $tri -eq 0 ] ; then
			tri=2;
		else
			exit 8
		fi ;;
		'--avl') if [ $tri -eq 0 ] ; then
			tri=3;
		else
			exit 9
		fi ;;
		'-d') if [ $min -eq 0 ] && [ $max -eq 0 ] ; then
			c=$(($c+1))
		else 
			exit 23
		fi ;;
		'-h') if [ $h -eq 0 ] ; then
			h=1
		else
			exit 20 
		fi;;
		'-t1') if [ $t1 -eq 0 ] ; then
				t1=1
			else
				exit 13 
			fi;;
		'-t2') if [ $t2 -eq 0 ] ; then
				t2=1
			else
				exit 14
			fi;;
		'-t3') if [ $t3 -eq 0 ] ; then
				t3=1
			else
				exit 14
			fi;;
		'-p1') if [ $p1 -eq 0 ] ; then
				p1=1
			else
				exit 15
			fi;;
		'-p2') if [ $p2 -eq 0 ] ; then
				p2=1
			else
				exit 16
			fi;;
		'-p3') if [ $p3 -eq 0 ] ; then
				p3=1
			else
				exit 17
			fi;;
		'-w') if [ $wd -eq 0 ] ; then
				wd=1
			else
				exit 18
			fi;;
		'-m') if [ $m -eq 0 ] ; then
				m=1
			else
				exit 19
			fi;;
		'-f') if [ ! $f -eq 0 ] ; then
				if [ $f -eq 2 ] ; then
					exit 10
				fi
			else
				f=1
			fi ;;
		*) ;;
	esac
done;

if [ ! $tmp -eq 0 ] ; then
	sed -n '1p' $a > meteo2.csv
	cat $a | head -n1000 | cut -d ';' -f10 > coo.txt
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
			*) exit 12 ;;
		esac
	i=$(($i+1))
	done < "$coo"
fi

dateconvert () {
	if [ $# -eq 1 ] ; then 
		a=$(echo $1 | cut -c 1-10 | sed 's/-//g')
		if [[ ! $a =~ [0-9]+ ]]; then 
			if [ ! $a -ge 20100101 ] || [ ! $a -le 20300101 ] ; then 
				exit 25
			fi
			echo $a
			return 0
		else 
			exit 26
		fi
		else
			echo 0
	fi
}

sortdate () {
cat $1 | head -n50 | cut -d ';' -f2 > date.txt
	sed 1d date.txt -i
	date="date.txt"
	i=2
	min1=`dateconvert $min`
	max1=`dateconvert $max`
	echo $min1
	echo $max1
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

add () {
cp $1 tmp.txt
awk '{print $0";"}' tmp.txt > $1
}

i=0;
for i in $(seq 1 "$#"); do
  case "${!i}" in 
    '-h') cat meteo3.csv | head -n50 | cut -d ';' -f1,14 > height.txt
	sed 1d height.txt -i
	add height.txt
      ;;
    '-t1')cat meteo3.csv | head -n50 | cut -d ';' -f1,11,12,13 > temp1.txt
	sed 1d temp1.txt -i
	add temp1.txt
      ;;
    '-t2')cat meteo3.csv | head -n50 | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,12 > temp2.txt
	sed 1d temp2.txt -i
	add temp2.txt
      ;;
    '-t3')cat meteo3.csv | head -n50 | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,12 > temp3.txt
	sed 1d temp3.txt -i
	add temp3.txt
      ;;
    '-p1')cat meteo3.csv | head -n50 | cut -d ';' -f1,2,7,8 > pressure1.txt
	sed 1d pressure1.txt -i
	add pressure1.txt
    ;;
    '-p2')cat meteo3.csv | head -n50 | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,9,8 > pressure2.txt
	sed 1d pressure2.txt -i
	add pressure2.txt
    ;;
    '-p3')cat meteo3.csv | head -n50 | tr -d '-'|tr 'T' ';' | cut -d ';' -f1,2,9,8 > pressure3.txt
	sed 1d pressure3.txt -i
	add pressure3.txt
    ;;
    '-w')cat meteo3.csv | head -n50 | cut -d ';' -f1,4,5,10 > wind.txt
	sed 1d wind.txt -i
	add wind.txt
    ;;
    '-m')cat meteo3.csv | head -n50 | cut -d ';' -f1,6,10 > moisture.txt
	sed 1d moisture.txt -i
	add moisture.txt
    ;;
    *);;
  esac
done ;
