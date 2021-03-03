DROP TABLE IF EXISTS temp;

CREATE TABLE temp (
    rank INT,
    name VARCHAR(255),
    platform VARCHAR(255),
    year INT,
    genre VARCHAR(255),
    publisher VARCHAR(255),
    na_sales REAL,
    eu_sales REAL,
    jp_sales REAL,
    other_sales REAL,
    global_sales REAL
);

-- Copy rows from psql CLI utility: 
-- \copy temp FROM '/home/etienne/Cours/bds/ProjetBDDspe/vgsales.csv' WITH (FORMAT CSV) 
-- Or (if posgresql has access permissions) the following PostgreSQL expression: 
--COPY temp FROM '/home/etienne/Cours/bds/ProjetBDDspe/vgsales.csv' DELIMITER ',' CSV HEADER;
-- Delete incomplete rows
DELETE FROM
    temp
WHERE
    name IS NULL
    OR platform IS NULL
    or year IS NULL
    or publisher IS NULL
    or genre IS NULL;

-- Remove duplicates
WITH -- Find duplicates
dup1 AS (
    SELECT
        name,
        platform,
        "year",
        genre,
        publisher,
        COUNT(*)
    FROM
        temp
    GROUP BY
        name,
        platform,
        year,
        genre,
        publisher
    HAVING
        COUNT(*) > 1
),
-- rank duplicates
dup2 AS (
    SELECT
        temp.rank,
        row_number() OVER(
            PARTITION BY temp.name,
            temp.platform,
            temp.year,
            temp.genre,
            temp.publisher
            ORDER BY
                temp.rank ASC
        ) AS rk
    FROM
        dup1
        JOIN temp ON dup1.name = temp.name
        AND dup1.platform = temp.platform
        AND dup1.genre = temp.genre
        AND dup1.publisher = temp.publisher
) -- delete duplicates of rank > 1 (only keep first occurrence)
DELETE FROM
    temp
WHERE
    rank IN (
        SELECT
            rank
        FROM
            dup2
        WHERE
            rk > 1
    );

-- Populate publishers
INSERT INTO
    publishers(name)
SELECT
    DISTINCT publisher
from
    temp ON CONFLICT DO NOTHING;

-- Populate platforms
INSERT INTO
    platforms(name)
SELECT
    DISTINCT platform
from
    temp ON CONFLICT DO NOTHING;

-- Populate genres
INSERT INTO
    genres(name)
SELECT
    DISTINCT genre
from
    temp ON CONFLICT DO NOTHING;

-- Populate games
WITH t AS (
    SELECT
        DISTINCT temp.name AS name,
        temp.year AS year,
        platforms.id AS platform_id,
        genres.id AS genre_id,
        publishers.id AS publisher_id
    FROM
        temp
        LEFT OUTER JOIN publishers ON publishers.name = publisher
        LEFT OUTER JOIN genres ON genres.name = genre
        LEFT OUTER JOIN platforms ON platforms.name = platform
)
INSERT INTO
    games(name, year, platform_id, genre_id, publisher_id)
SELECT
    *
FROM
    t;

-- Populate sales
WITH t AS (
    SELECT
        temp.rank AS rank,
        games.id AS game_id,
        temp.na_sales AS na_sales,
        temp.eu_sales AS eu_sales,
        temp.jp_sales AS jp_sales,
        temp.other_sales AS other_sales,
        temp.global_sales AS global_sales
    FROM
        temp
        LEFT OUTER JOIN publishers ON publishers.name = publisher
        LEFT OUTER JOIN genres ON genres.name = genre
        LEFT OUTER JOIN platforms ON platforms.name = platform
        LEFT OUTER JOIN games ON games.platform_id = platforms.id
        AND games.genre_id = genres.id
        AND games.publisher_id = publishers.id
        AND games.name = temp.name
        AND games.year = temp.year
)
INSERT INTO
    sales(
        rank,
        game_id,
        na_sales,
        eu_sales,
        jp_sales,
        other_sales,
        global_sales
    )
SELECT
    *
FROM
    t;