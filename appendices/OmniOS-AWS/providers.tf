terraform {
  required_providers {
    aws = {
      source = "hashicorp/aws"
      version = "~> 3.0"
    }
  }
}

provider "aws" {
  region = "us-east-1"

  # Make it clear where these resources came from
  default_tags {
    tags = {
      Name    = "revolving-doors"
      Project = "https://github.com/robertdfrench/revolving-doors"
    }
  }
}
