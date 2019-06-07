#pragma once
#include "Cos.h"
#include "Observable.h"

class service_cos : public Observable
{
private:
	cos_cumparaturi& cos;
	
public:
	service_cos(cos_cumparaturi& cs) : cos{cs} {}

	service_cos& operator=(service_cos& ss);

	float genereaza_cos(const int &k);
	float adauga_incos(const std::string& str);
	float salveaza_cos(std::string nume = "");
	float goleste_cos();

	const std::vector<produs*>& get_cos() const;

	service_cos() = default;
	~service_cos();
};

