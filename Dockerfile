# Get the base Ubuntu image from Docker Hub
FROM ubuntu:latest

# Update apps on the base image
RUN apt -y update && apt install -y

# Install the Clang compiler
RUN apt -y install clang git-all

# Copy the current folder which contains C++ source code to the Docker image under /usr/src
COPY . /usr/src/turinidev1

# Specify the working directory
WORKDIR /usr/src/turinidev1

# Use Clang to compile the Test.cpp source file
RUN clang++ -o Main main.cpp

# Run the output program from the previous step
CMD ["./Main"]