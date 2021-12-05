#include <map>
#include <vector>

#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"


// Test TSP function
TEST(TrojanMapTest, TSP) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> input{"1873056015", "6905329551", "213332060", "1931345270"}; // Input location ids 
  auto result = m.TravellingTrojan(input);
  std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
  std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
  std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
  bool flag = false;
  if (gt == result.second[result.second.size()-1]) // clockwise
    flag = true;
  std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
  if (gt == result.second[result.second.size()-1]) 
    flag = true;
  
  EXPECT_EQ(flag, true);

  auto result_2opt = m.TravellingTrojan_2opt(input);
  std::cout << "My path length of 2-opt: "  << result_2opt.first << "miles" << std::endl; // Print the result path lengths
  EXPECT_EQ(false, true);
}

// TEST(TrojanMapTest, TSP) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::vector<std::string> input{"358786623","368172344", "1873056015", "4399693644","6905329551", "358850019", "4399693646", "213332060", "1931345270", "358793609"}; // Input location ids 
//   auto result = m.TravellingTrojan(input);
//   std::cout << "My path length: "  << result.first << "miles" << std::endl; // Print the result path lengths
//   std::vector<std::string> gt{"1873056015", "213332060", "1931345270", "6905329551", "1873056015"}; // Expected order
//   std::cout << "GT path length: "  << m.CalculatePathLength(gt) << "miles" << std::endl; // Print the gt path lengths
//   bool flag = false;
//   if (gt == result.second[result.second.size()-1]) // clockwise
//     flag = true;
//   std::reverse(gt.begin(),gt.end()); // Reverse the expected order because the counterclockwise result is also correct
//   if (gt == result.second[result.second.size()-1]) 
//     flag = true;
  
//   EXPECT_EQ(flag, true);

//   auto result_2opt = m.TravellingTrojan_2opt(input);
//   std::cout << "My path length of 2-opt: "  << result_2opt.first << "miles" << std::endl; // Print the result path lengths
//   EXPECT_EQ(false, true);
// }

// // Test Topological sort function
// TEST(TrojanMapTest, TopologicalSort) {
//   TrojanMap m;
//   m.CreateGraphFromCSVFile();
//   std::vector<std::string> location_names = {"0", "1","2", "3", "4", "5"};
//   std::vector<std::vector<std::string>> dependencies = {{"2","3"}, {"3","1"}, {"4","0"}, {"4", "1"}, {"5", "0"}, {"5", "1"}};
//   auto result = m.DeliveringTrojan(location_names, dependencies);
//   std::vector<std::string> gt ={"5", "4","2", "3", "1", "0"};
//   EXPECT_EQ(result, gt);
// }

