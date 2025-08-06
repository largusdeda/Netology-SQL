insert into genre (name)
values 
('Rock'), 
('Post-punk'), 
('Post-hardcore'), 
('Metal'), 
('Synth-pop');


insert into artist (name)
values 
('Scorpions'),
('Metallica'),
('The Cure'),
('A-ha'),
('Ultravox'),
('Camouflage'),
('Thursday'),
('Finch'),
('Sienna Skies');


insert into artist_genre (genre_id, artist_id)
values 
(1, 1),
(1, 3),
(1, 4),
(1, 5),
(1, 8),
(2, 3),
(2, 5),
(3, 7),
(3, 8),
(3, 9),
(4, 1),
(4, 2),
(4, 8),
(4, 9),
(5, 4),
(5, 5),
(5, 6);


insert into album (id, name, release_date)
values
(1, 'Lovedrive', '1979-02-25'),
(2, 'Blackout', '1982-03-29'),
(3, 'Master of Puppets', '1986-03-03'),
(4, 'The Black Album', '1991-08-12'),
(5, 'The Head on the Door', '1985-08-30'),
(6, 'Disintegration', '1989-05-02'),
(7, 'Hunting High and Low', '1985-06-01'),
(8, 'Scoundrel Days', '1986-10--6'),
(9, 'Ha! Ha! Ha!', '1977-10-14'),
(10, 'Lament', '1984-04-06'),
(11, 'Voices & Images', '1988-03-04'),
(12, 'Methods of Silence', '1989-06-05'),
(13, 'Full Collapse', '2001-04-10'),
(14, 'War All The Time', '2003-09-16'),
(15, 'What It Is to Burn', '2002-03-12'),
(16, 'Falling into Place', '2001-10-09'),
(17, 'Only Change Is Permanent', '2024-03-08'),
(18, 'Truest Of Colours', '2009-01-01'),
(19, 'Non-existent album', '2019-01-01');


insert into album_artist (artist_id, album_id) 
values 
(1, 1),
(1, 2),
(2, 3),
(2, 4),
(3, 5),
(3, 6),
(4, 7),
(4, 8),
(5, 9),
(5, 10),
(6, 11),
(6, 12),
(7, 13),
(7, 14),
(8, 15),
(8, 16),
(9, 17),
(9, 18),
(9, 19);


insert into track (album_id, name, duration, id)
values 
(1, 'Is There Anybody There?', 238, 1),
(1, 'Holiday', 392, 2),
(1, 'Another Piece of Meat', 210, 3),
(2, 'When the Smoke Is Going Down', 230, 4),
(2, 'No One Like You', 237, 5),
(3, 'Master of Puppets', 516, 6),
(3, 'Damage, Inc.', 330, 7),
(4, 'Enter Sandman', 330, 8),
(4, 'The Unforgiven', 386, 9),
(5, 'In Between Days', 178, 10),
(5, 'Push', 271, 11),
(6, 'Lovesong', 208, 12),
(6, 'Disintegration', 498, 13),
(7, 'Take On Me', 228, 14),
(7, 'The Sun Always Shines On T.V.', 305, 15),
(7, 'Here I Stand and Face The Rain', 270, 16),
(8, 'Manhattan Skyline', 258, 17),
(8, 'Scoundrel Days', 236, 18),
(9, 'The Man Who Dies Every Day', 250, 19),
(9, 'Distant Smile', 321, 20),
(10, 'One Small Day', 270, 21),
(10, 'Dancing with Tears in My Eyes', 279, 22),
(11, 'The Great Commandment', 257, 23),
(11, 'Winner Takes Nothing', 356, 24),
(12, 'Love Is a Shield', 282, 25),
(12, 'Anyone', 225, 26),
(13, 'Understanding in a Car Crash', 264, 27),
(13, 'A Hole in the World', 207, 28),
(14, 'Signals Over the Air', 265, 29),
(14, 'Division St.', 254, 30),
(15, 'Letters to You', 200, 31),
(15, 'Ender', 808, 32),
(16, 'Waiting', 229, 33),
(16, 'Perfection Through Silence', 209, 34),
(17, 'Mess', 256, 35),
(17, 'Let It Burn', 206, 36),
(18, 'Worth It?', 207, 37),
(18, 'Commence', 94, 38),
(19, 'Non-existent Song 1', 180, 39),
(19, 'Non-existent Song 2', 180, 40);


insert into track_collection (name, release_date)
values
('Still Loving You', '1992-04-06'),
('Greatest Hits', '2001-11-07'),
('Headlines and Deadlines: The Hits of A-ha', '1991-11-04'),
('Kill the House Lights', '2007-10-30'),
('Die besten Hits der 80er', '2013-02-05'),
('Old School Emo', '2025-07-31'),
('Non-existent Compilation', '2019-01-01');


insert into collections (track_collection_id, track_id) 
values 
(1, 1),
(1, 2),
(2, 10),
(2, 12),
(3, 14),
(3, 15),
(3, 17),
(4, 27),
(4, 29),
(5, 14),
(5, 22),
(5, 23),
(5, 25),
(6, 27),
(6, 31),
(7, 31),
(7, 10),
(7, 3);




