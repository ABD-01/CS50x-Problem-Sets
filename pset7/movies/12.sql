Hi , I'm having problem with 9, 12, 13 .sql. Can anyone help..
This what I have done for 12.sql

SELECT title FROM movies
WHERE
(id IN (SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE name = "Johnny Depp") =
id IN (SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE name = "Helena Bonham Carter") );



people.name = "Helena Bonham Carter" AND people.name = "Johnny Depp"

