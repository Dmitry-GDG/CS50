-- In 2.sql, write a SQL query to determine the birth year of Emma Stone.
-- Your query should output a table with a single column and a single row (not including the header) containing Emma Stone’s birth year.
-- You may assume that there is only one person in the database with the name Emma Stone.

SELECT birth FROM people WHERE name = "Emma Stone";

-- In Terminal
--      sqlite3 movies.db
--      .schema
--      SELECT birth FROM people WHERE name = "Emma Stone";
--
-- OR just
--      $ cat filename.sql | sqlite3 movies.db