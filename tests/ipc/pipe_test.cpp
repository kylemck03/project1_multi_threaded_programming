// #include <gtest/gtest.h>
// #include <string>
// #include <cstdio>
// #include <array>
// #include <thread>
// #include <chrono>

// class PipeTest : public ::testing::Test {
// protected:
//     static void SetUpTestSuite() {
//         // Compile the producer and consumer if needed
//     }
// };

// // Test basic pipe communication
// TEST_F(PipeTest, BasicCommunication) {
//     FILE* pipe = popen("./producer | ./consumer", "r");
//     ASSERT_NE(pipe, nullptr);
    
//     std::array<char, 128> buffer;
//     std::string result;
    
//     while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
//         result += buffer.data();
//     }
    
//     pclose(pipe);
//     EXPECT_FALSE(result.empty());
// }

// // Test large data transfer
// TEST_F(PipeTest, LargeDataTransfer) {
//     // Create large test data
//     const int DATA_SIZE = 1000000;
//     std::string large_data;
//     large_data.reserve(DATA_SIZE);
    
//     auto start = std::chrono::high_resolution_clock::now();
    
//     FILE* pipe = popen("./producer | ./consumer", "r");
//     ASSERT_NE(pipe, nullptr);
    
//     // Measure throughput
//     auto end = std::chrono::high_resolution_clock::now();
//     auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    
//     pclose(pipe);
    
//     // Verify performance meets requirements (e.g., < 1 second for 1MB)
//     EXPECT_LT(duration.count(), 1000);
// } 