# Pull the gcc image
FROM gcc:13    

# Set the working directory
WORKDIR /app

# Copy the project's directory content from the current directory to docker's current direcotry
COPY  . .

# step into the app source file and run make
WORKDIR /app/Dynamic_Array 
RUN make

# Run the program
CMD ["./ArrayList"]
