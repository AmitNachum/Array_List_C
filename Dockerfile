# Pull the gcc image
FROM gcc:13    

# Set the working directory
WORKDIR /app

# Copy the project from the current directory to docker's current direcotry
COPY . . 

# Run make
RUN make

# Run the program
CMD ["./main"]
