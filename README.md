🌐 C++ Web Server
📌 Introduction

This C++ Web Server is a robust, efficient, and easy-to-use web server built using the standalone ASIO library. It's designed to serve static files from a specified root directory over HTTP. The server is suitable for a wide array of applications including hosting websites, providing file downloads, or even for educational purposes to understand the basics of web server operations and HTTP protocols.
⚙️ Features

    Multi-threaded: Efficiently handles multiple connections concurrently using threads.
    MIME Type Recognition: Automatically determines the MIME type based on file extensions.
    Static File Serving: Serves files from a specified root directory.
    Local Network Accessibility: Accessible from any device within the same local network.

📋 User Manual
Prerequisites

    C++ Compiler: A modern C++ compiler that supports C++11 standard (e.g., g++).

    ASIO Library: This project uses the standalone version of ASIO, which does not require Boost. It can be installed via package managers like apt on Ubuntu:

    bash

    sudo apt install libasio-dev

    Or you can download it from ASIO's official website.

Compilation

Ensure you have g++ and the ASIO library installed. Navigate to the root directory of the project and compile the server using the following command:

bash

g++ -std=c++11 -pthread src/server.cpp -o bin/server -l pthread

If your ASIO headers are in a non-standard directory, include the path:

bash

g++ -std=c++11 -pthread -I/path/to/asio/include src/server.cpp -o bin/server -l pthread

Running the Server

Execute the compiled server using:

bash

./bin/server

The server will start on port 8080 by default. Access it by going to http://localhost:8080 in your web browser.
Accessing from Other Devices

Any device on the same local network can access the server. They need to enter http://<Server's Local IP Address>:8080 in their browser. The server's local IP address can be found by running ifconfig (on Linux/Mac) or ipconfig (on Windows) in the terminal.
Stopping the Server

To stop the server, you can simply press Ctrl+C in the terminal where it's running.
⚠️ Safety Concerns

    🛡️ Port Exposure: The server listens on port 8080 by default. Ensure that exposing this port doesn't violate your network security policies.
    ⚠️ Directory Traversal: Ensure that the server's root directory doesn't contain sensitive files, as all files in the directory will be publicly accessible.
    🔒 No HTTPS Support: This server does not support encrypted connections (HTTPS). For production use, it's recommended to add SSL/TLS support or use a reverse proxy that provides encryption.
    🐛 Error Handling: Basic error handling is implemented. However, in a production environment, more robust error handling and logging would be advisable.
    💻 Resource Management: The server spawns a new thread for each connection. For a high number of concurrent connections, resource management strategies should be considered.

📝 License

This software is provided under the MIT License.
✒️ Author

[Your Name]
