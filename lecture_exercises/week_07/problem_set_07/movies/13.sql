SELECT people.name FROM people WHERE id IN(
    SELECT stars.person_id FROM stars
    JOIN movies ON movies.id = stars.movie_id
    WHERE movies.id IN (
        SELECT movies.id FROM movies
        JOIN people ON people.id = stars.person_id
        JOIN stars ON movies.id = stars.movie_id
        WHERE people.name = 'Kevin Bacon'
    )
)
AND people.name != 'Kevin Bacon';
