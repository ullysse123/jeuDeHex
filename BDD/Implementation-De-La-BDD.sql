drop table jouer;
drop table joueur;
drop table coup;
drop table dateP;

create table dateP (
	IdDate Number,
	Heure Number,
	Jour Number,
	Mois varchar2(10),
	Annee Number,
	constraint ck_jour check (Jour between 1 and 31),
	constraint ck_annee check (Annee>2016),
	constraint ck_mois check ( Mois in('janvier','fevrier','mars','avril','mai','juin','juillet','aout','septembre','octobre','novembre','decembre')),
	constraint ck_heure check (Heure between 0 and 23),
	constraint pk_dateP Primary Key(IdDate)
);

create table coup (
	IdCoup Number,
	Couleur varchar2(10),
	X Number,
	Y Number,
	Numero Number,
	constraint ck_couleur check (Couleur in('rouge','noir','blanc')),
	constraint ck_numero check (Numero>0),
	constraint ck_x check (x>=0),
	constraint ck_y check (y>=0),
	constraint pk_coup Primary Key(IdCoup)
);

create table joueur (
	Pseudo varchar2(30),
	Mail varchar2(50),
	Annee Number,
	constraint ck_mail check (Mail like '%@%'),
	constraint ck_anneePseudo check (Annee>2016),
	constraint pk_joueur Primary Key(Pseudo)
);

create table jouer (
	Pseudo varchar2(30),
	IdDate Number,
	IdCoup Number,
	Status varchar2(15),
	constraint fk_jouer_pseudo Foreign Key(Pseudo) References joueur(Pseudo),
	constraint fk_jouer_iddate Foreign Key(IdDate) References dateP(IdDate),
	constraint fk_jouer_idcoup Foreign Key(IdCoup) References coup(IdCoup),
	constraint ck_status check (Status in('abandonnee','gagnee','perdue')),
	constraint pk_jouer Primary Key(Pseudo,IdDate,IdCoup)
);


	
