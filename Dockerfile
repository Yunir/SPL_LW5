FROM gcc:14.2.0

WORKDIR /app
COPY Makefile /app/
COPY images /app/images
COPY src /app/src

RUN make

ENTRYPOINT ["./main"]