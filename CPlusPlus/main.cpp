#include "TextList.h"
#include <vector>

using namespace NeoSmart;

int main(int argc, const char *argv[])
{
	uint32_t failCount = 0;
	auto allNames = std::vector<std::string>{ "Meg", "Jo", "Beth", "Amy" };
	auto names = std::vector<std::string>();
	names.reserve(allNames.size());

	bool oxford = true;
	bool spaces = true;
	bool conjunction = true;

	auto with = [&](bool x) {
		return x ? "" : "out";
	};

	{
		auto textList = (TextList::Make(names));
		std::cout << ("***Empty list***");
		std::cout << textList.c_str();
	}

	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				printf("***With%s oxford comma, with%s spaces, with%s conjunction***\n", with(oxford), with(spaces), with(conjunction));

				names.clear();
				for (auto name : allNames)
				{
					names.push_back(name);
					TextList::ListFormat flags = (oxford ? TextList::ListFormat::OxfordSeparator : TextList::ListFormat::None);
					auto textList = TextList::Make(names, (conjunction ? "and" : ""), flags);
					printf(" %s\n", textList.c_str());
				}
				printf("\n");
				conjunction = !conjunction;
			}
			spaces = !spaces;
		}
		oxford = !oxford;
	}

	return true;
}
