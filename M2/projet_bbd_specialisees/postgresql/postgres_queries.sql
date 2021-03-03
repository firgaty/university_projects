--  Les jeux publiés par Nintendo qui sont dans le top 100 (plan)
-- 5.804 ms -> 21 ms
SELECT
    sales.rank AS rank,
    games.name AS name,
    publishers.name AS publisher
FROM
    games
    JOIN sales ON sales.game_id = games.id
    RIGHT JOIN publishers ON games.publisher_id = publishers.id
WHERE
    publishers.name = 'Nintendo'
    AND sales.rank <= 100
ORDER BY
    sales.rank;

-- Les studios qui ont conçus des jeux sur PS3 dont le pourcentage de vente a été supérieur à 20%
-- 6.4 ms -> 19 ms
SELECT
    publishers.name AS publisher
FROM
    sales
    JOIN games ON sales.game_id = games.id
    JOIN publishers ON games.publisher_id = publishers.id
    JOIN platforms ON games.platform_id = platforms.id
WHERE
    platforms.name = 'PS3'
    AND sales.global_sales >= 20;

--  Les jeux conçu après 2000 par le studio qui a fait the Elder scrolls
-- 4 ms -> 10 ms
WITH t AS (
    SELECT
        DISTINCT publishers.name AS name
    FROM
        publishers
        RIGHT JOIN games ON games.publisher_id = publishers.id
    WHERE
        games.name = 'The Elder Scrolls V: Skyrim'
    LIMIT
        1
)
SELECT
    DISTINCT games.name
FROM
    games
    JOIN publishers ON games.publisher_id = publishers.id
    JOIN t ON t.name = publishers.name
WHERE
    games.year > 2000;

-- Les consoles sur lequel les studios qui ont produits super mario bros ont fait des jeux?
-- 5.6 ms -> 14.14 ms
WITH t AS (
    SELECT
        DISTINCT publishers.id AS id,
        publishers.name AS name
    FROM
        publishers
        RIGHT JOIN games ON games.publisher_id = publishers.id
    WHERE
        games.name = 'Super Mario Bros.'
    LIMIT
        1
)
SELECT
    DISTINCT platforms.name
FROM
    games
    JOIN t ON t.id = games.publisher_id
    JOIN platforms ON games.platform_id = platforms.id;

-- La moyenne des pourcentages de ventes fait par Capcom
-- 5 ms -> 7 ms
SELECT
    avg(sales.global_sales)
FROM
    sales
    JOIN games ON games.id = sales.game_id
    JOIN publishers ON publishers.id = games.publisher_id
WHERE
    publishers.name = 'Capcom';

-- La moyenne de pourcentages de vente des jeux qui contiennent Grand Theft Auto dans le titre (plan)
-- 1.8 ms -> 2.7 ms
SELECT
    avg(sales.global_sales) AS "avg"
FROM
    sales
    JOIN games ON games.id = sales.game_id
WHERE
    games.name LIKE 'Grand Theft Auto%';

-- Les pourcentages de ventes moyens par console
-- 22 ms -> 70 ms
SELECT
    platforms.name,
    avg(sales.global_sales) AS "avg sales"
FROM
    sales
    JOIN games ON games.id = sales.game_id
    JOIN platforms ON games.platform_id = platforms.id
GROUP BY
    platforms.name;

-- Le rang minimal obtenu par un jeu qui commence par un Z
-- 0.9 ms -> 2.7 ms
SELECT
    min(sales.rank) as "rank"
FROM
    sales
    JOIN games ON games.id = sales.game_id
WHERE
    games.name LIKE 'Z%';

-- Les studios de jeux vidéos qui ont produit plus de 100 jeux sur PS3
-- 5 ms -> 21 ms
WITH t AS (
    SELECT
        publishers.name AS name,
        count(*) as count
    FROM
        games
        JOIN platforms ON games.platform_id = platforms.id
        JOIN publishers ON games.publisher_id = publishers.id
    WHERE
        platforms.name = 'PS3'
    GROUP BY
        publishers.name
)
SELECT
    *
FROM
    t
WHERE
    count >= 100;

-- Le pourcentage maxium de vente fait par Ubisoft (plan)
-- 5.2 ms -> 15 ms
SELECT
    max(sales.global_sales)
FROM
    sales
    JOIN games ON games.id = sales.game_id
    JOIN publishers ON publishers.id = games.publisher_id
WHERE
    publishers.name = 'Ubisoft';

-- Les genres présents sur DS 
-- 4.2 ms -> 20 ms
SELECT
    DISTINCT genres.name
FROM
    games
    JOIN genres ON genres.id = games.genre_id
    JOIN platforms ON platforms.id = games.platform_id
WHERE
    platforms.name = 'DS';