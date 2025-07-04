SELECT * FROM crime_scene_reports
    WHERE street = 'Humphrey Street';


-- get witnesses interviews
SELECT year, month, day, name, transcript FROM interviews
WHERE transcript LIKE '%bakery%'
AND year = 2024 AND month = 7 AND day = 28;


-- check bakery logs from within 10 minutes of the theft
SELECT hour, minute, activity, license_plate FROM bakery_security_logs WHERE year = 2024
AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 25;

-- get atm transactions for that day and owner of account
SELECT name, phone_number, license_plate, passport_number, name FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
        (SELECT account_number FROM atm_transactions
        WHERE year = 2024 AND month = 7 AND day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));

-- check short phone call at around theft time
SELECT people.name, caller, receiver, duration FROM phone_calls
JOIN people ON people.phone_number = phone_calls.caller
WHERE year = 2024 AND month = 7 AND day = 28
AND duration < 65
ORDER BY duration ASC;

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

-- Bruce or Diana?! --

