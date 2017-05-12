 #! /bin/sh

nomFic=codeExecuteeValgrind
cheminAcces=./resultatDebug/
vide="Status: install ok installed"
install=`dpkg -s valgrind | grep Status` >/dev/null
rep="j"

pwd

if [ "$install" != "$vide" ]
then
	echo "[Make Valgrind] Souhaitez vous installer Valgrind pour pouvoir continuer ? y/n"

	while [ $rep != "y" || $rep != "n" ]
	do
		read rep
	done
	
	if ( rep = "y" )
	then
		sudo apt-get install valgrind
	else
		echo "[Make Valgrind] Vous ne souhaitez continuer, fin du programme"
		exit 1
	fi
fi

if [ -f "$cheminAcces$nomFic" ]
then
	rm $cheminAcces$nomFic
fi

valgrind ./"$1" >"$nomFic" 
mv "$nomFic" "$cheminAcces$nomFic"

echo "[Make Valgrind] Sauvegarde du code executé par valgrind dans resultatDebug/codeExecuteeValgrind"

exit 0
