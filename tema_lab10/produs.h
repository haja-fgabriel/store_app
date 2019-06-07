#pragma once

#include <string>
#include <iostream>

void increment_inst();

int get_inst();


class produs
{
private:
	std::string nume, tip, producator;
	float pret = 0;

public:
	produs(const std::string &nume, const std::string tip, const float &pret, const std::string &producator);
	produs() { increment_inst(); pret = 0; };
	~produs();
	
	std::string get_nume() const;
	std::string get_tip() const;
	std::string get_producator() const;
	float get_pret() const;

	std::string get_member_names() const;

	std::string get_pret_as_string(int & lng) const;

	bool operator==(const produs &other) const;

	void set_nume(const std::string &nume);
	void set_tip(const std::string &nume);
	void set_producator(const std::string &nume);
	void set_pret(const float &k);

	produs& operator=(const produs& pr);
	
	
	friend std::istream& operator>>(std::istream& s, produs& prd);
	friend std::ostream& operator<<(std::ostream& s, produs prd);
	
};
