# Bitmap image rotation

## Quick start

Build the docker image

```shell
docker build -t spl_lw5 .
```

Run the docker container with a mounted directory to get the results 

```shell
docker run --rm -v ./images:/app/images spl_lw5
```