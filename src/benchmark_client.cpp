#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include <string>
#include "httplib.h"

using namespace httplib;

const std::string API_URL = "http://localhost:8080/v1/keys/";
std::atomic<int> total_requests(0);
std::atomic<double> total_latency(0.0);

void benchmark_client(int thread_id, int num_keys) {
    Client cli("localhost");
    for (int key_id = thread_id; key_id < num_keys * 1024; ++key_id) {
        int key = key_id % num_keys;
        auto start = std::chrono::high_resolution_clock::now();
        
        // Set request headers
        const Header hdrs[] = { {"Content-Type", "application/json"} };

        // Prepare empty body (for demonstration purposes)
        const char* json_body = "{}";

        Result res = cli.Put(
            API_URL + std::to_string(key),
            json_body,                  // Request body
            const_cast<Header*>(hdrs)   // Include headers in the Put request
        );

        if (res && res->status == 200) {
            auto latency = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
            total_latency += latency;
            ++total_requests;
        } else {
            std::cerr << "Error: Unable to set key " << key_id << "; status code: " 
                      << (res ? res->status : 0) << "\n";
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 4) {
        std::cerr << "Usage: ./benchmark [Num Threads] [Num Keys] [Duration]\n";
        return 1;
    }

    int num_threads = std::stoi(argv[1]);
    int num_keys = std::stoi(argv[2]);
    int duration_seconds = std::stoi(argv[3]);

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(benchmark_client, i, num_keys);
    }

    for (auto& t : threads) {
        t.join();
    }

    double throughput_per_sec = static_cast<double>(total_requests.load()) / duration_seconds;
    double average_latency = total_latency.load() / total_requests.load();

    std::cout << "Benchmark Results:\n";
    std::cout << "  Threads: " << num_threads << "\n";
    std::cout << "  Keys per thread: " << num_keys << "\n";
    std::cout << "  Duration: " << duration_seconds << " seconds\n";
    std::cout << "  Total Requests: " << total_requests.load() << "\n";
    std::cout << "  Average Latency (micros): " << average_latency << "\n";

    return 0;
}
