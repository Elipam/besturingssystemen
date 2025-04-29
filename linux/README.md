4.1 Kan je bestand per scherm laten zien, zodat het in je terminal past en nog steeds door te lezen valt.
4.2 tail -f "bestandsnaam"
4.3 apropos "numbers"
4.4 seq -s "#" 1 10

5.1 nano gisteren
5.2 cat gisteren gisteren
5.3 cat gisteren gisteren gisteren > gisteren3
5.4 less gisteren3
Pagina omlaag: spatiebalk of f
Pagina omhoog: b
Einde bestand: G (shift+g)
Begin bestand: g
Zoeken: / "zoekterm"
Volgende zoekinstantie: n
Verlaten: q
5.5 ping -i.2 localhost | less
5.6 less < /dev/random
5.7 cut - remove sections from each line of files
sort - sort lines of text files
head - output the first part of files
tail - output the last part of files
wc - print newline, word, and byte counts for each file
5.8 sort -r gisteren
5.9 cut -c1 gisteren
5.10 wc -l gisteren3
5.11 head -n 5 gisteren3
5.12 tail -n 3 gisteren3
5.13 head -n 5 gisteren3 | tail -n 3 | wc -c, telt linebreak ook als character

6.1 pwd
6.2 cd /
6.3 cd /usr/bin
6.4 cd
6.5 /home
6.6 ls /usr | wc -l
6.7 ls -l ~
6.8 bestandrechten, aantal verwijzingen naar het bestand, eigenaar van het bestand (eigenaarrechten), groep van het bestand (groeprechten), bestandgrootte, wijzigingdatum, naam

7.1 mkdir ~/eerste
7.2 mkdir ~/eerste/tweede
7.3 touch ~/mijnBestand
7.4 mv ~/mijnBestand ~/eerste/tweede/
7.5 cp ~/eerste/tweede/mijnBestand ~/
7.6 mv ~/mijnBestand ~/eenAnderBestand
7.7 cp ~/eenAnderBestand /, foutmelding, want geen sudo rechten
7.8 rm ~/eenAnderBestand
7.9 rmdir ~/eerste, kan het niet weghalen, want er zitten nog bestanden in
7.10 mv ~/eerste/tweede ~/
7.11 rmdir ~/eerste

8.1 ls -l /usr/bin/s*
8.2 ls -l /usr/bin/*a*b* /usr/bin/*b*a\*
8.3 ls -l /usr/bin/?????

9.1 users en groups worden executablerechten verleend
9.2 chmod a+w mijnBestand
9.3 chmod a+r,a-x,u+x mijnBestand
ls -l mijnBestand

10.1 df -h
10.2 du -sh ~

11.1 nano datum.sh
echo "Hallo gebruiker, het is nu:"
date
chmod a+x datum.sh
./datum.sh
11.2 nano hallo.sh
naam="Jouw Naam"
echo "Hallo $naam, hoe gaat het met je?"
        chmod a+x hallo.sh
        ./hallo.sh
11.3    nano woordenteller.sh
        aantal=`wc -w < gisteren`
        echo "Het bestand 'gisteren' bevat $aantal woorden."
        chmod a+x woordenteller.sh
        ./woordenteller.sh
11.4    nano woordenteller2.sh
        bestand=$1
        aantal=`wc -w < $bestand`
        echo "Het bestand '$bestand' bevat $aantal woorden."
        chmod a+x woordenteller2.sh
        ./woordenteller2.sh gisteren
11.5    nano woordenteller3.sh
        bestand=$1
        if [[ -z $bestand ]]; then
            echo "Fout: geen bestandsnaam opgegeven."
            echo "Gebruik: $0 bestandsnaam"
            exit 1
        fi
        aantal=`wc -w < $bestand`
        echo "Het bestand '$bestand' bevat $aantal woorden."
        chmod a+x woordenteller3.sh
        ./woordenteller3.sh gisteren
11.6    nano beerteller.sh
        for (( i = 100; i > 0; i-- )); do
            if (( i > 1 )); then
                echo "$i bottles of beer on the wall, $i bottles of beer."
                if (( i-1 > 1 )); then
                    echo "If one of those bottles would happen to fall, there'd be $(i-1) bottles of beer on the wall."
                else
                    echo "If one of those bottles would happen to fall, there'd be 1 bottle of beer on the wall."
                fi
            else
                echo "1 bottle of beer on the wall, 1 bottle of beer."
                echo "If that bottle would happen to fall, there'd be no bottles of beer on the wall."
            fi
        done
        chmod a+x beerteller.sh
        ./beerteller.sh
11.7    nano hernoemd.sh
        for bestand in *; do
            # Controleer of het een bestand is (en geen directory)
            if [[ -f $bestand ]]; then
                # Controleer of de naam nog niet eindigt op -hernoemd
                if [[ $bestand != *-hernoemd ]]; then
                    mv "$bestand" "${bestand}-hernoemd"
echo "Hernoemd: $bestand naar ${bestand}-hernoemd"
fi
fi
done
chmod a+x hernoemd.sh
./hernoemd.sh
11.8 nano script1
export naam="Jouw Naam" # Vervang door je eigen naam
echo "In script1, naam is: $naam"
./script2
echo "Terug in script1, naam is: $naam"
nano script2
echo "In script2, naam is: $naam"
naam="Gewijzigd in script2"
echo "In script2, na wijziging, naam is: $naam"
chmod a+x script1 script2
./script1

12.1 ps
1031 pts/0 00:00:00 bash
1717 pts/0 00:00:00 ps
12.2 ps a 6
12.3 ps u 2
12.4 ps a | sort

13.1 uname; hostname
13.2 uname & hostname
Het verschil is dat bij de ampersand (&) beide commando's tegelijk starten, maar de uitvoer kan door elkaar lopen met andere processen er ook bij. Bij punt-komma (;) wordt eerst uname volledig uitgevoerd, dan pas hostname.
13.3 ping localhost &
13.4 ping localhost
[Ctrl]+[Z]
bg
13.5 jobs
[1]+ Running ping localhost &
ps
11341 pts/0 00:00:00 ping
13.6 kill %1  
 kill 1234  
 fg
[Ctrl]+[C]

14.1 top
14.2 nice 10 top
14.3 sudo renice -n -20 -p [PID]

15 c++ -o race_prio race_prio.cpp -lpthread
Zet nrg-base aan om de processor te beladen, zodat je het verschil goed kan zien
sudo ./race_prio

16 Signal number is dan 15
./catch_signal
verander kill(processNo, SIGINT/SIGUSR2/SIGTERM/SIGUSR1);
make
./send_signal

17 Eerste versie zonder aanpassingen werkt toch gewoon???
make
./receive_message
./send_message
