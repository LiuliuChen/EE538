#include <map>
#include <vector>
#include <unordered_set>
#include "gtest/gtest.h"
#include "src/lib/trojanmap.h"


// Test Autocomplete function
TEST(TrojanMapTest, Autocomplete) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test the simple case
  auto names = m.Autocomplete("Ko");
  std::unordered_set<std::string> gt1 = {"Korean Presbyterian Church", "Kobunga Korean Grill"}; // groundtruth for "Ko"
  int success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt1.count(n) > 0, true);
    if (gt1.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt1.size());
  // Test the lower case
  names = m.Autocomplete("ko");
  std::unordered_set<std::string> gt2 = {"Korean Presbyterian Church", "Kobunga Korean Grill"}; // groundtruth for "ko"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt2.count(n) > 0, true);
    if (gt2.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt2.size());
  // Test the lower and upper case 
  names = m.Autocomplete("kO"); 
  std::unordered_set<std::string> gt3 = {"Korean Presbyterian Church", "Kobunga Korean Grill"}; // groundtruth for "kO"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt3.count(n) > 0, true);
    if (gt3.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt3.size());
  // Test the upper case 
  names = m.Autocomplete("KO"); 
  std::unordered_set<std::string> gt4 = {"Korean Presbyterian Church", "Kobunga Korean Grill"}; // groundtruth for "KO"
  success = 0;
  for (auto& n: names) {
    EXPECT_EQ(gt4.count(n) > 0, true);
    if (gt4.count(n) > 0){
      success++;
    }
  }
  EXPECT_EQ(success, gt4.size());
}

// Test FindPosition function
TEST(TrojanMapTest, FindPosition) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test CVS
  auto position = m.GetPosition("CVS");
  std::pair<double, double> gt1(34.0234847,-118.2793109); // groundtruth for "CVS"
  EXPECT_EQ(position, gt1);
  // Test Kobunga Korean Grill
  position = m.GetPosition("Kobunga Korean Grill");
  std::pair<double, double> gt2(34.0250482,-118.2853951); // groundtruth for "Kobunga Korean Grill"
  EXPECT_EQ(position, gt2);
  // Test Coffee Bean2
  position = m.GetPosition("Coffee Bean2");
  std::pair<double, double> gt3(34.0246375,-118.2853001); // groundtruth for "Coffee Bean2"
  EXPECT_EQ(position, gt3);
  // Test Unknown
  position = m.GetPosition("XXX");
  std::pair<double, double> gt4(-1, -1);
  EXPECT_EQ(position, gt4);
}

// Test CalculateShortestPath_Bellman_Ford function
TEST(TrojanMapTest, CalculateShortestPath_Bellman_Ford) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from CVS to Target
  auto path = m.CalculateShortestPath_Bellman_Ford("CVS", "Target");
  std::vector<std::string> gt{ "3088548446", "6813379501", "6787803628", "6285409682", "6813379531", "4141790934", "123327636", "6807200379", "123327627", "6813379521", "6813379517", "6813379513", "123005253", "4399698008", "4399698009", "123044712", "4399698010", "4399698011", "4399698013", "4399698012", "5237381975", "6813379479", "5237417650" }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to CVS
  path = m.CalculateShortestPath_Dijkstra("Target", "CVS");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

// Test CalculateShortestPath_Dijkstra function
TEST(TrojanMapTest, CalculateShortestPath_Dijkstra) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test from CVS to Target
  auto path = m.CalculateShortestPath_Dijkstra("CVS", "Target");
  std::vector<std::string> gt{ "3088548446", "6813379501", "6787803628", "6285409682", "6813379531", "4141790934", "123327636", "6807200379", "123327627", "6813379521", "6813379517", "6813379513", "123005253", "4399698008", "4399698009", "123044712", "4399698010", "4399698011", "4399698013", "4399698012", "5237381975", "6813379479", "5237417650" }; // Expected path
  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
  
  // Reverse the input from Target to CVS
  path = m.CalculateShortestPath_Dijkstra("Target", "CVS");
  std::reverse(gt.begin(),gt.end()); // Reverse the path

  // Print the path lengths
  std::cout << "My path length: "  << m.CalculatePathLength(path) << "miles" << std::endl;
  std::cout << "GT path length: " << m.CalculatePathLength(gt) << "miles" << std::endl;
  EXPECT_EQ(path, gt);
}

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
}


// Test cycle detection function
TEST(TrojanMapTest, CycleDetection) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  // Test case 1
  std::vector<double> square1 = {-118.283, -118.269, 34.029, 34.018};
  bool result1 = m.CycleDetection(square1);
  EXPECT_EQ(result1, true);

  // Test case 2
  std::vector<double> square2 = {-118.290919, -118.282911, 34.02235, 34.019675};
  bool result2 = m.CycleDetection(square2);
  EXPECT_EQ(result2, false);
}

// Test Topological sort function(The nodes do not relate to the map)
TEST(TrojanMapTest, TopologicalSort) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  std::vector<std::string> location_names = {"0", "1","2", "3", "4", "5"};
  std::vector<std::vector<std::string>> dependencies = {{"2","3"}, {"3","1"}, {"4","0"}, {"4", "1"}, {"5", "0"}, {"5", "1"}};
  auto result = m.DeliveringTrojan(location_names, dependencies);
  std::vector<std::string> gt ={"5", "4","2", "3", "1", "0"};
  EXPECT_EQ(result, gt);
}

// Test K closest points
TEST(TrojanMapTest, FindKClosestPoints) {
  TrojanMap m;
  m.CreateGraphFromCSVFile();
  auto result = m.FindKClosestPoints("CVS",6);
  std::vector<std::string> gt{
  "6045067407", "4400281328", "6045067406", "6047237631", "6045038065", "5231970321"};
  EXPECT_EQ(result, gt);
}
