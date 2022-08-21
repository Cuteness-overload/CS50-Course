-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Initial report
SELECT * FROM crime_scene_reports WHERE street LIKE 'Humphrey Street' AND day = 28

-- Getting the interviews
SELECT * FROM interviews WHERE transcript LIKE '%bakery%' AND day = 28

-- Car Plates
SELECT * FROM bakery_security_logs WHERE hour = 10 AND minute BETWEEN 15 AND 30 AND day = 28

-- ATM
SELECT account_number,amount FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND month = 7 AND transaction_type = 'withdraw'

-- People and Bank accounts
SELECT * FROM people WHERE id IN(SELECT person_id FROM bank_accounts WHERE account_number IN(SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND day = 28 AND transaction_type = 'withdraw'))

-- Phone calls
SELECT caller,receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND caller IN('(829) 555-5269', '(389) 555-5198', '(367) 555-5533')
-- Seem to indicate Bruce stole the duck, only call that day between the three suspects
--

-- Finding the suspect
SELECT * FROM people WHERE phone_number IN(SELECT receiver FROM phone_calls WHERE day = 28 AND month = 7 AND year = 2021 AND caller = '(367) 555-5533')


SELECT flight_id FROM passengers WHERE passport_number = 5773159633
-- Getting Fiftyville Aiport ID
SELECT id FROM airports WHERE city LIKE 'Fiftyville'
-- getting flights on the 29th of July 2021
SELECT id,hour,minute FROM flights WHERE origin_airport_id = 8 AND day = 29 AND month = 7 AND year = 2021
-- earliest is ID 36
SELECT city FROM airports WHERE id IN(SELECT destination_airport_id FROM flights WHERE id = 36)