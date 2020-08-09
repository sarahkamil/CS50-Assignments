--- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
--- Your query should output a table with a single column for the title of each movie.
--- You may assume that there is only one person in the database with the name Johnny Depp.
--- You may assume that there is only one person in the database with the name Helena Bonham Carter.

SELECT movies.title
FROM
    stars
    JOIN people ON stars.person_id = people.id
    JOIN movies ON stars.movie_id = movies.id
WHERE
    people.name = "Johnny Depp" OR
    people.name = "Helena Bonham Carter"
GROUP BY
    stars.movie_id
HAVING
    count(stars.movie_id) > 1

