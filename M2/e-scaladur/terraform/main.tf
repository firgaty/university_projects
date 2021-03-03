# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.


/*
The AWS user used by terraform is granted the AWS managed policy AdministratorAccess.
*/

terraform {
  backend "s3" {
    bucket = "escaladur-tfstates"
    key = "poca-2020"
    region = "eu-west-3"
    dynamodb_table = "poca-tfstates-locks"
  }
  required_providers {
    aws = {
      source  = "hashicorp/aws"
      version = "~> 3.7.0"
    }
  }
}

provider "aws" {
  region = "eu-west-3"  # Europe (Paris)
}

data "aws_ami" "amazon_linux_2" {
  most_recent = true
  owners = ["amazon"]

  filter {
    name = "name"
    values = ["amzn2-ami-hvm-*-x86_64-gp2"]
  }
}
