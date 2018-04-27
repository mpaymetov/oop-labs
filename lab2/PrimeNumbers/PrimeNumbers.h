#pragma once

bool GetNumber(const std::string &str, int& number);

std::vector<bool> GenerateIsPrimeVector(int upperBound);

std::set<int> GeneratePrimeNumbersSet(int upperBound);

void PrintPrimeNumbers(const std::set<int>& primeNumbers);

