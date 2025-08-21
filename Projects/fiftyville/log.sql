-- Keep a log of any SQL queries you execute as you solve the mystery.


-- Let's start by checking for any crime scene reports that happened on Humphrey Street
SELECT * FROM crime_scene_reports WHERE street = "Humphrey Street";


-- We learn from the crime scene reports that there were 3 witnesses to the crime
-- Next lets take a look at the interviews of the witnesses of the crime
SELECT * FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;


-- We get 4 pieces of valuable info.
-- One: that the thief left in a car from Emma's bakery 10 minute after the crime.
-- Two: that they had taken money out from the ATM on Leggett Street the morning of the robbery.
-- Three: that they called their accomplice as they were leaving the bakery and spoke for less than a minute.
-- Four: They planned to take the earliest flight out of Fiftyville the next day. The accomplice bought the tickets.


-- Let's first follow the lead of the car in Emma's Bakery.
SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26;
-- We get 8 licence plates:
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55


-- Next let's check the ATM records
SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
-- We get 8 account numbers:
-- 28500762
-- 28296815
-- 76054385
-- 49610011
-- 16153065
-- 25506511
-- 81061156
-- 26013199


-- Next we can match these account numbers to bank records to get a list of suspects.
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"));
-- We get a list of suspects:
-- Kenny
-- Iman
-- Benista
-- Taylor
-- Brooke
-- Luca
-- Diana
-- Bruce


-- Now we can cross reference these names with the cars that left the bakery to narrow our list.
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
AND
license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute > 15 AND minute < 26);
-- Our supsect list is narrowed down to:
-- Iman
-- Luca
-- Diana
-- Bruce


-- Next let's check on the phone call made to the accomplice.
SELECT * FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61;
-- We get 10 phone numbers which we can match against out current list of suspects.
SELECT name FROM people WHERE name IN ("Iman","Luca","Diana","Bruce")
AND
phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61);
-- We've narrowed our list to 2 names:
-- Diana
-- Bruce


-- Next we can follow the lead on the flight to see if either of our suspects were on board.
SELECT * FROM flights WHERE year = 2021 AND month = 7 AND day = 29 AND origin_airport_id = (SELECT id FROM airports WHERE city = "Fiftyville")
ORDER BY hour;
-- We see the earliest flight out of Fiftyville left at 8:20AM
-- Lets check the passengers of this flight
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = (SELECT id FROM flights WHERE id = 36));
-- Of our list of suspects only Bruce was on the flight.
-- Bruce is our theif!


-- We can now find who the accomplice is as well
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 61 AND caller = (SELECT phone_number FROM people WHERE name = "Bruce"));
-- Our accomplice is Robin!

-- Finally we must determine where they fled to
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = 36);
--They fled to New York City!



