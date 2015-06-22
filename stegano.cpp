
#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <bitset>

using namespace std;

vector<unsigned char> read(ifstream &inputFile)
{
	vector<unsigned char> buf((std::istreambuf_iterator<char>(inputFile)), (std::istreambuf_iterator<char>()));

	return buf;
}

int main(int argc, char* argv[])
{
	ifstream wavFile("input.wav", ios::binary);
	if (!wavFile)
	{
		cout << "Error! Unable to open wav file! " << argv[1] << endl;
		return 0;
	}

	ifstream txtFile("input.txt", ios::binary);
	if (!txtFile)
	{
		cout << "Error! Unable to open txt file! " << argv[2] << endl;
		return 0;
	}

	vector<unsigned char> mas_wav = read(wavFile);
	vector<unsigned char> mas_txt = read(txtFile);

	if (mas_wav.size() - 44 < mas_txt.size() * 8)
	{
		cout << "Error! Increase wav file capacity." << endl;
		return 0;
	}

	size_t j = 44;
	for (size_t i = 0; i < mas_txt.size(); i++)
	{
		unsigned char wav = mas_wav[j];
		unsigned char txtByte = mas_txt[i];

		unsigned char bit = txtByte;

		for (size_t k = 0; k < 8; k++)
		{
			bit <<= i;
			bit >>= (7 - i);

			wav >>= 1;
			wav <<= 1;

			if (bit)
			{
				wav += 1;
			}

			mas_wav[j] = wav;
			++j;
			wav = mas_wav[j];
		}

	}

	ofstream outputFile("output.wav", ios::binary);

	for (size_t i = 0; i < mas_wav.size(); i++)
	{
		outputFile << static_cast<unsigned char>(mas_wav[i]);
	}
	system("pause");
	outputFile.close();
	return 0;
}