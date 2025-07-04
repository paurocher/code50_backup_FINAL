-- Keep a log of any SQL queries you execute as you solve the mystery.


-- get schema
--.schema
--CREATE TABLE crime_scene_reports (
--    id INTEGER,
--    year INTEGER,
--    month INTEGER,
--    day INTEGER,
--    street TEXT,
--    description TEXT,
--    PRIMARY KEY(id)
--);
--CREATE TABLE interviews (
--    id INTEGER,
--    name TEXT,
--    year INTEGER,
--    month INTEGER,
--    day INTEGER,
--    transcript TEXT,
--    PRIMARY KEY(id)
--);
--CREATE TABLE atm_transactions (
--    id INTEGER,
--    account_number INTEGER,
--    year INTEGER,
--    month INTEGER,
--    day INTEGER,
--    atm_location TEXT,
--    transaction_type TEXT,
--    amount INTEGER,
--    PRIMARY KEY(id)
--);
--CREATE TABLE bank_accounts (
--    account_number INTEGER,
--    person_id INTEGER,
--    creation_year INTEGER,
--    FOREIGN KEY(person_id) REFERENCES people(id)
--);
--CREATE TABLE airports (
--    id INTEGER,
--    abbreviation TEXT,
--    full_name TEXT,
--    city TEXT,
--    PRIMARY KEY(id)
--);
--CREATE TABLE flights (
--    id INTEGER,
--    origin_airport_id INTEGER,
--    destination_airport_id INTEGER,
--    year INTEGER,
--    month INTEGER,
--    day INTEGER,
--    hour INTEGER,
--    minute INTEGER,
--    PRIMARY KEY(id),
--    FOREIGN KEY(origin_airport_id) REFERENCES airports(id),
--    FOREIGN KEY(destination_airport_id) REFERENCES airports(id)
--);
--CREATE TABLE passengers (
--    flight_id INTEGER,
--    passport_number INTEGER,
--    seat TEXT,
--    FOREIGN KEY(flight_id) REFERENCES flights(id)
--);
--CREATE TABLE phone_calls (
--    id INTEGER,
--    caller TEXT,
--    receiver TEXT,
--    year INTEGER,
--    month INTEGER,
--    day INTEGER,
--    duration INTEGER,
--    PRIMARY KEY(id)
--);
--CREATE TABLE people (
--    id INTEGER,
--    name TEXT,
--    phone_number TEXT,
--    passport_number INTEGER,
--    license_plate TEXT,
--    PRIMARY KEY(id)
--);
--CREATE TABLE bakery_security_logs (
--    id INTEGER,
--    year INTEGER,
--    month INTEGER,
--    day INTEGER,
--    hour INTEGER,
--    minute INTEGER,
--    activity TEXT,
--    license_plate TEXT,
--    PRIMARY KEY(id)
--);


-- get crime report
SELECT * FROM crime_scene_reports WHERE year = 2024 AND month = 7 AND day = 28 AND street = 'Humphrey Street';

-- happened in the bakery at 10:15am
-- 3 witnesses interviewed: WHO?

-----------------------------------------------------

-- get witnesses interviews
SELECT year, month, day, name, transcript FROM interviews
WHERE transcript LIKE '%bakery%'
AND year = 2024 AND month = 7 AND day = 28;

--Sometime within ten minutes of the theft, I saw the --thief get into a car in the bakery parking lot and --drive away. Check security footage
--
--Thief withdrawing money at ATM in the am on Legett Street. Eugene --recognized the thief.
--
--Phonecall for less than a minute. Planning to leave --Fifyville with first flight next day in the am. --Ordered to buy plane tickets right away.


-----------------------------------------------------


-- check bakery logs from within 10 minutes of the theft
SELECT hour, minute, activity, license_plate FROM bakery_security_logs WHERE year = 2024
AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25;
--+------+--------+----------+---------------+
--| hour | minute | activity | license_plate |
--+------+--------+----------+---------------+
--| 10   | 16     | exit     | 5P2BI95       |
--| 10   | 18     | exit     | 94KL13X       |
--| 10   | 18     | exit     | 6P58WS2       |
--| 10   | 19     | exit     | 4328GD8       |
--| 10   | 20     | exit     | G412CB7       |
--| 10   | 21     | exit     | L93JTIZ       |
--| 10   | 23     | exit     | 322W7JE       |
--| 10   | 23     | exit     | 0NTHK55       |
--| 10   | 35     | exit     | 1106N58       |
--+------+--------+----------+---------------+


-- get atm transactions for that day and owner of account
SELECT name, phone_number, license_plate, passport_number, name FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions
        WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
--+---------+----------------+---------------+-----------------+---------+
--|  name   |  phone_number  | license_plate | passport_number |  name   |
--+---------+----------------+---------------+-----------------+---------+
--| Kenny   | (826) 555-1652 | 30G67EN       | 9878712108      | Kenny   |
--| Iman    | (829) 555-5269 | L93JTIZ       | 7049073643      | Iman    |
--| Benista | (338) 555-6650 | 8X428L0       | 9586786673      | Benista |
--| Taylor  | (286) 555-6063 | 1106N58       | 1988161715      | Taylor  |
--| Brooke  | (122) 555-4581 | QX4YZN3       | 4408372428      | Brooke  |
--| Luca    | (389) 555-5198 | 4328GD8       | 8496433585      | Luca    |
--| Diana   | (770) 555-1861 | 322W7JE       | 3592750733      | Diana   |
--| Bruce   | (367) 555-5533 | 94KL13X       | 5773159633      | Bruce   |
--+---------+----------------+---------------+-----------------+---------+



-- check short phone call at around theft time
SELECT people.name, caller, receiver, duration FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = 2024 AND month = 7 AND day = 28
AND duration < 65
ORDER BY duration ASC;
--+---------+----------------+----------------+----------+
--|  name   |     caller     |    receiver    | duration |
--+---------+----------------+----------------+----------+
--| Kelsey  | (499) 555-9472 | (892) 555-8872 | 36       |
--| Carina  | (031) 555-6622 | (910) 555-3251 | 38       |
--| Taylor  | (286) 555-6063 | (676) 555-6554 | 43       |
--| Bruce   | (367) 555-5533 | (375) 555-8161 | 45       |
--| Diana   | (770) 555-1861 | (725) 555-3243 | 49       |
--| Kelsey  | (499) 555-9472 | (717) 555-1342 | 50       |
--| Sofia   | (130) 555-0289 | (996) 555-8899 | 51       |
--| Benista | (338) 555-6650 | (704) 555-2131 | 54       |
--| Kenny   | (826) 555-1652 | (066) 555-9701 | 55       |
--| Kathryn | (609) 555-5876 | (389) 555-5198 | 60       |
--| Peter   | (751) 555-6567 | (594) 555-6254 | 61       |
--+---------+----------------+----------------+----------+



-----------------------------------------------------
(
--IRRELEVANT?
-- check people phone number and lic plates
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE license_plate IN ('L93JTIZ', '322W7JE', '0NTHK55', '1106N58');

--+--------+----------------+-----------------+---------------+
--|  name  |  phone_number  | passport_number | license_plate |
--+--------+----------------+-----------------+---------------+
--| Iman   | (829) 555-5269 | 7049073643      | L93JTIZ       |
--| Taylor | (286) 555-6063 | 1988161715      | 1106N58       |
--| Diana  | (770) 555-1861 | 3592750733      | 322W7JE       |
--| Kelsey | (499) 555-9472 | 8294398571      | 0NTHK55       |
--+--------+----------------+-----------------+---------------+
)

-----------------------------------------------------


-- check flight departure times from Fiftyville
SELECT * FROM flights WHERE origin_airport_id IN (
    SELECT id from airports WHERE city = 'Fiftyville'
    )
AND year = 2024 AND month = 7 AND day = 29
ORDER BY hour, minute;

-- get just the flight ids:
SELECT id FROM flights WHERE origin_airport_id IN (
    SELECT id from airports WHERE city = 'Fiftyville'
    )
AND year = 2024 AND month = 7 AND day = 29
ORDER BY hour, minute;



-- get list of passagers for each flight departing Fiftyville
SELECT passengers.passport_number, people.name FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
 WHERE flight_id IN (SELECT id FROM flights WHERE origin_airport_id IN (
    SELECT id from airports WHERE city = 'Fiftyville'
    )
AND year = 2024 AND month = 7 AND day = 29
ORDER BY hour, minute);




-- relate all relevant info to find the 2 persons
-- I want to expose name, passport number, phone number, lic plate
-- I want to filter by bakery time, atm, phone call
SELECT p.name, p.phone_number, p.license_plate, p.passport_number
FROM bakery_security_logs bak
JOIN people p ON p.license_plate = bak.license_plate
JOIN bank_accounts bank ON bank.person_id = p.id
JOIN atm_transactions atm ON atm.account_number = bank.account_number
JOIN phone_calls phone ON phone.caller = p.phone_number
WHERE bak.year = 2024 AND bak.month = 7 AND bak.day = 28 AND bak.hour = 10 AND bak.minute > 15 AND minute < 25
AND atm.atm_location = 'Leggett Street' AND atm.year = 2024 AND atm.month = 7 AND atm.day = 28 AND atm.transaction_type = 'withdraw'
AND phone.year = 2024 AND phone.month = 7 AND phone.day = 28 AND phone.duration < 60;
--+--------+----------------+---------------+-----------------+
--|  name  |  phone_number  | license_plate | passport_number |
--+--------+----------------+---------------+-----------------+
--| Diana  | (770) 555-1861 | 322W7JE       | 3592750733      |
--| Taylor | (286) 555-6063 | 1106N58       | 1988161715      |
--+--------+----------------+---------------+-----------------+


-- relate the 2 found persons to flight before 10am to figure out thieaf and destination city
SELECT passengers.flight_id, flights.destination_airport_id, airports.city, pl.name FROM passengers
JOIN flights ON flights.id = passengers.flight_id
JOIN people pl ON passengers.passport_number = pl.passport_number
JOIN airports ON airports.id = flights.destination_airport_id
WHERE passengers.passport_number IN
(SELECT p.passport_number
FROM bakery_security_logs bak
JOIN people p ON p.license_plate = bak.license_plate
JOIN bank_accounts bank ON bank.person_id = p.id
JOIN atm_transactions atm ON atm.account_number = bank.account_number
JOIN phone_calls phone ON phone.caller = p.phone_number
WHERE bak.year = 2024 AND bak.month = 7 AND bak.day = 28 AND bak.hour = 10 AND bak.minute > 15 AND minute < 25
AND atm.atm_location = 'Leggett Street' AND atm.year = 2024 AND atm.month = 7 AND atm.day = 28 AND atm.transaction_type = 'withdraw'
AND phone.year = 2024 AND phone.month = 7 AND phone.day = 28 AND phone.duration < 60
AND flights.year = 2024 AND flights.month = 7 AND flights.day = 29 AND flights.hour < 10)
;


-- We know it's Bruce!! Now let's look into the phonecalls and find out who Bruce tlaked to on the phone --
SELECT receiver.name AS receiver
FROM phone_calls pc
JOIN people caller ON pc.caller = caller.phone_number
JOIN people receiver ON pc.receiver = receiver.phone_number
WHERE caller.name = 'Bruce' AND pc.year = 2024 AND pc.month = 7 AND pc.day = 28 AND pc.duration < 60
;

-- Robin!! --
