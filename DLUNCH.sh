bash CLEAN.sh
docker build -t mon_image . && docker run --cap-add=SYS_PTRACE --security-opt seccomp=unconfined --security-opt apparmor=unconfined --name mon_container mon_image