FROM golang:latest

WORKDIR /usr/src/app

# pre-copy/cache go.mod for pre-downloading dependencies and only redownloading them in subsequent builds if they change
COPY go.mod .
COPY src/main.go .

RUN go mod download && go mod verify
RUN go get
RUN go build -v -o /usr/local/bin/app .

EXPOSE 8080

ENTRYPOINT [ "/usr/local/bin/app" ]