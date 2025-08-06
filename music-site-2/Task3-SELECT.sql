select g.name, count(artist_id) from genre g 
join artist_genre on g.id = genre_id
group by g.name;

select a.name, count(t.id) from album a
join track t on a.id = t.album_id 
where extract(year from a.release_date) between 2019 and 2020 
group by a.name;

select a.name, avg(t.duration) av_d from album a 
join track t on t.album_id = a.id
group by a.name 
order by av_d;

select distinct a.name from artist a
join album_artist ala on ala.artist_id = a.id
join album al on al.id = ala.album_id
where extract(year from al.release_date) != 2020;

select tc.name from track_collection tc 
join collections c on c.track_collection_id = tc.id
join track t on t.id = c.track_id
join album a on t.album_id = a.id 
join album_artist ala on ala.album_id = a.id
join artist on artist.id = ala.artist_id 
where artist."name" = 'Thursday';




