#ifndef SERVER_H
#define SERVER_H
#define ASIO_STANDALONE
#include <asio.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <thread>
#include <string>
#include <asio.hpp>  

// Use namespace for easier syntax
using asio::ip::tcp;

// Root directory where server files are located
extern const std::string root_directory;

// Function to get the MIME type based on file extension
std::string get_content_type(const std::string& extension);

// Function to create the HTTP response message
std::string make_http_response(const std::string& status, const std::string& content_type, const std::string& content);

// Function to read the content of a file
std::string get_file_content(const std::string& file_path);

// Function to handle HTTP requests
void handle_request(const std::string& request, tcp::socket& socket);

// Function to handle each client in a separate thread
void handle_client(tcp::socket socket);

#endif // SERVER_H
