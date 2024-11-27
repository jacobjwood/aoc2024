#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <stdexcept>

std::string get_cookie() {
    std::ifstream input{"cookie.txt"};
    if (!input.is_open()) {
        throw std::runtime_error("Couldn't read cookie file."); 
    }

    std::string cookie;
    input >> cookie;

    return "session=" + cookie;
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
    // https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
    // userp = user pointer
    // cast contents from void pointer into a char pointer, and append at the end
    userp->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main(int argc, char* argv[]) {
    CURL *curl;
    CURLcode res;

    // Error handling in case day is not an int between 1 and 25
    if (argc != 2) {
        std::cerr << "Got multiple arguments. Expected a single number between 1 and 25." << std::endl;
        return 1;
    }

    int day = std::stoi(argv[1]);
    if (!(1 <= day && day <= 25)) {
        std::cerr << "Day should be between 1 and 25. Got: " << day << std::endl;
        return 1;
    }

    // Get input data
    std::string day_url = "https://adventofcode.com/2023/day/" + std::to_string(day) + "/input";     
    std::string cookie = get_cookie();
    std::string input;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, day_url.c_str());
        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &input);
        // Without a write callback, libcurl expects the CURLOPT_WRITEDATA argument to be a file pointer
        // we need this callback to specify how to write the data (appending bytes to a string).
        // This is somewhat redundant given we end up writing to a file anyway, but will keep it as it's cool to learn.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback); 

        CURLcode res = curl_easy_perform(curl);
        // Without the WriteCallback, we end up with a segfault. Need to understand this.
        curl_easy_cleanup(curl);
    }

    std::string day_input_uri = "day" + std::to_string(day) + "/input.txt";
    std::ofstream day_input_file{day_input_uri};
    day_input_file << input;

    return 0;
}
