FROM debian:buster
RUN apt-get update
RUN apt-get -y upgrade
RUN apt-get install -y vim
RUN apt-get install -y wget
RUN apt-get install -y curl
RUN apt-get install -y net-tools
RUN apt-get install -y man
RUN apt-get install -y binutils
RUN apt-get install -y gcc
RUN apt-get install -y file
RUN apt-get install -y git
RUN apt-get install -y zsh
RUN apt-get install -y make
RUN apt-get install -y lldb
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

RUN mkdir /ft_nm
RUN mkdir /ft_nm/srcs
RUN mkdir /ft_nm/includes
RUN mkdir /ft_nm/tester

COPY    ./srcs/start.sh             /app/start.sh

COPY    ./srcs/                     ./ft_nm/srcs
COPY    ./libft                     ./ft_nm/libft
COPY    ./includes                  ./ft_nm/includes
COPY    ./Makefile                  ./ft_nm/
COPY    ./tester                    ./ft_nm/tester

CMD ["/bin/bash", "/app/start.sh"]