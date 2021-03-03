DROP TABLE IF EXISTS platforms CASCADE;
DROP TABLE IF EXISTS genres CASCADE;
DROP TABLE IF EXISTS publishers CASCADE;
DROP TABLE IF EXISTS games CASCADE;
DROP TABLE IF EXISTS sales CASCADE;

CREATE TABLE platforms (
    id INT GENERATED ALWAYS AS IDENTITY,
    name VARCHAR(255) NOT NULL UNIQUE,

    PRIMARY KEY(id)
);

CREATE TABLE genres (
    id INT GENERATED ALWAYS AS IDENTITY,
    name VARCHAR(255) NOT NULL UNIQUE,

    PRIMARY KEY(id)
);

CREATE TABLE publishers (
    id INT GENERATED ALWAYS AS IDENTITY,
    name VARCHAR(255) NOT NULL UNIQUE,

    PRIMARY KEY(id)
);

CREATE TABLE games (
    id INT GENERATED ALWAYS AS IDENTITY,
    name VARCHAR(255) NOT NULL,
    year INT NOT NULL,
    platform_id INT NOT NULL,
    genre_id INT NOT NULL,
    publisher_id INT NOT NULL,

    PRIMARY KEY(id),
    CONSTRAINT fk_platform_id FOREIGN KEY(platform_id) REFERENCES platforms(id) ON DELETE CASCADE,
    CONSTRAINT fk_genre_id FOREIGN KEY(genre_id) REFERENCES genres(id) ON DELETE SET NULL,
    CONSTRAINT fk_publisher_id FOREIGN KEY(publisher_id) REFERENCES publishers(id) ON DELETE CASCADE,
    CONSTRAINT unique_multiple_key UNIQUE (name, year, platform_id, genre_id, publisher_id)
);

CREATE TABLE sales (
    rank INT,
    game_id INT NOT NULL UNIQUE,
    na_sales REAL NOT NULL,
    eu_sales REAL NOT NULL,
    jp_sales REAL NOT NULL,
    other_sales REAL NOT NULL,
    global_sales REAL NOT NULL,

    CONSTRAINT pk_rank PRIMARY KEY(rank),
    CONSTRAINT fk_game_id FOREIGN KEY(game_id) REFERENCES games(id) ON DELETE CASCADE
);