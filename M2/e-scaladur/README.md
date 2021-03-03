# POCA 2020

Realised by ([efraika](https://github.com/efraika)), [firgaty](https://github.com/firgaty), [vch9](https://github.com/vch9), [Shtrow](https://github.com/Shtrow) and [maiste](https://github.com/maiste)
Original repository can be found [here](https://gaufre.informatique.univ-paris-diderot.fr/e-scaladur/poca-2020).


[![license](https://img.shields.io/badge/license-MPL%202.0-blue?style=flat-square)](https://www.mozilla.org/en-US/MPL/2.0/)

Our product is a marketplace connecting buyers to sellers. Similar products are: Amazon.com, Rakuten, Cdiscount.com, Veepee...

Online shopping is not original at all but it has a rich domain with interesting choices to make. Let's view it as a playground where we can either borrow ideas from our competitors or build our own vision of what a marketplace should be!

## Install instructions

To run the software locally, Docker and postgresql is needed.

In addition, scala, sbt and terraform are needed for development.

### Create the database

To connect: `sudo -u postgres psql`

```
postgres=# create database poca;
CREATE DATABASE
postgres=# create user poca with encrypted password 'poca';
CREATE ROLE
postgres=# grant all privileges on database poca to poca;
GRANT
postgres=# \connect poca
You are now connected to database "poca" as user "postgres".
poca=# alter schema public owner to poca;
ALTER SCHEMA
```

In `pg_hba.conf`, make sure there is a way to connect as poca:
* `local poca poca md5` to connect using `psql`
* `host poca poca 127.0.0.1/32 md5` to connect using TCP.

Restart the database. Test the connection with `psql poca poca`.

If you plan to run tests, you need to create another database `pocatest`.


## Run the tests

```
sbt clean coverage test coverageReport
```

This also creates a coverage report at [target/scala-2.13/scoverage-report/index.html](target/scala-2.13/scoverage-report/index.html).

## Add or update a table

To add a new table or update a previous one, you have to follow this steps:

1. Create a new file in the directory [src/main/scala/migrations](src/main/scala/migrations) with the name *Migration<ID>Action*.
2. In this file, add a new class that extends the Migration class
Ex:
```scala
package poca

import scala.concurrent.{Future, Await}
import scala.concurrent.duration.Duration
import com.typesafe.scalalogging.LazyLogging
import slick.jdbc.PostgresProfile.api._


class Migration<ID>Action(db: Database) extends Migration with LazyLogging {
    override def apply() {
      // Modification in the database
    }
}
```
3. Insert it into the migration list, line 10, in the [Migration.scala](src/main/scala/migrations/Migration.scala) file.

## Run the software

### Use the software online

Go to http://15.236.151.45/hello

### Run locally using the Docker image from Docker Hub

```
docker run poca/poca-2020:latest
```

### Run from the local directory

```
sbt run
```

Then visit `http://localhost:8080/hello`

## Package to a Docker image

```
sbt docker:publishLocal
```

Then the image with name `poca-2020` and tag `latest` is listed. (There is also an image `poca-2020:0.1.0-SNAPSHOT` that is identical).

```
docker image ls
```

Run the docker image locally:

```
docker run --net=host poca-2020:latest
```

To remove old images:

```
docker image prune
```

## Deployment

In the directory `terraform`, to initialize the project:

```
terraform init
```

Set the secrets in you shell:

```
export TF_VAR_db_password="xxx"
```

To plan the deployment:

```
terraform plan --var-file=integration.tfvars
```

To deploy:

```
terraform apply --var-file=integration.tfvars
```

To destroy:

```
terraform destroy --var-file=integration.tfvars
```

## Logs

Logs are stored on AWS Cloudwatch: https://eu-west-3.console.aws.amazon.com/cloudwatch/home?region=eu-west-3#logsV2:log-groups/log-group/poca-web/log-events
