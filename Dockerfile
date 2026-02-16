# Pull the gcc image
FROM gcc:13    

# Set the working directory
WORKDIR /app

# Copy the project's directory content from the current directory to docker's current direcotry
COPY  Dynamic_Array/ .

# Run make
RUN make

# Run the program
CMD ["./ArrayList"]
