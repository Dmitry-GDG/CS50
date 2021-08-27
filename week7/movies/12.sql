-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.

SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Johnny Depp"))
INTERSECT
SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Helena Bonham Carter"));

-- SELECT title FROM movies WHERE id IN
-- (SELECT movie_id FROM stars JOIN people ON stars.person_id = people.id WHERE name = "Helena Bonham Carter"
-- AND movie_id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Johnny Depp")));
--
-- Select title from movies
-- join stars on stars.movie_id = movies.id
-- join people on people.id = stars.person_id
-- where people.name = "Helena Bonham Carter"
-- INTERSECT
-- Select title from movies
-- join stars on stars.movie_id = movies.id
-- join people on people.id = stars.person_id
-- where people.name = "Johnny Depp";

-- In Terminal
--      sqlite3 movies.db
--      .schema
--      SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Johnny Depp"))
--      INTERSECT
--      SELECT title FROM movies WHERE id IN (SELECT movie_id FROM stars WHERE person_id IN (SELECT id FROM people WHERE name = "Helena Bonham Carter"));
--
-- OR just
--      $ cat filename.sql | sqlite3 movies.db