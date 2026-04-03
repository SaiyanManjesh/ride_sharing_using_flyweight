# Build stage
FROM gcc:12-bullseye AS builder

WORKDIR /build

COPY ride_sharing_cars.cpp .

RUN g++ -std=c++17 -Wall -Wextra -O2 -static \
    -o ride_sharing_cars ride_sharing_cars.cpp

# Runtime stage - minimal image
FROM alpine:3.19

# Copy binary to /usr/local/bin so it's not overwritten by volume mount
COPY --from=builder /build/ride_sharing_cars /usr/local/bin/

# Set working directory where HTML will be generated
WORKDIR /app

# Run the application (binary is in PATH)
CMD ["ride_sharing_cars"]