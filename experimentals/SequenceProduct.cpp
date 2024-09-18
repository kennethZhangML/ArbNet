#include <iostream>
#include <optional>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>

struct Product
{
  std::string Name;
  std::optional<double> Price;
  std::vector<std::string> Ingredients;
};

std::vector<std::string> SplitString(const std::string& str, const std::string& delimiter)
{
  std::vector<std::string> strs;
  size_t startPos = 0;
  size_t endPos = 0;
  while((endPos = str.find(delimiter, startPos)) != std::string::npos)
  {
    strs.emplace_back(str.substr(startPos, endPos - startPos));
    startPos = endPos + 1;
  }
  strs.emplace_back(str.substr(startPos));
  return strs;
}

std::vector<Product> GetProducts()
{
  std::vector<Product> products{};
  std::string input{};
  while(std::getline(std::cin, input))
  {
    if(input.empty())
    {
      break;
    }
    Product product{};
    auto inputs = SplitString(input, ",");
    if(inputs.size() != 3 && inputs.size() != 4)
    {
      std::cout << "Failed to parse input; Input=\"" << input << "\"" << std::endl;
      throw;
    }
    product.Name = inputs[0];
    if(inputs[1] != "null")
    {
      product.Price = stof(inputs[1]);
    }
    auto numIngredients = stoi(inputs[2]);
    if(numIngredients > 0)
    {
      if(inputs.size() != 4)
      {
        std::cout << "Failed to parse ingredients input; Input=\"" << input << "\"" << std::endl;
        throw;
      }
      product.Ingredients = SplitString(inputs[3], ";");
    }
    products.emplace_back(product);
  }

  return products;
}

std::unordered_map<std::string, double> costMemo;

double CalculateCost(const std::string& productName, const std::unordered_map<std::string, Product>& productMap) {
  if (costMemo.find(productName) != costMemo.end()) {
    return costMemo[productName];
  }
  
  const Product& product = productMap.at(productName);
  double minCost = product.Price.value_or(std::numeric_limits<double>::max());
  
  if (!product.Ingredients.empty()) {
    double buildCost = 0;
    for (const std::string& ingredient : product.Ingredients) {
      buildCost += CalculateCost(ingredient, productMap);
    }
    minCost = std::min(minCost, buildCost);
  }
  
  costMemo[productName] = minCost;
  return minCost;
}

double MySolution(const std::string& target, const std::vector<Product>& products)
{
  std::unordered_map<std::string, Product> productMap;
  for (const auto& product : products) {
    productMap[product.Name] = product;
  }
  return CalculateCost(target, productMap);
}

int main()
{
  std::string targetProductName;
  std::getline(std::cin, targetProductName);
  auto products = GetProducts();

  double bestPrice = MySolution(targetProductName, products);
  printf("%.2f\n", bestPrice);
  return 1;
}


