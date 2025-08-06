select a.name from album a
join album_artist ala on ala.album_id = a.id
join artist ar on ar.id = ala.artist_id
join artist_genre ag on ag.artist_id = ar.id
join genre g on g.id = ag.genre_id
group by a.name
having count(distinct g.name) > 1;

select t.name from track t 
left join collections c on t.id = c.track_id 
where c.track_collection_id is null;

select a.name from artist a
join album_artist ala on ala.artist_id = a.id
join album al on al.id = ala.album_id
join track t on t.album_id = al.id
where t.duration = (select min(duration) from track) 
group by a.name;

select a.name from album a
join track t on t.album_id = a.id
group by a.name
having count(*) = 2;