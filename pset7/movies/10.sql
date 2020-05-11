SELECT DISTINCT name
FROM people JOIN directors ON people.id = directors.person_id
WHERE movie_id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0);