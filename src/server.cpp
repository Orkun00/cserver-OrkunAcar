#include "server.h"

// Root directory where server files are located
const std::string root_directory = "site/";

// Map to associate file extensions with MIME types 
std::unordered_map<std::string, std::string> content_type_map = {
    {".html", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".webp", "image/webp"}
};

// Function to get the MIME type based on file extension
std::string get_content_type(const std::string& extension) {
    // Check if the extension is in the map
    if (content_type_map.find(extension) != content_type_map.end()) {
        return content_type_map[extension]; // Return the MIME type
    }
    return "application/octet-stream"; // Default MIME type if not found
}

// Function to create the HTTP response message
std::string make_http_response(const std::string& status, const std::string& content_type, const std::string& content) {
    std::ostringstream response_stream; // Use a string stream
    // Write the response headers
    response_stream << "HTTP/1.1 " << status << "\r\n";
    response_stream << "Content-Type: " << content_type << "\r\n";
    response_stream << "Content-Length: " << content.size() << "\r\n";
    response_stream << "Connection: close\r\n";
    response_stream << "\r\n";
    // Add the content
    response_stream << content;
    // Convert stream to string
    return response_stream.str();
}

// Function to read the content of a file
std::string get_file_content(const std::string& file_path) {
    std::ifstream file(file_path, std::ios::binary); // Open in binary mode
    if (file) { // If the file is open
        std::ostringstream content_stream;
        content_stream << file.rdbuf(); // Read the file content
        return content_stream.str(); // Return as a string
    }
    return ""; // Return empty string if file not found
}

// Function to handle HTTP requests
void handle_request(const std::string& request, tcp::socket& socket) {
    std::string file_path = root_directory;
    size_t path_end = request.find(' ', 4);
    if (path_end != std::string::npos) {
        file_path += request.substr(4, path_end - 4); // Extract the file path
        if (file_path.back() == '/') {
            file_path += "index.html"; // Default to index.html
        }
    }

    std::string extension = file_path.substr(file_path.find_last_of(".")); // Get file extension
    std::string content = get_file_content(file_path); // Get file content
    std::string response;

    // Check if content was found
    if (!content.empty()) {
        response = make_http_response("200 OK", get_content_type(extension), content); // Create 200 response
    } else {
        // Create 404 response
        std::string not_found_content = "<html><body><h1>404 Not Found</h1></body></html>";
        response = make_http_response("404 Not Found", "text/html", not_found_content);
    }

    // Write the response back to the socket
    asio::write(socket, asio::buffer(response));
}

// Function to handle each client in a separate thread
void handle_client(tcp::socket socket) {
    try {
        std::array<char, 1024> buffer; // Buffer to store request data
        size_t bytes_transferred = socket.read_some(asio::buffer(buffer)); // Read data from socket

        // Convert buffer to string and process the request
        std::string request(buffer.data(), bytes_transferred);
        handle_request(request, socket); // Handle the request
    } catch (std::exception& e) {
        // If an exception occurs, print it to stderr
        std::cerr << "Exception in thread: " << e.what() << "\n";
    }
}

// Main function where the server runs
int main() {
    try {
        asio::io_context io_context; // ASIO context
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 8080)); // Listen on port 8080
        std::cout << "Server is running on port 8080...\n";

        // Server loop
        while (true) {
            tcp::socket socket(io_context); // Socket for each client
            acceptor.accept(socket); // Accept incoming connections
            
            // Create a thread to handle the client
            std::thread client_thread(handle_client, std::move(socket));
            client_thread.detach(); // Detach the thread so it runs independently
        }
    } catch (std::exception& e) {
        // If an exception occurs, print it to stderr
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0; // End of program
}