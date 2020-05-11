SELECT DISTINCT name
FROM people JOIN stars ON people.id = stars.person_id
WHERE stars.movie_id IN (SELECT id FROM movies WHERE year = 2004)
ORDER BY people.birth;


