-- Keep a log of any SQL queries you execute as you solve the mystery.
------
-- the theft took place on July 28, 2020 and that it took place on Chamberlin Street.
-- took description about crime
SELECT description FROM crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";
-- description
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse.
-- Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.
----
-- check interviews at the date
SELECT name, transcript FROM interviews WHERE year = 2020 AND month = 7 AND day = 28;
-- name | transcript
-- Jose | “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- Eugene | “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- Barbara | “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
--* Ruth | Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
--** Eugene | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
--*** Raymond | As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
----
--* Check courthouse_security_logs from the date
SELECT hour, minute, license_plate, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 9 AND minute >= 00;
SELECT hour, minute, license_plate, activity FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 00;
-- minute | license_plate | activity
-- 9 | 14 | 4328GD8 | entrance
-- 9 | 15 | 5P2BI95 | entrance
-- 9 | 20 | 6P58WS2 | entrance
-- 9 | 28 | G412CB7 | entrance
--10 |  8 | R3G7486 | entrance
--10 | 14 | 13FNH73 | entrance
--10 | 16 | 5P2BI95 | exit
--10 | 18 | 94KL13X | exit
--10 | 18 | 6P58WS2 | exit
--10 | 19 | 4328GD8 | exit
--10 | 20 | G412CB7 | exit
--10 | 21 | L93JTIZ | exit
--10 | 23 | 322W7JE | exit
--10 | 23 | 0NTHK55 | exit
--10 | 35 | 1106N58 | exit
--10 | 42 | NRYN856 | entrance
--10 | 44 | WD5M8I6 | entrance
--10 | 55 | V47T75I | entrance
----
--* Check courthouse_security_logs from the date & time & exit => license_plate  => suspects
SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit";
-- license_plate
-- 5P2BI95
-- 94KL13X
-- 6P58WS2
-- 4328GD8
-- G412CB7
-- L93JTIZ
-- 322W7JE
-- 0NTHK55
-- 1106N58
----
--* Check courthouse_security_logs from the date & time & exit => license_plate  => suspects
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND activity = "exit");
-- name
-- Patrick
-- Amber
-- Elizabeth
-- Roger
-- Madison
-- Danielle
-- Russell
-- Evelyn
-- Ernest
----
--** Check atm_transactions that morning
SELECT account_number, transaction_type FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";
-- account_number | transaction_type
-- 28500762 | withdraw
-- 28296815 | withdraw
-- 76054385 | withdraw
-- 49610011 | withdraw
-- 16153065 | withdraw
-- 86363979 | deposit
-- 25506511 | withdraw
-- 81061156 | withdraw
-- 26013199 | withdraw
----
--** Chek bank_accounts (corresponding withdrow from ATM that morning) => suspects
SELECT name, phone_number, passport_number, license_plate FROM people
WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"));
-- name | phone_number | passport_number | license_plate
-- Bobby | (826) 555-1652 | 9878712108 | 30G67EN
-- Elizabeth | (829) 555-5269 | 7049073643 | L93JTIZ
-- Victoria | (338) 555-6650 | 9586786673 | 8X428L0
-- Madison | (286) 555-6063 | 1988161715 | 1106N58
-- Roy | (122) 555-4581 | 4408372428 | QX4YZN3
-- Danielle | (389) 555-5198 | 8496433585 | 4328GD8
-- Russell | (770) 555-1861 | 3592750733 | 322W7JE
-- Ernest | (367) 555-5533 | 5773159633 | 94KL13X
----
--*** Check phone calls
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28;
-- caller | receiver | duration
-- (336) 555-0077 | (098) 555-1164 | 318
-- (918) 555-5327 | (060) 555-2489 | 146
-- (491) 555-2505 | (478) 555-1565 | 241
-- (996) 555-8899 | (059) 555-4698 | 142
-- (704) 555-5790 | (772) 555-5770 | 200
-- (984) 555-5921 | (618) 555-9856 | 546
-- (579) 555-5030 | (971) 555-6468 | 421
-- (233) 555-0473 | (831) 555-0973 | 113
-- (293) 555-1469 | (749) 555-4874 | 195
-- (450) 555-8297 | (771) 555-7880 | 298
-- (130) 555-0289 | (996) 555-8899 | 51
-- (209) 555-7806 | (693) 555-7986 | 487
-- (918) 555-2946 | (006) 555-0505 | 359
-- (499) 555-9472 | (892) 555-8872 | 36
-- (669) 555-6918 | (914) 555-5994 | 233
-- (547) 555-8781 | (398) 555-1013 | 272
-- (544) 555-8087 | (389) 555-5198 | 595
-- (666) 555-5774 | (125) 555-8030 | 326
-- (047) 555-0577 | (059) 555-4698 | 379
-- (301) 555-4174 | (711) 555-3007 | 583
-- (801) 555-9266 | (984) 555-5921 | 148
-- (971) 555-6468 | (267) 555-2761 | 149
-- (367) 555-5533 | (375) 555-8161 | 45
-- (609) 555-5876 | (389) 555-5198 | 60
-- (357) 555-0246 | (502) 555-6712 | 305
-- (367) 555-5533 | (344) 555-9601 | 120
-- (394) 555-3247 | (035) 555-2997 | 111
-- (839) 555-1757 | (487) 555-5865 | 278
-- (770) 555-1196 | (324) 555-0416 | 527
-- (636) 555-4198 | (670) 555-8598 | 69
-- (068) 555-0183 | (770) 555-1861 | 371
-- (711) 555-3007 | (113) 555-7544 | 157
-- (060) 555-2489 | (204) 555-4136 | 510
-- (704) 555-2131 | (891) 555-5672 | 103
-- (367) 555-5533 | (022) 555-4052 | 241
-- (873) 555-3868 | (047) 555-0577 | 109
-- (867) 555-9103 | (068) 555-0183 | 116
-- (608) 555-9302 | (725) 555-3243 | 280
-- (901) 555-8732 | (491) 555-2505 | 451
-- (478) 555-1565 | (717) 555-1342 | 573
-- (499) 555-9472 | (717) 555-1342 | 50
-- (695) 555-0348 | (338) 555-6650 | 383
-- (696) 555-9195 | (258) 555-5627 | 525
-- (286) 555-6063 | (676) 555-6554 | 43
-- (770) 555-1861 | (725) 555-3243 | 49
-- (711) 555-3007 | (147) 555-6818 | 358
-- (725) 555-4692 | (821) 555-5262 | 456
-- (324) 555-0416 | (452) 555-8550 | 328
-- (234) 555-1294 | (772) 555-5770 | 573
-- (669) 555-6918 | (971) 555-6468 | 67
-- (031) 555-6622 | (910) 555-3251 | 38
-- (342) 555-9260 | (219) 555-0139 | 404
-- (342) 555-9260 | (487) 555-5865 | 560
-- (801) 555-9266 | (608) 555-9302 | 425
-- (398) 555-1013 | (329) 555-5870 | 237
-- (016) 555-9166 | (336) 555-0077 | 88
-- (594) 555-2863 | (491) 555-2505 | 361
-- (122) 555-4581 | (831) 555-0973 | 491
-- (914) 555-5994 | (973) 555-3809 | 320
-- (258) 555-5627 | (695) 555-0348 | 368
-- (751) 555-6567 | (594) 555-6254 | 61
-- (771) 555-7880 | (711) 555-3007 | 288
-- (219) 555-0139 | (867) 555-9103 | 514
-- (676) 555-6554 | (328) 555-9658 | 153
-- (749) 555-4874 | (492) 555-5484 | 575
-- (328) 555-9658 | (775) 555-7584 | 579
-- (219) 555-0139 | (910) 555-3251 | 121
-- (380) 555-4380 | (680) 555-4935 | 550
-- (826) 555-1652 | (066) 555-9701 | 55
-- (594) 555-6254 | (123) 555-5144 | 346
-- (338) 555-6650 | (704) 555-2131 | 54
-- (971) 555-6468 | (258) 555-5627 | 441
-- (730) 555-5115 | (343) 555-0167 | 101
-- (286) 555-6063 | (310) 555-8568 | 235
-- (367) 555-5533 | (704) 555-5790 | 75
-- (041) 555-4011 | (609) 555-5876 | 565
-- (478) 555-1565 | (031) 555-6622 | 398
----
--*** Check phone calls => suspects
SELECT name from people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28);
-- big list --
----
--*** Check airports => suspects
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND hour < 12 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")));
-- big list --
----
--==========================================
--***** The THIEF is:     ==INTERSECT (time up to 10:30)==
SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND hour < 12 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")))
INTERSECT
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 30 AND activity = "exit")
INTERSECT
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
INTERSECT
SELECT name from people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28);
-- name
-- Ernest
--==========================================
-- The thief ESCAPED TO:
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights
WHERE year = 2020 AND month = 7 AND day = 29 AND hour < 12 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")
AND id = (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name = "Ernest")));
-- city
-- London
----
SELECT city FROM airports WHERE id = (SELECT destination_airport_id FROM flights
WHERE year = 2020 AND month = 7 AND day = 29 AND hour < 12 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")
AND id = (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people
WHERE name = (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND hour < 12 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")))
INTERSECT
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 30 AND activity = "exit")
INTERSECT
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
INTERSECT
SELECT name from people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28)))));
-- city
-- London
--==========================================
-- The ACCOMPLICE is:
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND caller = (SELECT phone_number FROM people WHERE name = "Ernest"));
-- name
-- Berthold
----
SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28 AND duration < 60
AND caller = (SELECT phone_number FROM people WHERE name = (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers
WHERE flight_id IN (SELECT id FROM flights WHERE year = 2020 AND month = 7 AND day = 29 AND hour < 12 AND origin_airport_id IN (SELECT id FROM airports WHERE city = "Fiftyville")))
INTERSECT
SELECT name FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 30 AND activity = "exit")
INTERSECT
SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts
WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street" AND transaction_type = "withdraw"))
INTERSECT
SELECT name from people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28))));
-- name
-- Berthold
----