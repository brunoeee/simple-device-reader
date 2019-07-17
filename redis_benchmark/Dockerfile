FROM redis:5.0.5-alpine

# wait for connections
COPY . /app
WORKDIR /app
RUN ["chmod", "+x", "wait-for"]
