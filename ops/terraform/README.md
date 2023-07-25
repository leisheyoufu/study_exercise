// 初始化
terraform init
// apply changes
terraform apply .

// 查看状态
terraform state show
terraform state list

## input variable
variable "server_port" {
  description = "The port the server will use for HTTP requests"
  default = "8080"
}
resource "aws_security_group" "instance" {
  name = "terraform-example-instance"
  
  ingress {
    from_port	  = "${var.server_port}"
    to_port	    = "${var.server_port}"
    protocol	  = "tcp"
    cidr_blocks	= ["0.0.0.0/0"]
  }
}

变量可以通过environment指定环境，比如dev, staging

terraform apply -var "server_port=9000" // # prompt specify variable
tetraform apply -var-file terraform.tfvars

## credential
aws config to sture key

## tf module input and output
path start with ./ use local module, otherwise use module from cloud


## provisor
can execute scripts on instance, not suggest use


[Download and setup terraform](https://www.terraform.io/downloads.html)