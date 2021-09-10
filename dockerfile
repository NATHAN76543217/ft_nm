FROM	debian:buster

RUN		apt-get update
RUN		apt-get -y upgrade
RUN		apt-get install -y vim \
						wget \
						curl \
						net-tools \
						man \
						binutils \
						gcc \
						file \
						git \
						zsh \
						make \
						lldb
RUN sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"

RUN     mkdir /ft_nm
RUN     mkdir /ft_nm/srcs
RUN     mkdir /ft_nm/includes
RUN     mkdir /ft_nm/tester

COPY	./scripts/loop.sh           /app/loop.sh

COPY	./src/                     ./ft_nm
COPY    ./tester/NM_TESTER.sh		./bin/nm_tester

RUN     chmod 777 /bin/nm_tester

CMD ["/bin/bash", "/app/loop.sh"]