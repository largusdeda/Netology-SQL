select name, duration from track 
where duration = (select max(duration) from track);

select name from track 
order by duration >= 210;

select name from track_collection 
where extract(year from release_date) between 2018 and 2020;

select name from artist 
where name not like '% %';

select name from track 
where upper(name) like '%MY%';

