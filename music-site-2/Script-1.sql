create table if not exists genre (
	id SERIAL primary key,
	name VARCHAR(60) unique not null
);

create table if not exists artist (
	id SERIAL primary key,
	name VARCHAR(40) not null
);

create table if not exists artist_genre (
	genre_id INTEGER references genre(id),
	artist_id INTEGER references artist(id),
	constraint ag_pk primary key (genre_id, artist_id)
);

create table if not exists album (
	id SERIAL primary key,
	name VARCHAR(60) not null,
	release_date DATE not null 
);

create table if not exists album_artist (
	artist_id INTEGER references artist(id),
	album_id INTEGER references album(id),
	constraint aa_pk primary key (artist_id, album_id)
);

create table if not exists track ( 
	id SERIAL primary key,
	album_id INTEGER references album(id),
	name VARCHAR(60) not null,
	duration INTEGER not null 
);

create table if not exists track_collection (
	id SERIAL primary key,
	name VARCHAR(60) not null,
	release_date DATE not null 
);

create table if not exists collections ( 
	track_collection_id INTEGER references track_collection(id),
	track_id INTEGER references track(id),
	constraint c_pk primary key (track_collection_id, track_id)
);

