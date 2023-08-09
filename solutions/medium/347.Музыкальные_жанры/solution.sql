WITH RECURSIVE temp1 (track_id, genre_id, track_name, genere_name, parent_genre_id) as (

    SELECT track.id AS track_id, track_genre.genre_id, track.name As track_name, genre.name As genere_name, genre.parent_genre_id
    FROM track
             INNER JOIN track_genre
                        ON track.id = track_genre.track_id
             INNER JOIN genre
                        ON genre.id = track_genre.genre_id

    UNION
    select temp1.track_id, t2.genre_id, temp1.track_name, t2.genere_name, t2.parent_genre_id
    from
        (SELECT genre.id As genre_id, genre.name as genere_name, genre.parent_genre_id FROM genre) t2 inner join temp1 on (temp1.parent_genre_id = t2.genre_id))

select temp1.track_id, temp1.genre_id, temp1.track_name, temp1.genere_name from temp1 ORDER BY track_id ASC, genre_id ASC