if [ ! -e meteo2.csv ] ; then
			cp meteo.csv meteo2.csv
fi

h=0 ; t=0; i=0;
for i in $(seq 1 "$#"); do
  case "${!i}" in 
    '-h') echo "h" > height.txt;
	 	cat meteo2.csv | head -n3 | cut -d ';' -f1,14 >> height.txt
    wc -l height.txt >> height.txt
      ;;
    '-t1') echo "t1" > temp1.txt
		cat meteo2.csv | head -n3 | cut -d ';' -f1,10,11,12 >> temp1.txt
    wc -l temp1.txt >> temp1.txt
      ;;
    '-t2') echo "t2" > temp2.txt
		cat meteo2.csv | head -n3 | cut -d ';' -f2,10 >> temp2.txt
    wc -l temp2.txt >> temp2.txt
      ;;
    '-t3') ehco "t3" > temp3.txt
	 cat meteo2.csv | head -n3 | cut -d ';' -f1,2,10 >> temp3.txt
    wc -l temp3.txt >> temp3.txt
      ;;
    '-p1') echo "p1" > pressure1.txt
	 	cat meteo2.csv | head -n3 | cut -d ';' -f1,2,7,8 >> pressure1.txt
    wc -l pressure1.txt >> pressure1.txt
    ;;
    '-p2') echo "p2" > pressure2.txt
		cat meteo2.csv | head -n3 | cut -d ';' -f2,7,8 >> pressure2.txt
    wc -l pressure2.txt >> pressure2.txt
    ;;
    '-p3') echo "p3" > pressure3.txt
		cat meteo2.csv | head -n3 | cut -d ';' -f1,2,7,8 >> pressure3.txt
    wc -l pressure3.txt >> pressure3.txt
    ;;
    '-w') echo "w" > wind.txt
		cat meteo2.csv | head -n3 | cut -d ';' -f1,4,5 >> wind.txt
    wc -l wind.txt >> wind.txt
    ;;
    '-m') echo "m" > moisture.txt
		cat meteo2.csv | head -n3 | cut -d ';' -f6 >> moisture.txt
		wc -l moisture.txt >> moisture.txt
    ;;
    *) echo "idk" ;;
  esac
done ;
