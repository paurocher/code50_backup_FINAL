python
sorting dicts, collections.Counter, Counter().most_common

sql (structured query language)
CREATE TABLE table (column type, ...);

in the terminal: `sqlite favorites.db` creates our binary file database
```
mode .csv
.import favorites.csv favorites
.quit
```
This creates our database file.

Now we can open our table and do stuff with it:
```
sqlite3 favorites.db
.sqema  # will give us a structure of the db
SELECT * FROM favorites;  # selects everything from the table and prints it
SELECT language FROM favorites;  # this will only print all languages
SELECT language FROM favorites LIMIT 10;  # prints only the first 10 languages
```

Like LIMIT, there are many keywords to perform operations in SQL:
    - AVG
    - COUNT
    - DISTINCT
    - LOWER
    - MAX
    - MIN
    - UPPER
    - W`HERE
    - LIKE
    - ORDER BY
    - LIMIT
    - GROUP BY
    - ...

`SELECT COUNT(*) FROM favorites;` Prints the total rows.
`SELECT DISTINCT(language) favorites;` Prints all found languages.
`SELECT COUNT(DISTINCT(language)) FROM favorites;` Prints how many different languages there are.
`SELECT COUNT(DISTINCT(language)) FROM favorites ORDER BY COUNT(*) DESC;` Prints how many different languages there are in order.
`SELECT COUNT(*) FROM favorites WHERE language = 'C';` Prints how many times 'C' is found as a language.
`SELECT COUNT(*) FROM favorites WHERE language = 'C' AND problem = 'Hello, world';` Prints how many times 'C' is found as a language with the 'Hello, world'.
`SELECT language, COUNT(*) as var_name FROM favorites GROUP BY language ORDER BY n DESC` We can declare varaibles as well.
LIMIT 1 would return the greatest value if added to the last expamle.

`INSERT INTO table (column, ...) VALUES (value, ...);` To insert stuff into the database.
`INSERT INTO favorites (language, problem) VALUES ("SQL", "Fiftyville");`

`DELETE FROM favorites` Delete the whole db!!!!!!!!!!!!!!!!!
`DELETE FROM favorites WHERE timestamp IS NULL;` Will delete all rows where the timestamp is NULL

`UPDATE favorites SET language = 'SQL', problem = 'Fiftyville;' Updates all rows to language sql and problem Fiftyville.

SQL datatypes:
  - BLOB
  - INTEGER
  - REAL
  - NUMERIC
  - TEXT

Other keywords:
  - NOT NULL
  - UNIQUE


PRIMARY KEY is a unique id for an element in the table it is defined in
FOREIGN KEY is when a PRIMARY KEY is used in another table other than the one the element was defined in.
These 2 keys is the optimal way to link several tables together. Instead of using the name of the show (a string is very expensive), using numbers makes all operations work better.

`sqlite shows.db` load IMDB database
`SELECT * FROM ratings WHERE ratings >= 6.0 LIMIT 10;` show last 10 added
`SELECT * FROM ratings LIMIT 10`
`SELECT COUNT(*) FROM shows;`


`.schema shows` shows the design of the shows table
`.schema ratings`
schemas show us the PRIMARY KEY and FOREIGN KEY thus we can see how tables in the DB are related.
`schema` prints the schema of all tables in the data base.

Nested queries:
```
SELECT * FROM shows WHERE id IN (
    SELECT show_if FROM ratings WHERE rating <= 6.0 LIMIT 10);
```
will show a table with the show_id, title, year and episodes.


# cmbining tables (1h22, section: 1h06)
JOIN can be used to merge table so we can display values from several table in one go:
```
SELECT * FROM shows JOIN ratings ON shows.id = ratings.show_id WHERE rating <= 6.0 LIMIT 10;
```
We are telling to join to shows the show_id from the ratings table. I want the id column to line up with the show_id columns


# one-to-many relationships (1h30m)
a movie can have more than one genere.
```
SELECT show_id FROM generes WHERE genere = 'Comedy' LIMIT10;
```
Gets only the show IDs

```
SELECT title FROM shows WHERE id in (SELECT show_id FROM generes WHERE genere = 'Comedy' LIMIT 10);
```
Nested query that gets us the show title from the previous query.

`Select genere FROM generes WHERE show_id = 63881;`
`SELECT genere FROM generes WHERE show_id = (SELECT id from shows WHERE title = 'Catweazle');`


When joining data in a one-to-many relationship, some data is duplicated. For example here we have 3 time s the title of the movie, one for each genere it applies to. That is normal and it is fine.



# may-to-many relationship (1h35)
Like one show can have my characters in it, and one of these characters can appear in many different shows.
We are going to play with the 'people', 'stars' and 'shows' tables here.
`SELECT * FROM shows WHERE title 'The Office' AND year = 2005;`
`SELECT person_id FROM stars WHERE show_id = (SELECT id FROM shows WHERE title 'The Office' AND year = 2005);` THis gives us just a list of person IDs ... let's get their names:
```
SELECT name FROM people WHERE id IN(
  SELECT person_id FROM stars WHERE show_id = (
    SELECT is FROM shows WHERE tilte 'The Office' AND year = 2005)
  )
);
```

Get all shows where Steve Carell played in:
```
SELECT title FROM shows WHERE id IN (
  SELECT show_id FROM stars WHERE person_id = (
    SELECT id FROM people WHERE name = 'Steve Carell')
  )
);
```
We can get this list of movies where Steve Carell plays in by joining lists. It is a bit more complex though, and way more slow to get the result:
```
SELECT title FROM shows
  JOIN stars ON shows.id = stars.show_id
  JOIN people ON stars.person_id = people.id
  WHERE name = 'Steve Carell';
```
And there is a thirs way, also slower than the first solution:
```
SELECT title from show, stars, peple
  WHERE show.id = stars.show_id
  AND people.id = stars_person.id
  AND name = 'Steve Carel';
```


# timer
.timer ON


# indexes
it is a datastructure we can create to store things we want to have access to in the fastest way possible. As we have seen above, some queries take veriy long to resolve. This is a way to mitigate that.
`CREATE INDEX name ON table_name (columns, ...);`

`CREATE INDEX title_index ON shows (title);` Telling the database to index the title column because we want to make search there very fast, or we want to access it frequently.

THis creates what is called a B-tree (not a binary tree, something different). It is a short-fat tree, very fast to search through.

So, the slow example above that took almost 3 seconds, if we create indexes for some of the tables that are queries it will take 0.001 seconds>
```
CREATE INDEX person_index ON stars (person_id);
CREATE INDEX show_index ON stars (show_id);
CREATE nsertNDEX name_index ON people (name);

SELECT title FROM shows, stars, people
  WHERE shows.id = stars.show_id
  AND people.id = stars.person_id
  AND name = 'Steve Carell';
```


# python and sql
https://cs50.readthedocs.io/libraries/cs50/python/#cs50.SQL
Check the favorites.py file.

let's reset first the db:
```
sqlite favorites.db
mode .csv
.import favorites.csv favorites
.quit
```



# race conditions (2h05)
BEGIN TRANSCATION
COMMIT
ROLLBACK

Wrapping some lines of code between BEGIN TRANSACTION and COMMIT at the end avoids the problems when race conditions happen.

# SQL injection attack
Do not use formatted strings to pass SQL commands. Use the stings with the '?' character.




# Short video
we will work with a DB using these 2 tables:
users
idnum | username | password | fullname
10 | jerry | fuss!ll! | Jerrsy Seinfeld
11 | gcostanza | b0sc0 | George Costanza

moms
username | mother
jerry | Jelen Seinfeld
gcostanza | Estelle Costanza

### INSERT
`INSERT INTO table (columns(in csv)) VALUES (values (in csv));`
`INSERT INTO users (username,password,fullname) VALUES ("newman", "USMAIL", "Newman");`
this will result in a new row on users like so:
11 | newman | USMAIL | Newman
How come the idnum got populated automaitcally?!! Because we defined it as primary key, as integer and autoincrement

### SELECT
Used to get info back from the table through queries:
`SELECT <columns> FROM <table> WHERE <condition (named predicate in SQL)> ORDER BY <column>;`

`SELECT idnum, fullname FROM users;` will give us the 2 columns of the whole database.
`SELECT password FROM users WHERE idnum < 12;` restricts to users whose idnum is less than 12
`SELECT * FROM moms WHERE username = Jerry;` * returns the whole row

#### SELECT JOIN
`SELECT users.fullname, moms.mother FROM users JOIN moms ON users.usernmae = moms.username;`

### UPDATE
`UPDATE <table> SET <column = value> WHERE <predicate>;`
`UPDATE users SET password 'yadayada' WHERE idnum = 10;`


### DELETE
`DELETE FROM <table> WHERE <predicate>;`
`DELETE FROM users WHERE username = jerry;`
