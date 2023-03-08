-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Reading descriptions and get year
SELECT year, description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Reading interviews and get names
SELECT name, transcript FROM interviews WHERE month = 7 AND day = 28 AND transcript LIKE "%courthouse%";

-- Looking for cars that left the parking
SELECT hour, minute, activity, license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25;

-- Checking phone calls numbers and names
SELECT caller, receiver FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2020 AND duration < 60 AND caller = "(367) 555-5533";

-- Checking each persons name, passport based on cars left park and ATM withdraws earlier that morning and phone calls as well
SELECT name, passport_number, phone_number FROM people JOIN bank_accounts ON people.id = person_id WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND year = 2020 AND transaction_type = "withdraw") AND license_plate IN(SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2020 AND duration < 60);

-- Checking name in earliest flights departed from Fiftyville one day after
SELECT name FROM people JOIN passengers ON people.passport_number = passengers.passport_number WHERE passengers.passport_number IN(SELECT passport_number FROM people JOIN bank_accounts ON people.id = person_id WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = "Fifer Street" AND month = 7 AND day = 28 AND year = 2020 AND transaction_type = "withdraw") AND license_plate IN(SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25) AND phone_number IN(SELECT caller FROM phone_calls WHERE month = 7 AND day = 28 AND year = 2020 AND duration < 60)) AND flight_id IN(SELECT flights.id FROM flights JOIN airports ON origin_airport_id = airports.id WHERE month = 7 AND day = 29 AND year = 2020 AND city = "Fiftyville" ORDER BY hour, minute LIMIT 1);

-- Flight Destination
SELECT city FROM airports WHERE id IN(SELECT destination_airport_id FROM flights JOIN airports ON origin_airport_id = airports.id WHERE month = 7 AND day = 29 AND year = 2020 AND city = "Fiftyville" ORDER BY hour, minute LIMIT 1);

-- Checking ACCOMPLICE
SELECT name FROM people JOIN phone_calls ON phone_number = receiver WHERE month = 7 AND day = 28 AND year = 2020 AND duration < 60 AND caller IN(SELECT phone_number FROM people WHERE name = "Ernest");