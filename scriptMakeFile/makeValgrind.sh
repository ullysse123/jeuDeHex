 #! /bin/sh

nomFic=resultatValgrind
cheminAcces=../resultatDebug/

install=`dpkg -l | grep valgrind`
rep="j"

if ( "$install" != "" )
then
	echo "Souhaitez vous installer Valgrind pour pouvoir continuer ? y/n"

	while ( $rep != "y" | $rep != "n" )
	do
		read rep
	done
	
	if ( rep = "y" )
	then
		sudo apt-get install valgrind
	else
		echo "Vous ne souhaitez continuer, fin du programme"
		exit 1
	fi
fi

if ( -f "$cheminAcces$nomFic" )
then
	rm $cheminAcces$nomFic
fi

valgrind ../$1 >"$cheminAcces$nomFic"

echo "[Make Valgrind] Sauvegarde des resultats du valgrind dans resultatDebug/resultatValgrind"

exit 0
