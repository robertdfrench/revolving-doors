output "ipv4_address" {
  description = "Public IPv4 Address of the OmniOS VM"
  value       = aws_instance.lab_host.public_ip
}

resource "aws_instance" "lab_host" {
  ami             = data.aws_ami.omnios.id
  instance_type   = "t2.micro"
  key_name        = aws_key_pair.lab_key.key_name
  security_groups = [aws_security_group.allow_ssh.name]
}

resource "aws_security_group" "allow_ssh" {
  name        = "revolving-doors"

  ingress {
    description = "Inbound SSH"
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    description = "Outbound Whatever"
    from_port   = 0
    to_port     = 0
    protocol    = -1
    cidr_blocks = ["0.0.0.0/0"]
  }
}

data "aws_ami" "omnios" {
  // You can verify the results of this query against the list of AMIs (by
  // region) at https://omnios.org/setup/aws.html.
  most_recent = true
  owners = ["313551840421"] # OmniOS Community Edition Association

  filter {
    name   = "name"
    values = ["OmniOS *"]
  }
}

resource "aws_key_pair" "lab_key" {
  key_name = "revolving-doors"
  
  public_key = file("build/lab_key.pub")
}
