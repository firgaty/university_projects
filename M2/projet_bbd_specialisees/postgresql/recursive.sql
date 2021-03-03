WITH RECURSIVE split(name, split_name, rest) AS (
    SELECT
        games.name,
        '',
        games.name || ' '
    FROM
        games AS games
    UNION
    ALL
    SELECT
        name,
        SUBSTRING(rest, 0, position(' ' IN rest)),
        SUBSTRING(rest, position(' ' IN rest) + 1)
    FROM
        split
    WHERE
        rest <> ''
)
SELECT
    DISTINCT name,
    LOWER(split_name) AS split_name
FROM
    split
WHERE
    split_name <> ''
ORDER BY
    name;