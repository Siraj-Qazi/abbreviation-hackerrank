#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <vector>
#include <fstream>
#include <limits>

bool duplicateExists(char c, std::string test)
{
	long long count = 0;
	if (test.find(c) != std::string::npos || test.find(tolower(c)) != std::string::npos) {
		for (auto k : test)
			if (k == c || k == tolower(c))
				count++;
	}
	return (count > 1);
}

long long frequency(std::string s, char c) {
	c = toupper(c);
	std::map<char, long long> temp;

	for (auto i : s)
		temp[i]++;

	if (temp.count(c))
		return temp[c];
	else
		return 0;
}


std::string abbreviation(std::string a, std::string b)
{
	if (a == b)
		return "YES";

	if (a.size() < b.size())
		return "NO";

	std::map<char, long long> freqB;

	for (auto k : b)
		freqB[k]++;

	std::string temp;
	long long index = 0;
	for (long long i = 0; i < a.size(); ++i) {
		std::cout << "\n Processing a[" << i << "] = " << a[i];
		if (islower(a[i]))
		{
			if (temp.find(toupper(a[i])) != std::string::npos) {
				std::cout << "\n Duplicate exists = " << duplicateExists(toupper(a[i]), b) << " Frequency of a[" << i << "] in temp:  " << frequency(temp, toupper(a[i])) << " Frequency of a[i] in b: " << freqB[toupper(a[i])];
				if (duplicateExists(toupper(a[i]), b) && frequency(temp, a[i]) < freqB[toupper(a[i])])
				{

					if (toupper(a[i]) == b[index])
					{
						std::cout << "\n Appending " << (char)toupper(a[i]);
						temp.push_back(toupper(a[i]));
						index++;
					}
					continue;
				}
			}
			else if (b.find(toupper(a[i])) != std::string::npos)
			{
				std::cout << "\n b contains " << (char)toupper(a[i]);
				if (a.find(toupper(a[i])) != std::string::npos) {
					std::cout << "\n a also contains " << (char)toupper(a[i]);

					if (duplicateExists(toupper(a[i]), b) && frequency(temp, a[i]) < freqB[toupper(a[i])]) {
						std::cout << "\n b contains duplicates of " << (char)toupper(a[i]);

						if (toupper(a[i]) == b[index])
						{
							temp.push_back(toupper(a[i]));
							index++;
						}
					}
					else {
						std::cout << "\n b doesnt contain duplicates of " << (char)toupper(a[i]);
						continue;
					}
				}
				else {
					if (toupper(a[i]) == b[index])
					{
						std::cout << "\n Appending " << (char)toupper(a[i]);
						temp.push_back(toupper(a[i]));
						index++;
					}
				}
			}
		}
		else {
			if (b.find(a[i]) != std::string::npos) {

				if (temp.find(a[i]) != std::string::npos) {
					if (duplicateExists(a[i], b) && frequency(temp, a[i]) < freqB[toupper(a[i])]) {
						if (toupper(a[i]) == b[index])
						{
							std::cout << "\n Appending " << (char)toupper(a[i]);
							temp.push_back(toupper(a[i]));
							index++;
						}
					}
					else if (a.find(tolower(a[i]) != std::string::npos))
						continue;
					else
						return "NO";
				}
				else {
					if (toupper(a[i]) == b[index]) {
						std::cout << "\n Appending " << (char)toupper(a[i]);
						temp.push_back(a[i]);
						index++;
					}
				}
			}
			else {
				return "NO";
			}
		}
	}

	a = temp;
	std::cout << "\n a  = " << a << "\n b  = " << b << "\n";
	if (a == b)
		return "YES";
	else
		return "NO";
}


int main(int argc, char* argv[])
{
	if (argc < 2) {
		std::cout << "\n Usage: abbreviation <test-cases-file.txt>\n";
		exit(1);
	}
	std::ifstream inFile(argv[1]);
	std::ofstream outFile("output_abbreviation_test.txt");
	if (inFile.fail()) {
		std::cout << "\n Error in reading " << argv[1] << ".";
		exit(1);
	}
	else if (outFile.fail()) {
		std::cout << "\n Error in writing output to file.";
		exit(1);
	}
	int queries;
	inFile >> queries;
	inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::string result;

	for (long long q_itr = 0; q_itr < queries; q_itr++) {
		std::string sourceString;
		getline(inFile, sourceString);

		std::string targetString;
		std::getline(inFile, targetString);

		result = abbreviation(sourceString, targetString);

		outFile << result << "\n";
	}

	outFile.close();
	std::cout << " " << result << std::endl;

	return 0;
}