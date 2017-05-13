#! /bin/sh

dossierSauvegarde=save
dossierUtilisateur=user

if [ ! -d "$dossierUtilisateur" ]
then
	mkdir "$dossierUtilisateur"
fi

if [ ! -d "$dossierSauvegarde" ]
then
	mkdir "$dossierSauvegarde"
fi

exit 0
