#include <iostream>
#include <string>
#include <clocale>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;

struct Rec
{
	std::string name, phone, addr;
	struct ByName {};
	struct ByPhone {};
	struct ByAddr {};
};

typedef boost::multi_index_container<Rec, indexed_by< ordered_unique< tag<Rec::ByName>,
	member<Rec, std::string, &Rec::name>
>,
ordered_non_unique<
	tag<Rec::ByPhone>, member<Rec, std::string, &Rec::phone>
>,
ordered_non_unique<
	tag<Rec::ByAddr>, member<Rec, std::string, &Rec::addr>
>
>
> Store;

int main(int argc, char** argv)
{
	Store rec_inf;
	Rec r1 = { "Jo Byden", "+442089786564", "White house, USA" };
	Rec r2 = { "Vladimir Putin", "+71870306749", "Dvorets, Gelenjyk" };
	Rec r3 = { "Alexey Navalniy", "+71646554761", "Matrosskaya tishina, Russia" };
	Rec r4 = { "Takeshi Kurosava", "+818963478452", "Japan" };
	Rec r5 = { "Adriano Chellentano", "+3068393386", "Our hearts and Italy" };
	Rec r6 = { "Christophor Columbus", "+8190600004762", "Spain" };
	Rec r7 = { "Santa Claus", "+88005553535", "Laplandia" };
	rec_inf.insert(r1);
	rec_inf.insert(r2);
	rec_inf.insert(r3);
	rec_inf.insert(r4);
	rec_inf.insert(r5);
	rec_inf.insert(r6);
	rec_inf.insert(r7);

// поиск по имени
    std::cout << "Name search" << std::endl;
    std::string find_id = "Santa Claus";
	typedef Store::index<Rec::ByName>::type List;
	const List& ls = rec_inf.get<Rec::ByName>();
	List::const_iterator it = ls.find(find_id);
	if (it != ls.end())
	{
		std::cout << "Addr: " << (*it).addr << std::endl;
		std::cout << "Phone: " << (*it).phone << std::endl;
	}
	std::cout << std::endl;

    // поиск по номеру
    std::cout << "Phone search" << std::endl;
	std::string find_phone = "+442089786564";
	Store::index<Rec::ByPhone>::type::iterator it0, it1;
	tie(it0, it1) = rec_inf.get<Rec::ByPhone>().equal_range(find_phone);
	while (it0 != it1)
	{
		std::cout << "Name: " << (*it0).name << std::endl;
		++it0;
	}
	std::cout << std::endl;

    // поиск по адресу
    std::cout << "Address search" << std::endl;
	std::string find_address = "Japan";
	Store::index<Rec::ByAddr>::type::iterator it2, it3;
	tie(it2, it3) = rec_inf.get<Rec::ByAddr>().equal_range(find_address);
	while (it2 != it3)
	{
		std::cout << "Name: " << (*it2).name << std::endl;
		++it2;
	}

	std::cout << std::endl;

	// сортировка по именам
	size_t count = 1;
	for (auto it = rec_inf.begin(); it != rec_inf.end(); ++it)
	{
		std::cout << "Abonent #" << count << std::endl;
		std::cout << "Name: " << (*it).name << ", phone: " << (*it).phone << ", addr: " << (*it).addr << ";" << std::endl;
		count++;
	}

	system("pause");
	return EXIT_SUCCESS;
}
