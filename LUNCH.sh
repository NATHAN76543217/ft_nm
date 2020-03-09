bash CLEAN.sh
docker build -t mon_image . && docker run --name mon_container mon_image