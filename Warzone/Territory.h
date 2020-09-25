#pragma once

#include <string>

class Territory {
private:
	std::string name;
	int armies;

public:
	Territory() = default;

	Territory(const std::string& name) : name(name), armies(0) {}

	Territory(const Territory &c);

	std::string getName() const;

	void setName(const std::string& name);

	bool operator==(const Territory& other) const;

	bool operator!=(const Territory& other) const { return !operator==(other); }

	bool operator<(const Territory& second) const;

	void increaseArmies(); // TODO: Rename to incrementArmies

	int getArmies() const;

	void setArmies(int n); //sets amount of armies on territory

	void increaseArmiesBy(int n);

	void decreaseArmiesBy(int n);
};
